//***********************************************************************
//      Title: clocks.c 
//      Description: This file contains the clock initializations 
//      Rachel Williams
//      September 2015
//      Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//***********************************************************************
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

//***********************************************************************
//      Function name: Five_Msec_Delay
//      Description: Creates a delay 
//      Global variables: milli_counter
//      Local variables: fivemsec
//      Return: VOID
//***********************************************************************
void Five_Msec_Delay(unsigned int fivemsec){
  milli_counter = ORIGINAL;
  while(milli_counter < (fivemsec*FIVE_MSEC));
  milli_counter = ORIGINAL;
}

//***********************************************************************
//      Function name: X_Seconds_Delay
//      Description: Creates a delay in 1 second intervals  
//      Global variables: milli_counter
//      Local variables: sec
//      Return: VOID
//***********************************************************************
void X_Seconds_Delay(unsigned int sec){
  if(sec < POSIT_10){
    milli_counter = ORIGINAL;
    while(milli_counter < (sec*ONE_SECOND));
  }
  milli_counter = ORIGINAL;
}
//***********************************************************************
//      Function name: Init_Clocks
//      Description: Clock configurations; clock initialization for the 
//                   program; initial clock configuration, runs 
//                   immediately after boot; disables 1ms watchdog timer;
//                   configure MCLK to 8MHz; configure SMCLK to 8MHz; 
//                   X1CLK is an unknown speed since X1 oscillator 
//                   not connected 
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Init_Clocks(void){
  WDTCTL = WDTPW | WDTHOLD;  // Disable watchdog
//  PJSEL0 |= XINR;
//  PJSEL0 |= XOUTR;
  
// Clocks:
// Clock System Control 0 Register
  CSCTL0 = CSKEY;            // Unlock register
  
// Clock System Control 1 Register
  CSCTL1 = CLEAR_REGISTER;   // Clear register
  CSCTL1 &= ~DCORSEL;        // DCO range select. For high-speed devices,
                             // this bit can be written by the user.
                             // For low-speed devices, it is always reset.
//  CSCTL1 |= DCOFSEL_0;     // Set 5.33MHz DCO or 16MHz  
//  CSCTL1 |= DCOFSEL_1;     // Set 6.67MHz DCO or 20MHz 
//  CSCTL1 |= DCOFSEL_2;     // Set 5.33MHz DCO or 16MHz
  CSCTL1 |= DCOFSEL_3;       // Set 8MHz DCO or 24MHz
  
// Clock System Control 2 Register
  CSCTL2 = CLEAR_REGISTER;   // Clear register
//  CSCTL2 |= SELA_0;        // set ACLK = XT1; 
  CSCTL2 = SELA_1;           // set ACLK = vlo;
  CSCTL2 |= SELS_3;          // set SMCLK = DCO;
  CSCTL2 |= SELM_3;          // set MCLK = DCO
  
// Clock System Control 3 Register
  CSCTL3 = CLEAR_REGISTER;   // Clear register
  CSCTL3 |= DIVA_0;          // set ACLK clock divider /1
  CSCTL3 |= DIVS_0;          // set SMCLK clock divider /1
  CSCTL3 |= DIVM_0;          // set MCLK clock divider /1
  
// Clock System Control 4 Register
  CSCTL4 = CLEAR_REGISTER;   // Clear register
  CSCTL4 &= ~XT1OFF;         // XT1 is on if XT1 is selected by the port selection and XT1 is not in bypass 
  CSCTL4 &= ~SMCLKOFF;       // SMCLK is not Off 
  CSCTL4 &= ~XT1BYPASS;      // XT1 sourced from external crystal 
  CSCTL4 &= ~XTS;            // Low-frequency mode
  CSCTL4 |= XT1DRIVE_0;      // Lowest current consumption for XT1 LF mode. 
                             // XT1 oscillator operating range in HF mode is 4 MHz to 8 MHz.
  CSCTL4 |= XT2OFF;          // High Frequency Oscillator 2 (XT2) disable 
  
  CSCTL0_H = CSLOCK;         // Lock registers
//------------------------------------------------------------------------------
}