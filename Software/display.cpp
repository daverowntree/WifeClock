// radio functions

// Cant really do this as a real C++ class, since we need to have 
// an ISR
  
#include "Arduino.h"
#include <DS1307RTC.h>
#include <Time.h>

#include "constants.h"
#include "globals.h"
#include "display.h"

const char lookup_tab_digpin[] = {0b11101110, 0b10001000, 0b01111100, 0b11011100, 0b10011010, 0b11010110, 0b11110110, 0b10001100, 0b11111111, 0b11011111};
const char bit2seg[] = {SEG1_PIN, SEG2_PIN, SEG3_PIN, SEG4_PIN, SEG5_PIN, SEG6_PIN, SEG7_PIN};

extern char seconds_counter;

// Perhaps inline these for more speed
void update_portb(){
    PORTB = PortB & 0x0f;
}

void update_portc(){
    PORTC = PortC & 0x1f;
}

void update_portd(){
    PORTD = PortD & 0xfc;
}

void init_display(){
  
}

// Given time as hours::mins decode into four unique digits and spit it out.
// Also handle 12/24 hour mode

int time_to_digits(char *dig1, char *dig2, char *dig3, char *dig4){
    char lhours;
    tmElements_t tm; 
  
    if (RTC.read(tm)) {
	lhours = tm.Hour;
  
	// adjust hours...
	if (gMode == DISPLAY_12HR and (lhours > 12)){
	    lhours -= 12;
	}

	*dig1 = lhours / 10;
	if (gMode == DISPLAY_12HR and !*dig1){
	    blank_dig[0] = 1; 
	} else {
	    blank_dig[0] = 0; 
	}
	*dig2 = lhours % 10;
	*dig3 = tm.Minute / 10;
	*dig4 = tm.Minute % 10;    
  
    } else {
	*dig1 = *dig2 = *dig3 = *dig4 = 0;
    }
}

//
// Turn off the display drivers to blank the display when the seconds_counter expires
//
void blank_display(void){
    digitalWrite(DIG1_PIN, LOW);
    digitalWrite(DIG2_PIN, LOW);
    digitalWrite(DIG3_PIN, LOW);
    digitalWrite(DIG4_PIN, LOW);  
}

// We're assuming the digits decoding as hh:mm has already been done
// we get called from the main loop, if the display is enabled - each digit has a time slot, with only one digit enabled at any time

void scan_display(void){
  
      if (DIG_SEP_flag && DIG_SEP_enable){
  	digitalWrite(DIG0_PIN, HIGH);
  	DIG_SEP_flag = false;
      } else if (DIG_SEP_reset_flag && DIG_SEP_enable){
  	digitalWrite(DIG0_PIN, LOW);
  	DIG_SEP_reset_flag = false;
      }
    
    digitalWrite(DIG1_PIN, LOW);
    digitalWrite(DIG2_PIN, LOW);
    digitalWrite(DIG3_PIN, LOW);
    digitalWrite(DIG4_PIN, LOW);

    // active the appropriate digit  
    switch (scan_phase){
    case 0:
	//PORTC = lookup_tab_pc[dig1];
	//PORTD = lookup_tab_pd[dig1];
	write_segs(dig1);
	if (!blank_dig[0] ){
	    digitalWrite(DIG1_PIN, HIGH);
	}    
	break;
    
    case 1:
	//PORTC = lookup_tab_pc[dig2];
	//PORTD = lookup_tab_pd[dig2];
	write_segs(dig2);
	digitalWrite(DIG2_PIN, HIGH);    
	break;
    
    case 2:
	//PORTC = lookup_tab_pc[dig3];
	//PORTD = lookup_tab_pd[dig3];    
	write_segs(dig3);
	digitalWrite(DIG3_PIN, HIGH);  
	break;
    
    case 3:
	//PORTC = lookup_tab_pc[dig4];
	//PORTD = lookup_tab_pd[dig4];    
	write_segs(dig4);
	digitalWrite(DIG4_PIN, HIGH);    
	break;
    
    default:
	break;
    }
  
    // Update the display scan phase
    if (scan_phase == 3){
	scan_phase = 0;
    } else {
	scan_phase++;
    }  
}

void write_segs(char n){
    char i;
    char bit = 2;
    char pattern = lookup_tab_digpin[n];
  
    for (i=0; i<7; i++){
	if (pattern & bit){
	    digitalWrite(bit2seg[i], LOW);
	} else {
	    digitalWrite(bit2seg[i], HIGH);       
	}
	bit = bit << 1;
    } 
}



