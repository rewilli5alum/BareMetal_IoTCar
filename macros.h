//******************************************************************************
//   Description: This file contains all the defined macros from main.c
//                and clocks.c 
//   Rachel Williams
//   September 9 2015
//******************************************************************************   

//------------------------------------------------------------------------------
// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define CNTL_STATE_INDEX        (3)

// LCD macros
#define LCD_HOME_L1	       (0x80)
#define LCD_HOME_L2            (0xA0)
#define LCD_HOME_L3            (0xC0)
#define LCD_HOME_L4            (0xE0)
#define POS_1                  (0x01)
#define POS_2                  (0x02)
#define POS_3                  (0x03)
#define POS_4                  (0x04)

// Initialize array sizes 
#define INIT_ARRAY              (0x00)
#define ARRAY_LENGTH            (0x0B)

//MACROS from clocks.c 
#define FLLN_BITS               (0x03ffu)
#define FLLN_255                (0x00ffu)

// Port 1 Pins 
#define V_DETECT_R              (0x01) // P1.0
#define V_DETECT_L              (0x02) // P1.1
#define IR_LED                  (0x04) // P1.2
#define V_THUMB                 (0x08) // P1.3
#define SPI_CS_LCD              (0x10) // P1.4
#define RS_LCD                  (0x20) // P1.5
#define SPI_SIMO                (0x40) // P1.6
#define SPI_SOMI                (0x80) // P1.7

// Port 2 Pins 
#define USB_TXD                 (0x01) // P2.0 
#define USB_RXD                 (0x02) // P2.1 
#define SPI_SCK                 (0x04) // P2.2 
#define UNK_P23                 (0x08) // P2.3 
#define UNK_P24                 (0x10) // P2.4 
#define CPU_TXD                 (0x20) // P2.5 
#define CPU_RXD                 (0x40) // P2.6 
#define UNK_P27                 (0x80) // P2.7 

// Port 3 Pins 
#define P3X                     (0x01) // P3.0
#define P3Y                     (0x02) // P3.1
#define P3Z                     (0x04) // P3.2
#define LCD_BACKLITE            (0x08) // P3.3
#define R_FORWARD               (0x10) // P3.4
#define R_REVERSE               (0x20) // P3.5
#define L_FORWARD               (0x40) // P3.6
#define L_REVERSE               (0x80) // P3.7

// Port 4 Pins 
#define SW1                     (0x01) // P4.0
#define SW2                     (0x02) // P4.1

// Port J Pins 
#define IOT_FACTORY             (0x01) // PJ.0
#define IOT_WAKEUP              (0x02) // PJ.1
#define IOT_STA_MINIAP          (0x04) // PJ.2
#define RESET                   (0x08) // PJ.3
#define XINR                    (0x10) // XINR
#define XOUTR                   (0x20) // XOUTR
#define CLEAR_REGISTER          (0x0000)

// LCD
#define ALWAYS                  (1)
#define BLINK_LED            (0x01) // Allow LED to Blink
#define CNTL_STATE_INDEX        (3) // Control States
#define LCD_LINE_1           (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_LINE_2           (0xC0) // Position Cursor at Character 01 of Line 2
#define GPS_ONOFF            (0x08) //
#define USE_LED5             (0x40)  //
#define USE_SMCLK            (0x00)  //
#define USE_NFETS            (0xA0)  //

#define CSLOCK               (0x01) // Any incorrect password locks registers

// Display Modes
#define ORIGINAL             (0x00) 
#define POSIT_0              (0)
#define POSIT_1              (1)
#define POSIT_2              (2)
#define POSIT_3              (3)
#define POSIT_4              (4)
#define POSIT_5              (5)
#define POSIT_6              (6)
#define POSIT_7              (7)
#define POSIT_8              (8)
#define POSIT_9              (9)
#define POSIT_10             (10)
#define POSIT_11             (11)
#define POSIT_12             (12) 


// Switch Constants 
#define WAIT_TIME            (20)   // Delay time
#define CYCLE                (2)    // number of times to do each shape 
#define MAX_CYCLE            (3)    // max number of times to do each shape 
#define TIME_CYCLE           (3)    // amt of time before R_wheel changes
#define MAX_CLOCK            (250)  // max clock time 
#define MAX_MSEC             (400)
#define BIG_DELAY            (500)
#define FITTY                (50)
#define HUNNIT               (100)

// Timer Interrupt 
#define TA0CCR0_INTERVAL      (125)// 25 msec = 8 mil/8/2/12500= 40 {20 (Hz)(25000)}
#define MAX_MILLI             (10000)
#define FOURP5_SEC            (4500) 
#define ONE_SECOND            (1000)          
#define FIVE_MSEC             (5)   
#define BOOT_DELAY            (25)

// ADC
#define NUM_BASE              (0x0030)

// Serial Communication 
#define SMALL_RING_SIZE       (40) 
#define BEGINNING             (0)
#define B_RATE_9600           (52)
#define B_RATE_115200         (4)
#define UCA1MCTLW_DFLT        (0x4911)
#define UCA1MCTLW_BBR         (0x5551)
#define UCA1IV_DFLT           (0x08) 
#define CAR_RET               (0x0D) 

// Hex Representaion: Numbers 
#define TEN23                 (1023)

// Global Variables
extern volatile unsigned char control_state[CNTL_STATE_INDEX];
extern volatile unsigned int Time_Sequence;
extern char led_smclk;
extern volatile char one_time; 

// For display 
extern char display_line_1[ARRAY_LENGTH];
extern char display_line_2[ARRAY_LENGTH];
extern char display_line_3[ARRAY_LENGTH];
extern char display_line_4[ARRAY_LENGTH];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;

// For detectors 
extern _Bool enabled_thumb; 
extern int temp;

// For timers 
extern volatile unsigned int milli_counter;
extern volatile unsigned int milli_counter2; 

// For ADC 
extern volatile unsigned int chng_channel; 
extern volatile unsigned int ADC_Right_Detector; 
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ADC_Thumb; 

// For serial communication 
extern volatile unsigned int cpu_rx_ring_wr;
extern volatile unsigned int cpu_rx_ring_rd;
extern volatile unsigned int cpu_tx_ring_wr;
extern volatile unsigned int cpu_tx_ring_rd;
extern volatile char CPU_Char_Rx[SMALL_RING_SIZE];
extern volatile char CPU_Char_Tx[SMALL_RING_SIZE];
extern volatile char packet; 
extern int baud_rate;
extern _Bool enabled_RX;
extern char temp1;

// For IOT communication 
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_tx_ring_wr;
extern volatile unsigned int usb_tx_ring_rd;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx[SMALL_RING_SIZE];
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern unsigned int menu_type;

// For Hex to Int conversion 
extern int diff; 
extern _Bool ones; 
extern _Bool tens; 
extern _Bool hundreds; 
extern char tens_num;
extern char hundreds_num;