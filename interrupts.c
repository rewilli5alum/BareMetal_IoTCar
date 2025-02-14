//******************************************************************************
//      Title: interrupts.c
//      Description: This file contains initialization and configuration for
//                   all interrupts
//      Rachel Williams
//      October 2015
//      Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

//******************************************************************************
//      Function name: TIMER0_A0_VECTOR 
//      Description: Sets up timer
//      Global variables: milli_counter, milli_counter2
//      Local variables: NONE
//      Return: VOID
//******************************************************************************
#pragma vector = TIMER0_A0_VECTOR 
__interrupt void Timer0_A0_ISR(void){  
  if(milli_counter >= MAX_MILLI){
    milli_counter = ORIGINAL;
  }
  
  if(milli_counter == FOURP5_SEC){
     milli_counter2++; 
     //PJOUT ^= LED3;  
     milli_counter= ORIGINAL;
  }
  milli_counter++;
  TA0CCR0 += TA0CCR0_INTERVAL; // Add Offset to TACCR0, get new interrupt
                               // same # of counts b/w interrupts 
}

//******************************************************************************
//      Function name: ADC10_ISR 
//      Description: Sets up ADC for overall system 
//      Global variables: ADC_Left_Detector, ADC_Right_Detector, ADC_Thumb_Wheel
//      Local variables: NONE
//      Return: VOID
//******************************************************************************
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
  switch(__even_in_range(ADC10IV,POSIT_12)) {
  case POSIT_0: break; // No interrupt
  case POSIT_2: break; // conversion result overflow
  case POSIT_4: break; // conversion time overflow
  case POSIT_6: break; // ADC10HI
  case POSIT_8: break; // ADC10LO
  case POSIT_10: break;// ADC10IN
  case POSIT_12:
    ADC10CTL0 &= ~ADC10ENC;    // stops sampling and conversion
    
    // preparing to change ADC channels
    switch(chng_channel++){
    case POSIT_0:                     // Left Detector 
      ADC10MCTL0 = ADC10INCH_1;       // upcoming: channel A1
      ADC_Left_Detector = ADC10MEM0;  //  channel is read to detector 
      break;
    case POSIT_1:                      // Right Detector
      ADC10MCTL0 = ADC10INCH_3;        // upcoming: channel A3  
      ADC_Right_Detector = ADC10MEM0;  // channel is read to detector 
      break;
    case POSIT_2:                      // Thumb Wheel
      ADC10MCTL0 = ADC10INCH_11;       // upcoming: channel A11           
      ADC_Thumb = ADC10MEM0;           // channel is read to thumb wheel           
      break; 
    default: break;
    }
    break; 
  default:break; 
  }
}

//******************************************************************************
//      Function name: USCI_A0_ISR
//      Description: Transmission and reception interrupt for USCI_A0
//      Global variables: usb_rx_ring_wr, temp, USB_Char_Rx[] 
//      Local variables: NONE
//      Return: VOID
//******************************************************************************
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA0IV,UCA1IV_DFLT)){
  case POSIT_0:                          // Vector 0 - no interrupt
    break;
  case POSIT_2:                          // Vector 2 - RXIFG
    temp = usb_rx_ring_wr;
    USB_Char_Rx[temp] = UCA0RXBUF;        // RX -> USB_Char_Rx character
    if (++usb_rx_ring_wr >= (SMALL_RING_SIZE)){
      usb_rx_ring_wr = BEGINNING;         // Circular buffer back to beginning
    }
    break;
  case POSIT_4:                          // Vector 4 – TXIFG
    break;
  default: break;
  }
}

//******************************************************************************
//      Function name: USCI_A1_ISR
//      Description: Transmission and reception interrupt for USCI_A1
//      Global variables: cpu_rx_ring_wr, temp, temp1 
//      Local variables: NONE
//      Return: VOID
//******************************************************************************
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){
  switch(__even_in_range(UCA1IV,UCA1IV_DFLT)){
  case POSIT_0:                               // Vector 0 - no interrupt
    break;
  case POSIT_2:                               // Vector 2 - RXIFG
    enabled_RX = POSIT_1; 
    temp = cpu_rx_ring_wr; 
    IOT_Char_Rx[temp] = UCA1RXBUF;           // RX -> IOT_Char_Rx character
    if (++cpu_rx_ring_wr >= (SMALL_RING_SIZE)){
      cpu_rx_ring_wr = BEGINNING;           // Circular buffer back to beginning
    }
    enabled_RX = ORIGINAL;
    break;
  case POSIT_4:                               // Vector 4 – TXIFG
    break;
  default: break;
  }
}