// setup functions

#include "Arduino.h"
#include "constants.h"
#include "globals.h"
#include "setup.h"
#include "clock_core.h"
#include "radio.h"
#include <DS1307RTC.h>
#include <TimerOne.h>
#include <Time.h>

// init from reset
void setup() {                
  
    // initialize the digital pins
    pinMode(ACT_LED, OUTPUT);
    pinMode(RF_IN_PIN, INPUT);
#ifdef PLAN_B
    digitalWrite(RF_IN_PIN, HIGH); // Pullup enable
#endif
  
    init_digital();

    Serial.begin(9600);
    while (!Serial) ; // wait for serial
    delay(200);
    Serial.println("Project WifeClock");
    Serial.println("-----------------"); 

#ifndef PLAN_B
    setup_rf();
#endif    
    setup_clock();
    init_clock();
}

void setup_clock(){
    //init_display(); // empty
    // initialise the I2C interface
  
    // initialise timer interrupt for 1ms
    Timer1.initialize(100);
    //Timer1.attachInterrupt(isr); // DRO: This should be deleted once radio integration is proved to work (kicked off by radio ISR instead)
    Timer1.attachInterrupt(radio_isr);
}

void setup_rf(){
    // Initialise the IO and ISR
    //vw_set_ptt_inverted(true); // Required for DR3100   ** FIXME needed ? **
    vw_setup(2000);	 // Bits per sec 
    vw_set_rx_pin(RF_IN_PIN);
    vw_rx_start();       // Start the receiver PLL running
}

void init_digital(){
    // Configure pin directions
    // Port B
    pinMode(RF_IN_PIN, INPUT);
    pinMode(DIG3_PIN, OUTPUT);
    pinMode(DIG4_PIN, OUTPUT);
    pinMode(DIG0_PIN, OUTPUT);  
 
    // Port C
    pinMode(SEG1_PIN, OUTPUT);
    pinMode(SEG2_PIN, OUTPUT);
    pinMode(SEG3_PIN, OUTPUT);
    pinMode(SEG4_PIN, OUTPUT);
  
    // Port D
    pinMode(SEG5_PIN, OUTPUT);
    pinMode(SEG6_PIN, OUTPUT);
    pinMode(SEG7_PIN, OUTPUT);
    pinMode(DIG2_PIN, OUTPUT); 
    pinMode(DIG1_PIN, OUTPUT); 
}

void init_clock(){
    tmElements_t tm; 
  
    //init_time();
  
    if (RTC.read(tm)) {
	Serial.print("init_clock() Current Time = ");
	print2digits(tm.Hour);
	Serial.write(':');
	print2digits(tm.Minute);
	Serial.write(':');
	print2digits(tm.Second);
	Serial.println();
    
    } else {
	if (RTC.chipPresent()) {
	    Serial.println("The DS1307 is stopped.  Resetting...");
	    init_time();
      
	} else {
	    Serial.println("DS1307 read error");
	}  
    }
}

tmElements_t tm; 

void init_time(){
    bool parse=false;
    bool config=false;
     
    // get the date and time the compiler was run
    if (getTime(__TIME__)) {
	parse = true;
	// and configure the RTC with this info
	if (RTC.write(tm)) {
	    config = true;
	}
    }

    if (parse && config) {
	Serial.print("DS1307 configured Time=");
	Serial.print(__TIME__);
	Serial.print(", Date=");
	Serial.println(__DATE__);
    } else if (parse) {
	Serial.println("DS1307 Communication Error :-{");
	Serial.println("Please check your circuitry");
    } else {
	// cannot parse
    }
}

bool getTime(const char *str)
{
    int Hour, Min, Sec;

    if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
    tm.Hour = Hour;
    tm.Minute = Min;
    tm.Second = Sec;
    return true;
}

void print2digits(int number) {
    if (number >= 0 && number < 10) {
	Serial.write('0');
    }
    Serial.print(number);
}



