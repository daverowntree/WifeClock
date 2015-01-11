
// Define to select plan b - disable radio RX and re-use pin as manual clock enable with 10s timer
#define PLAN_B 1

extern char PortB;
extern char PortC;
extern char PortD;

extern int slot;
extern boolean TOS_flag;
extern boolean TOS_enable;
extern boolean DIG_SEP_reset_flag;
extern boolean DIG_SEP_enable;
extern boolean DIG_SEP_flag;

extern state_t State;

// hardware mappings
extern const int digits[NUM_DIGITS]; // digital pin number so we can use digitalWrite
extern char dig1, dig2, dig3, dig4;
extern char blank_dig[NUM_DIGITS];

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
extern const char lookup_tab_pc[];
extern const char lookup_tab_pd[];
extern const char lookup_tab_digpin[];
extern const char bit2seg[];

//char gMode = DISPLAY_12HR;
extern char gMode;
extern char scan_phase;

