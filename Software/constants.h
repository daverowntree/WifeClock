// constant declarations

// Hardware Consts
#define NUM_SEGMENTS 70
#define NUM_DIGITS 5
#define ACT_LED 7
#define RF_IN_PIN 8

// Global config defaults
#define MAX_BRIGHTNESS 255
//      BRIGHTNESS units/ms
#define FADEIN_RATE 10
#define FADEOUT_RATE 10

//      ms
#define WAKE_TIME 5000

// 12/24 Hour mode
#define DISPLAY_12HR 0
#define DISPLAY_24HR 1

// ->Main state machine<-
typedef enum {IDLE, SLEEP, FADEIN, HOLD, FADEOUT } state_t;

// digital bindings
// PortB
// 0 rf_data
// 1 digit3
// 2 digit4
// 3 digit0
// 4 x
// 5 x
// 6 x
// 7 x

// Masks and shifts
#define PORTB_DIG_MASK 0x0e
#define PORTB_DIG_SHIFT 1
#define PORTB_RFIN_MASK 0x01
#define PORTB_RFIN_SHIFT 0

// Hardware pin mapping
#define DIG3_PIN  9
#define DIG4_PIN  10
#define DIG0_PIN  11

// PortC
// 0 seg1
// 1 seg2
// 2 seg3
// 3 seg4
// 4 (SDA)
// 5 (SCL)
// 6 x
// 7 x

// Masks and shifts
#define PORTC_SEG_MASK 0x1f
#define PORTC_SEG_SHIFT 0

// Hardware pin mapping
#define SEG1_PIN 14
#define SEG2_PIN 15
#define SEG3_PIN 16
#define SEG4_PIN 17
#define SDA_PIN 27
#define SCL_PIN 28

// PortD
// 0 RxD
// 1 TxD
// 2 seg5
// 3 seg6
// 4 seg7
// 5 digit2
// 6 digit1
// 7 activity

// Masks and shifts
#define PORTD_SEG_MASK 0x1c
#define PORTD_SEG_SHIFT 2
#define PORTD_DIG_MASK 0x60
#define PORTD_DIG_SHIFT 5
#define PORTD_ACT_MASK 0x80
#define PORTD_ACT_SHIFT 7

// Hardware pin mapping
#define RXD_PIN 2
#define TXD_PIN 3
#define SEG5_PIN 2
#define SEG6_PIN 3
#define SEG7_PIN 4
#define DIG2_PIN 5
#define DIG1_PIN 6

// Maximum number of bytes in a message, counting the byte count and FCS
#define VW_MAX_MESSAGE_LEN 30

// The maximum payload length
#define VW_MAX_PAYLOAD VW_MAX_MESSAGE_LEN-3

// The size of the receiver ramp. Ramp wraps modulu this number
#define VW_RX_RAMP_LEN 160

// Number of samples per bit
#define VW_RX_SAMPLES_PER_BIT 8

// Ramp adjustment parameters
// Standard is if a transition occurs before VW_RAMP_TRANSITION (80) in the ramp,
// the ramp is retarded by adding VW_RAMP_INC_RETARD (11)
// else by adding VW_RAMP_INC_ADVANCE (29)
// If there is no transition it is adjusted by VW_RAMP_INC (20)
#define VW_RAMP_INC (VW_RX_RAMP_LEN/VW_RX_SAMPLES_PER_BIT)
#define VW_RAMP_TRANSITION VW_RX_RAMP_LEN/2
#define VW_RAMP_ADJUST 9
#define VW_RAMP_INC_RETARD (VW_RAMP_INC-VW_RAMP_ADJUST)
#define VW_RAMP_INC_ADVANCE (VW_RAMP_INC+VW_RAMP_ADJUST)

// Outgoing message bits grouped as 6-bit words
// 36 alternating 1/0 bits, followed by 12 bits of start symbol
// Followed immediately by the 4-6 bit encoded byte count, 
// message buffer and 2 byte FCS
// Each byte from the byte count on is translated into 2x6-bit words
// Caution, each symbol is transmitted LSBit first, 
// but each byte is transmitted high nybble first
#define VW_HEADER_LEN 8


