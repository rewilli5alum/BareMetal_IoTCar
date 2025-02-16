//******************************************************************************
//   Name: init.c
//   Author: Rachel E. Williams
//   Date Created: September 9 2015 (9/9/2015)
//   Last Updated: 2/15/2025
//   Description: This file contains the configuration and initialization for
//                interrupts, Timers, ADC, and UART
//   Originally built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//   Updated revisions built with IAR Embedded Workbench - MSP430 V8.10.3
//******************************************************************************   

// #includes 
#include "msp430.h"
#include "functions.h"
#include "macros.h"

// Global Variables 

// Constant Variables

//------------------------------------------------------------------------------
//      Function name: Init_Conditions
//      Description: Initialization configurations for interrupts and
//                   display features
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Init_Conditions(void){
  // Interrupts are disabled by default, they are enabled here  
  enable_interrupts();
  display_1 = &display_line_1[INIT_ARRAY];
  display_2 = &display_line_2[INIT_ARRAY];
  display_3 = &display_line_3[INIT_ARRAY];
  display_4 = &display_line_4[INIT_ARRAY];
}

//------------------------------------------------------------------------------
//      Function name: Init_Timers
//      Description: Initializes all timers. Timers not used for the project are
//                   commented
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Init_Timers(void){
  Init_Timer_A0();     //
  //  Init_Timer_A1(); // 
  //  Init_Timer_B0(); // 
  //  Init_Timer_B1(); //  
  Init_Timer_B2();     //  Required for instructor-provided compiled code to run
}

//------------------------------------------------------------------------------
//      Function name: Init_Timer_A0
//      Description: Initializes Timer A0, sets up both A0_0 and A0_1-A0_2
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Init_Timer_A0(void) {
  TA0CTL = TASSEL__SMCLK;    // SMCLK source
  TA0CTL |= TACLR;           // Resets TA0R, clock divider, count direction
  TA0CTL |= MC__CONTINOUS;   // Continuous up to 0xFFFH then back to 0
  TA0CTL |= ID__2;           // Divide clock by 2
  TA0CTL &= ~TAIE;           // Disable Overflow Interrupt
  TA0CTL &= ~TAIFG;          // Clear Overflow Interrupt flag
  
  TA0EX0 = TAIDEX_7;         // Divide clock by an additional 8, index bit
  
  TA0CCR0 = TA0CCR0_INTERVAL; // CCR0, time the timer counts up to 
  TA0CCTL0 |= CCIE;           // CCR0 enable interrupt, as soon as it's 
                              //    initialized, interrupts will be enabled
}

//------------------------------------------------------------------------------
//      Function name: ADC_Process
//      Description: Configures system for analog-to-digital (ADC) ADC sampling 
//                   and conversion for ADC channel 10
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void ADC_Process(void){
  while (ADC10CTL1 & BUSY);              // Wait if ADC10 core is active
  ADC10CTL0 |= ADC10ENC + ADC10SC;       // Sampling and conversion start
} 

//------------------------------------------------------------------------------
//      Function name: Init_Serial_UCA0
//      Description: Initializing serial port for CPU communication 
//      Global variables: CPU_Char_Rx, CPU_Char_Tx, cpu_rx_ring_wr,
//                        cpu_rx_ring_rd, cpu_tx_ring_wr, cpu_tx_ring_rd
//      Local variables: i 
//      Return: VOID
//------------------------------------------------------------------------------
void Init_Serial_UCA0(void){
  int i;
  for(i=POSIT_0; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = ORIGINAL;                 // USB Rx Buffer
  }
  usb_rx_ring_wr = BEGINNING;
  usb_rx_ring_rd = BEGINNING;
  
  for(i=ORIGINAL; i<SMALL_RING_SIZE; i++){ 
    USB_Char_Tx[i] = CLEAR_REGISTER;          // USB Tx Buffer
  }
  usb_tx_ring_wr = BEGINNING;
  usb_tx_ring_rd = BEGINNING;
  
  // Configure UART 0
  UCA0CTLW0 = POSIT_0;                         // Use word register
  UCA0CTLW0 |= UCSSEL__SMCLK;                  // Set SMCLK as fBRCLK
  UCA0CTLW0 |= UCSWRST;                        // Set Software reset enable
  UCA0BRW = B_RATE_9600;                       // 9,600 Baud
  UCA0MCTLW = UCA1MCTLW_DFLT;                  // UCA0MCTLW = UCSx concatenate 
                                               //    UCFx concatenate UCOS16;
  
  // re-configuring ports 
  P2SEL0 &= ~USB_TXD;
  P2SEL1 |= USB_TXD; 
  P2OUT |= USB_TXD; 
  P2DIR |= USB_TXD; 
  
  P2SEL0 &= ~USB_RXD;
  P2SEL1 |= USB_RXD;
  P2OUT &= ~USB_RXD; 
  P2DIR &= ~USB_RXD;
  
  P2SEL1 |= CPU_TXD;
  P2SEL0 &= ~CPU_TXD;
  P2OUT  |= CPU_TXD;
  P2DIR  |= CPU_TXD;
  
  P2SEL1 |= CPU_RXD;
  P2SEL0 &= ~CPU_RXD;
  P2OUT &= ~CPU_RXD;
  P2DIR &= ~CPU_RXD;
  
  UCA0CTL1 &= ~UCSWRST;                       // Release from reset
  UCA0IE |= UCRXIE;                           // Enable RX interrupt
  UCA0IE |= UCTXIE;                           // Enable TX interrupt 
}

//------------------------------------------------------------------------------
//      Function name: Init_Serial_UCA1
//      Description: Initializing serial port for CPU communication 
//      Global variables: CPU_Char_Rx, CPU_Char_Tx, cpu_rx_ring_wr,
//                        cpu_rx_ring_rd, cpu_tx_ring_wr, cpu_tx_ring_rd
//      Local variables: i 
//      Return: VOID
//------------------------------------------------------------------------------
void Init_Serial_UCA1(void){
  int i;
  for(i=ORIGINAL; i<SMALL_RING_SIZE; i++){
    CPU_Char_Rx[i] = CLEAR_REGISTER;          // CPU Rx Buffer
  }
  cpu_rx_ring_wr = BEGINNING;
  cpu_rx_ring_rd = BEGINNING;
  
  for(i=ORIGINAL; i<SMALL_RING_SIZE; i++){ 
    CPU_Char_Tx[i] = CLEAR_REGISTER;           // CPU Tx Buffer
  }
  cpu_tx_ring_wr = BEGINNING;
  cpu_tx_ring_rd = BEGINNING;
  
  // Configure UART 1
  UCA1CTLW0 = ORIGINAL;                       // Use word register
  UCA1CTLW0 |= UCSSEL__SMCLK;                 // Set SMCLK as fBRCLK
  UCA1CTLW0 |= UCSWRST;                       // Set Software reset enable     
  UCA1BRW = B_RATE_9600;                      // setting baud rate 
  UCA1MCTLW = UCA1MCTLW_DFLT;
  
  // Re-configuring ports 
  P2SEL0 &= ~USB_TXD;
  P2SEL1 |= USB_TXD; 
  P2OUT |= USB_TXD; 
  P2DIR |= USB_TXD; 
  
  P2SEL0 &= ~USB_RXD;
  P2SEL1 |= USB_RXD;
  P2OUT &= ~USB_RXD; 
  P2DIR &= ~USB_RXD;
  
  P2SEL1 |= CPU_TXD;
  P2SEL0 &= ~CPU_TXD;
  P2OUT  |= CPU_TXD;
  P2DIR  |= CPU_TXD;
  
  P2SEL1 |= CPU_RXD;
  P2SEL0 &= ~CPU_RXD;
  P2OUT &= ~CPU_RXD;
  P2DIR &= ~CPU_RXD;
  
  // Reset release and interrupt enabling 
  UCA1CTL1 &= ~UCSWRST;                     // Release from reset
  UCA1IE |= UCRXIE;                         // Enable RX interrupt
  UCA1IE |= UCTXIE;                         // Enable TX interrupt 
}