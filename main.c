//******************************************************************************
//  Title: main.c 
//  Description: This file contains the Main Routine - "While" Operating System
//  Rachel Williams
//  October 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

//-----------------------Global Variables---------------------------------------
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time; 

// For display 
extern char display_line_1[ARRAY_LENGTH];
extern char display_line_2[ARRAY_LENGTH];
extern char display_line_3[ARRAY_LENGTH];
extern char display_line_4[ARRAY_LENGTH];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char posL1;
char posL2;
char posL3;
char posL4;

// For emitters, detectors, thumb wheel 
int calib_amtR;
int calib_amtL;

// For timers 
volatile unsigned int milli_counter;
volatile unsigned int milli_counter2; 

// For ADC 
volatile unsigned int chng_channel; 
volatile unsigned int ADC_Right_Detector; 
volatile unsigned int ADC_Left_Detector;
volatile unsigned int ADC_Thumb; 
int temp;
volatile char packet;

// For serial communication 
volatile unsigned int cpu_rx_ring_wr;
volatile unsigned int cpu_rx_ring_rd;
volatile unsigned int cpu_tx_ring_wr;
volatile unsigned int cpu_tx_ring_rd;
volatile char CPU_Char_Rx[SMALL_RING_SIZE];
volatile char CPU_Char_Tx[SMALL_RING_SIZE];
int baud_rate;
int diff;
_Bool enabled_RX;
char temp1;
_Bool ones; 
_Bool tens; 
_Bool hundreds; 
char tens_num;
char hundreds_num;

// For IOT communication 
volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_rd;
volatile char USB_Char_Rx[SMALL_RING_SIZE];
volatile char USB_Char_Tx[SMALL_RING_SIZE];
volatile char IOT_Char_Rx[SMALL_RING_SIZE];
unsigned menu_type;
_Bool is_pressed;

//------------------------------------------------------------------------------
void main(void){
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System 
  Init_Conditions();
  Time_Sequence = ORIGINAL;             
  Init_Timers();                       // Initialize Timers
  Five_Msec_Delay(BOOT_DELAY);
  Init_LCD();                          // Initialize LCD
  ADC_Process();                       // Configuring for ADC 
  Init_Serial_UCA0(); 
  Init_Serial_UCA1();                  // Initialize ports for serial coms 
 
  // Turning off all motors at initialization 
  Left_Reverse_Off(); 
  Right_Reverse_Off(); 
  
  // Initializing counters for interrupt timers 
  milli_counter = ORIGINAL;
  milli_counter2 = ORIGINAL;
  
  // Initializing variables for thumb wheel 
  chng_channel = ORIGINAL;
  temp = ORIGINAL;
  diff = ORIGINAL;
  tens = ORIGINAL;
  hundreds = ORIGINAL;
  enabled_RX=POSIT_0;
  temp1 = NUM_BASE;
  tens_num = NUM_BASE;
  hundreds_num = NUM_BASE;
  menu_type = ORIGINAL;
  lcd_BIG_mid();
   
  // Initial display 
  display_1 = "Rachel";
  posL1 = POSIT_2;
  display_2 = "PROJECT 8";
  posL2 = POSIT_0;
  display_3 = "Williams";
  posL3 = POSIT_1;
  Display_Process(); 
  
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
while(ALWAYS) {                            // Can the Operating system run
  switch(Time_Sequence){
    case 250:                               // 1000 msec  
      /*if(one_time){
        Init_LEDs();                        // Initialize LEDs
        one_time = 0;
      }
      Time_Sequence = 0;*/                    // 
    case 200:                               // 1000 msec  
      /*if(one_time){
        PJOUT |= LED4;                      // Change State of LED 4
        P3OUT |= LED5;                      // Change State of LED 5
        one_time = 0;
      }*/
    case 150:                               // 750 msec  
      /*if(one_time){
        PJOUT |= LED3;                      // Change State of LED 3
        P3OUT |= LED6;                      // Change State of LED 6
        one_time = 0;
      }*/
    case 100:                               // 500 msec  
      /*if(one_time){
        PJOUT |= LED2;                      // Change State of LED 2
        P3OUT |= LED7;                      // Change State of LED 7
        one_time = 0;
      }*/
    case  50:                               // 250 msec  
      /*if(one_time){
        PJOUT |= LED1;                      // Change State of LED 1
        P3OUT |= LED8;                      // Change State of LED 8
        one_time = 0;
      }*/
      break;                                // 
    default: break; 
  }
  Switches_Process();                       // Check for switch state change 
  if(Time_Sequence > 250){
    Time_Sequence = 0;
  }
 }
//------------------------------------------------------------------------------
}