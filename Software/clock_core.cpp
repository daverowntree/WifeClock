// radio functions

#include "Arduino.h"
#include "constants.h"
#include "globals.h"
#include "radio.h"
#include "clock_core.h"
#include "display.h"

extern char seconds_counter;

void isr(void){

    // timing slot decoder - let's not hang around too long...
    switch (State){
    case IDLE:
	break;
    
    case SLEEP:

	break;
    
    case FADEIN:
	break;
    
    case HOLD:
    
	break;
    
    case FADEOUT:
	break;
    
    default: State = IDLE;  
    }  

    if (State != SLEEP){
    
	// Top of Second sampling of RTC - updating display digits
	if (slot < 50 & !TOS_flag  & !TOS_enable) { // 5->50
	    TOS_flag = true;
	    TOS_enable = true;
	}
	if (slot > 50){ // 5->50
	    TOS_enable = false;    
	}
    
	// Digits separator
	if (slot > 5000 && !DIG_SEP_reset_flag && !DIG_SEP_enable){ // 500->5000
	    DIG_SEP_reset_flag = true;
	    DIG_SEP_enable = true;
	}
    }

#ifdef PLAN_B
    if (seconds_counter) {
      scan_display();
    } else {
      blank_display(); 
    }
#else
    scan_display();
#endif
    // Slot counter
    slot++;
    if (slot >= 10000){ // 1000->10000
	slot = 0;
	TOS_flag = false;
	TOS_enable = false;    
	DIG_SEP_reset_flag = false;
	DIG_SEP_enable = false;
    }  
}


