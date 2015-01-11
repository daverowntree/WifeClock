/*
  WifeClock Receiver (the clock bit) for Arduino.1.0.5

  Set Board->Arduino Uno
  Set Progammer->AVRISP MkII (others untested)

  Dave Rowntree
  
  Version  Date        Notes
  1.0      19/01/14    Initial version
  1.1      
  
*/
#include "Arduino.h"
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>

#include <TimerOne.h>
//#include <VirtualWire.h>

#include "radio.h"
#include "constants.h"
#include "setup.h"
#include "clock_core.h"
#include "display.h"
#include "globals.h"

// Port globals
// Need to store the current values of the digital ports in one common place, and combine the
// bits from all connections in one place 

char PortB = 0;
char PortC = 0;
char PortD = 0;

int slot = 0;
boolean TOS_flag = false;
boolean TOS_enable = false;
boolean DIG_SEP_reset_flag = false;
boolean DIG_SEP_enable = false;
boolean DIG_SEP_flag = false;

state_t State = HOLD;

// hardware mappings
const int digits[NUM_DIGITS] = {DIG0_PIN,DIG1_PIN,DIG2_PIN,DIG3_PIN,DIG4_PIN}; // digital pin number so we can use digitalWrite
char dig1=0, dig2=0, dig3=0, dig4=0;
char blank_dig[NUM_DIGITS] = {0,0,0,0};

// Digit lookup table; convert ascii to segment pattern - we need two patterns, one for portC and portD
// need to avoid PD[7..5] as these are used for digits and activity LED
// index[0] is ascii(32)

/*
        s2              s1 pc0
     xxxxxxxx           s2 pc1
  s1 x      x s3        s3 pc2
     x  s4  x           s4 pc3
     xxxxxxxx           s5 pd2
  s5 x      x s7        s6 pd3
     x      x           s7 pd4
     xxxxxxxx
        s6
*/

// Just digits 0-9 for now
// Other potential digits that can be represented: A b cC d eE F G H I J L n oO P Q r S t uU Y
const char lookup_tab_pc[] = {0b00000111, 0b00000001, 0b00001110, 0b00001110, 0b00001101, 0b00001101, 0b00001101, 0b00000110, 0b00001111, 0b00001111};
const char lookup_tab_pd[] = {0b00011100, 0b00000100, 0b00001100, 0b00011000, 0b00010000, 0b00011000, 0b00011100, 0b00010000, 0b00011100, 0b00011000};

//char gMode = DISPLAY_12HR;
char gMode = DISPLAY_24HR;
char scan_phase = 0;

// main application loop
void loop() {
#ifndef PLAN_B
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    // rf_loop kicks off the clock 'loop' for a fixed time then get's restarted
    if (vw_get_message(buf, &buflen)){ // Non-blocking
        Serial.println("HERE");
        checkmessage(buf);
    }
#endif
    clock_loop();
}

bool checkmessage(uint8_t *buf){
  
    Serial.print("rx:");  
    Serial.println((char*)buf);  
    
    return(true); // fixme
}

char seconds_counter = 0;

void clock_loop(){
    char tick_flag = 1;
    char tick_counter = 10; // 10 seconds
    char dig = 0;
    char sep = 0;      
#ifdef PLAN_B    
    pinMode(RF_IN_PIN, INPUT);
    digitalWrite(RF_IN_PIN, HIGH);
   
    if (!digitalRead(RF_IN_PIN)){
      seconds_counter = 10;
     Serial.println("push!"); 
    }
#endif    

    //while(1){
      if (seconds_counter){
	if (TOS_flag && TOS_enable) {
	    time_to_digits(&dig1, &dig2, &dig3, &dig4);
	    digitalWrite(DIG0_PIN, HIGH);  
	}    
	if (DIG_SEP_reset_flag && DIG_SEP_enable){
	    digitalWrite(DIG0_PIN, LOW); 
	    DIG_SEP_reset_flag = false;
	}
      } else {
	    digitalWrite(DIG0_PIN, LOW); 
	    DIG_SEP_reset_flag = false;        
      }
      
	if (slot==0){
	    if (tick_flag){
		tick_counter--;
		//Serial.println("tick!"); 
		tick_flag = 0;

#ifdef PLAN_B
              if (seconds_counter){
                seconds_counter--;    
              }
#endif
	    }
	}
    
	if (slot>900){
	    tick_flag = 1; 
	}
	//if (!tick_counter) return;
    //}
}




