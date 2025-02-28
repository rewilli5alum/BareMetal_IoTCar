//******************************************************************************
//   Name: main.c
//   Author: Rachel E. Williams
//   Date Created: September 9 2015 (9/9/2015)
//   Last Updated: 2/17/2025
//   Description: This file contains the main routine to run the entire project
//                using while(1) "Super Loop" architecture
//   
//******************************************************************************   

// #includes 
#include "msp430.h"
#include "functions.h"
#include "macros.h"

// Global Variables 
volatile unsigned int Time_Sequence;
volatile char one_time; 

// For display 
char posL1;
char posL2;
char posL3;
char posL4;

// For timers 
volatile unsigned int milli_counter;
volatile unsigned int milli_counter2; 

// For ADC 
volatile unsigned int chng_channel; 
volatile unsigned int ADC_Right_Detector; 
volatile unsigned int ADC_Left_Detector;
volatile unsigned int ADC_Thumb; 
int temp;

// For serial communication 
volatile unsigned int cpu_rx_ring_wr;
volatile unsigned int cpu_rx_ring_rd;
volatile unsigned int cpu_tx_ring_wr;
volatile unsigned int cpu_tx_ring_rd;
volatile char CPU_Char_Rx[SMALL_RING_SIZE];
volatile char CPU_Char_Tx[SMALL_RING_SIZE];
int diff;
_Bool enabled_RX;
char temp1;
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

// Constant Variables 

void main(void)
{
    Init_Ports();                        // Initialize Ports
    Init_Clocks();                       // Initialize Clock System 
    Init_Conditions();                   // Initialize and enable Interrupts
    Time_Sequence = ORIGINAL;             
    Init_Timers();                       // Initialize Timers
    Five_Msec_Delay(BOOT_DELAY);
    Init_LCD();                          // Initialize LCD screen
    ADC_Process();                       // Configuring for ADC 
    Init_Serial_UCA0(); 
    Init_Serial_UCA1();                  // Initialize ports for serial comms 
 
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
    Out_To_LCD(display_1,posL1,display_2,posL2,display_3,posL3,display_4,posL4); 
    Display_Process(); 
  
//------------------------------------------------------------------------------
// Begining of the While "Super Loop" Operating System
//------------------------------------------------------------------------------
    while(ALWAYS) 
    {  
      // After initialization, waiting for state change of switches--SW1 or SW2
      Switches_Process(); 
      
      // Resetting the Time_Sequence counter 
      if(Time_Sequence > 250)
      {
        Time_Sequence = 0;
      }
    }  
}
//------------------------------------------------------------------------------
// End of the While "Super Loop" Operating System
//------------------------------------------------------------------------------