//***********************************************************************
//      Title: ports.c 
//      Description: This file contains all port definitions 
//      Rachel Williams
//      September 2015
//      Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//***********************************************************************

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

//***********************************************************************
//      Function name: Init_Ports
//      Description: Initializes all port functions 
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Init_Ports(void){
	Init_Port1();
        Init_Port2();
        Init_Port3();
        Init_Port4();
        Init_PortJ();
        Init_ADC();
}

//***********************************************************************
//      Function name: Init_Port_1 
//      Description: Initializes Port 1
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Init_Port1(void){
  //---------------------------------------------------------------------
  // Pin Name   Function        P1DIR.x P1SEL1.x        P1SEL0.x
  // P1.0       I/O             0/1     0               0       
  //            TA0.CCI1A       0       0               1
  //            TA0.1           1       0               1
  //            DMAE0           0       1               0
  //            RTCCLK          1       1               0
  //            A0              X       1               1
  //            CD0             X       1               1
  //            VeREF           X       1               1
  // P1.1       I/O             0/1     0               0       
  //            TA0.CCI2A       0       0               1
  //            TA0.2           1       0               1
  //            TA1CLK          0       1               0
  //            CDOUT           1       1               0
  //            A1              X       1               1
  //            CD1             X       1               1
  //            VeREF           X       1               1
  // P1.2       I/O             0/1     0               0       
  //            TA1.CCI2A       0       0               1
  //            TA1.1           1       0               1
  //            TA0CLK          0       1               0
  //            CDOUT           1       1               0
  //            A2              X       1               1
  //            CD2             X       1               1
  // P1.3       I/O             0/1     0               0       
  //            TA1.CCI2A       0       0               1
  //            TA1.2           1       0               1
  //            UCB0STE         X       1               0
  //            A3              X       1               1       
  //            CD3             X       1               1
  // P1.4       I/O             0/1     0               0       
  //            TB0.CCI2A       0       0               1
  //            TB0.2           1       0               1
  //            UCA0STE         X       1               0
  //            A4              X       1               1       
  //            CD4             X       1               1
  // P1.5       I/O             0/1     0               0       
  //            TB0.CCI2A       0       0               1
  //            TB0.2           1       0               1
  //            UCA0CLK         X       1               0
  //            A5              X       1               1       
  //            CD5             X       1               1
  // P1.6       I/O             0/1     0               0
  //            TB1.CCI1A       0       0               1
  //            TB1.1           1       0               1
  //            UCB0SIMO/       X       1               0
  //             UCB0SDA
  //            TA0.CCI0A       0       1               1
  //            TA0.0           1       1               1       
  // P1.7       I/O             0/1     0               0
  //            TB1.CCI2A       0       0               1
  //            TB1.2           1       0               1
  //            UCB0SOMI/       X       1               0
  //             UCB0SCL
  //            TA1.CCI0A       0       1               1
  //            TA1.0           1       1               1  
  //---------------------------------------------------------------------
  //Configure Port 1
  // V_DETECT_R (0x01) //
  // V_DETECT_L (0x02) //
  // IR_LED (0x04) //
  // V_THUMB (0x08) //
  // SPI_CS_LCD (0x10) // LCD Chip Select
  // RS_LCD (0x20) // LCD SA0 H/L Slave Address
  // SIMO_B (0x40) // SPI mode - slave in/master out of USCI_B0
  // SOMI_B (0x80) // SPI mode - slave out/master in of USCI_B0
  //----------------------------------------------------------------------
  P1SEL0 = CLEAR_REGISTER; // P1 set as I/0
  P1SEL1 = CLEAR_REGISTER; // P1 set as I/0
  P1DIR = CLEAR_REGISTER; // Set P1 direction to input
  
  P1SEL0 |= V_DETECT_R; // V_DETECT_R selected
  P1SEL1 |= V_DETECT_R; // V_DETECT_R selected
  P1OUT &= ~V_DETECT_R; // Output is 0 
  P1DIR &= ~V_DETECT_R; // DIR is 0
  
  P1SEL0 |= V_DETECT_L; // V_DETECT_L selected
  P1SEL1 |= V_DETECT_L; // V_DETECT_L selected
  P1OUT &= ~V_DETECT_L; // Output is 0 
  P1DIR &= ~V_DETECT_L;  // DIR is 0
  
  P1SEL0 &= ~IR_LED; // IR_LED GPI/O selected
  P1SEL1 &= ~IR_LED; // IR_LED GPI/O selected
  P1OUT |= IR_LED; // P1 IR_LED Port Pin set low
  P1DIR |= IR_LED; // Set P1 IR_LED direction to output
  
  P1SEL0 |= V_THUMB; // V_THUMB selected
  P1SEL1 |= V_THUMB; // V_THUMB selected
  P1OUT &= ~V_THUMB; // Output is 0 
  P1DIR &= ~V_THUMB; // DIR is 0 
  
  P1SEL0 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
  P1SEL1 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
  P1OUT |= SPI_CS_LCD; // P1 SPI_CS_LCD Port Pin set high
  P1DIR |= SPI_CS_LCD; // Set SPI_CS_LCD output direction
  
  P1SEL0 &= ~RS_LCD; // RS_LCD GPI/O selected
  P1SEL1 &= ~RS_LCD; // RS_LCD GPI/O selected  
  P1OUT &= ~RS_LCD; // P1 SA0_LCD Port Pin set low
  P1DIR |= RS_LCD; // Set SA0_LCD output direction
  
  P1SEL0 &= ~SPI_SIMO; // SIMO_B selected
  P1SEL1 |= SPI_SIMO; // SIMO_B selected
  P1OUT &= ~SPI_SIMO; // Output is 0
  P1DIR |= SPI_SIMO; // SIMO_B set to Output
  
  P1SEL0 &= ~SPI_SOMI; // SOMI_B is used on the LCD
  P1SEL1 |= SPI_SOMI; // SOMI_B is used on the LCD
  P1OUT &= ~SPI_SOMI; // SOMI_B is not set to output 
  P1DIR &= ~SPI_SOMI; // SOMI_B set to Input
  P1REN |= SPI_SOMI; // Enable pullup resistor
}

//***********************************************************************
//      Function name: Init_Port_2 
//      Description: Initializes Port 2
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Init_Port2(void){
  //---------------------------------------------------------------------
  // Pin Name   Function        P2DIR.x    P2SEL1.x        P2SEL0.x
  // P2.0       I/0             0/1        0               0
  //            TB2.CCI0A       0          0               1
  //            TB2.0           1          0               1
  //            UCA0TXD/        X          1               0
  //             UCA0SIMO
  //            TB0CLK          0          1               1
  //            ACLK            1          1               1
  // P2.1       I/0             0/1        0               0
  //            TB2.CCI1A       0          0               1
  //            TB2.1           1          0               1
  //            UCA0RXD/        X          1               0
  //             UCA0SOMI
  //            TB0.CCI0A       0          1               1
  //            TB0.0           1          1               1
  // P2.2       I/0             0/1        0               0
  //            TB2.CCI2A       0          0               1
  //            TB2.2           1          0               1
  //            UCB0CLK         X          1               0
  //            TB1.CCI0A       0          1               1
  //            TB1.0           1          1               1
  // P2.3       I/O             0/1        0               0
  //            TA0.CCI0B       0          0               1
  //            TA0.0           1          0               1
  //            UCA1STE         X          1               0 
  //            A6              X          1               1
  //            CD10            X          1               1 
  // P2.4       I/O             0/1        0               0
  //            TA1.CCI0B       0          0               1
  //            TA1.0           1          0               1
  //            UCA1CLK         X          1               0 
  //            A7              X          1               1
  //            CD11            X          1               1 
  // P2.5       I/O             0/1        0               0
  //            TB0.CCI0B       0          0               1 
  //            TB0.0           1          0               1
  //            UCA1TXD/        X          1               0
  //             UCA1SIMO
  // P2.6       I/O             0/1        0               0
  //            TB1.CCI0B       0          0               1 
  //            TB1.0           1          0               1
  //            UCA1RXD/        X          1               0
  //             UCA1SOMI
  // P2.7       I/0             0/1        0               0 
  //---------------------------------------------------------------------
  P2SEL0 = CLEAR_REGISTER; 
  P2SEL1 = CLEAR_REGISTER;
  P2OUT = CLEAR_REGISTER;
  P2DIR = CLEAR_REGISTER; 
    
  // P2.0 USB_TXD 
  P2SEL0 &= ~USB_TXD;
  P2SEL1 |= USB_TXD; 
  P2OUT &= ~USB_TXD; 
  P2DIR |= USB_TXD; 
    
  // P2.1 USB_RXD
  P2SEL0 &= ~USB_RXD;
  P2SEL1 |= USB_RXD;
  P2OUT &= ~USB_TXD; 
  P2DIR &= ~USB_RXD;
  
  // P2.2 SPI_SCK
  P2SEL0 &= ~SPI_SCK;
  P2SEL1 |= SPI_SCK;
  P2OUT |= SPI_SCK;
  P2DIR |= SPI_SCK; 
  
  // P2.3 UNKNOWN
  P2SEL0 &= ~UNK_P23;
  P2SEL1 &= ~UNK_P23;
  P2OUT &= ~UNK_P23;
  P2DIR |= UNK_P23;
  P2REN &= ~UNK_P23; 
  
  // P2.4 UNKNOWN
  P2SEL0 &= ~UNK_P24;
  P2SEL1 &= ~UNK_P24;
  P2OUT &= ~UNK_P24;
  P2DIR |= UNK_P24;
  P2REN &= ~UNK_P24;
  
  // P2.5 CPU_TXD
  P2SEL0 &= ~CPU_TXD;
  P2SEL1 |= CPU_TXD;
  P2OUT &= ~CPU_TXD; 
  P2DIR |= CPU_TXD; 
  
  // P2.6 CPU_RXD
  P2SEL0 &= ~CPU_RXD;
  P2SEL1 |= CPU_RXD;
  P2OUT &= ~CPU_RXD;
  P2DIR &= ~CPU_RXD; 
  
  // P2.7 UNKNOWN 
  P2SEL0 &= ~UNK_P27;
  P2SEL1 &= ~UNK_P27;
  P2OUT &= ~UNK_P27;
  P2DIR |= UNK_P27;
  P2REN &= ~UNK_P27; 
}

//***********************************************************************
//      Function name: Init_Port_3 
//      Description: Initializes Port 3
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Init_Port3(void){
  //---------------------------------------------------------------------
  // Pin Name   Function        P3DIR.x P3SEL1.x        P3SEL0.x
  // P3.0       I/0             0/1     0               0
  //            A12             X       1               1
  //            CD12            X       1               1
  // P3.1       I/0             0/1     0               0
  //            A13             X       1               1
  //            CD13            X       1               1
  // P3.2       I/0             0/1     0               0
  //            A14             X       1               1
  //            CD14            X       1               1
  // P3.3       I/0             0/1     0               0
  //            A15             X       1               1
  //            CD15            X       1               1
  // P3.4       I/O             0/1     0               0
  //            TB1.CCI1B       0       0               1
  //            TB1.1           1       0               1
  //            TB2CLK          0       1               1
  //            SMCLK           1       1               1
  // P3.5       I/O             0/1     0               0
  //            TB1.CCI2B       0       0               1
  //            TB1.2           1       0               1
  //            CDOUT           1       1               1
  // P3.6       I/O             0/1     0               0
  //            TB2.CCI1B       0       0               1
  //            TB2.1           1       0               1
  //            TB1CLK          1       1               1
  // P3.7       I/O             0/1     0               0
  //            TB2.CCI2B       0       0               1
  //            TB2.2           1       0               1
  //---------------------------------------------------------------------
  P3SEL0 = CLEAR_REGISTER; 
  P3SEL1 = CLEAR_REGISTER;
  P3OUT = CLEAR_REGISTER; 
  P3DIR = CLEAR_REGISTER;  
  
  // P3.0 X
  P3SEL0 &= ~P3X; 
  P3SEL1 &= ~P3X;
  P3OUT &= ~P3X; 
  P3DIR &= ~P3X; 
  P3REN &= ~P3X; 
  
  // P3.1 Y
  P3SEL0 &= ~P3Y; 
  P3SEL1 &= ~P3Y;
  P3OUT &= ~P3Y; 
  P3DIR &= ~P3Y; 
  P3REN &= ~P3Y;
  
  // P3.2 Z 
  P3SEL0 &= ~P3Z; 
  P3SEL1 &= ~P3Z;
  P3OUT &= ~P3Z;
  P3DIR &= ~P3Z; 
  P3REN &= ~P3Z; 
  
  // P3.3 LCD_BACKLITE
  P3SEL0 &= ~LCD_BACKLITE; 
  P3SEL1 &= ~LCD_BACKLITE;
  P3OUT &= ~LCD_BACKLITE; 
  P3DIR |= LCD_BACKLITE;
  
  // P3.4 R_FORWARD
  P3SEL0 &= ~LED5; 
  P3SEL1 &= ~LED5;
  P3OUT &= ~LED5; 
  P3DIR |= LED5;
  
  // P3.5 R_REVERSE
  P3SEL0 &= ~LED6; 
  P3SEL1 &= ~LED6;
  P3OUT &= ~LED6; 
  P3DIR |= LED6;
  
  // P3.6 L_FORWARD
  P3SEL0 &= ~LED7; 
  P3SEL1 &= ~LED7;
  P3OUT &= ~LED7;
  P3DIR |= LED7;
  
  // P3.7 L_REVERSE 
  P3SEL0 &= ~LED8; 
  P3SEL1 &= ~LED8;
  P3OUT &= ~LED8;
  P3DIR |= LED8;
}

//***********************************************************************
//      Function name: Init_Port_4 
//      Description: Initializes Port 4
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Init_Port4(void){
  //---------------------------------------------------------------------
  // Pin Name   Function        P4DIR.x P4SEL1.x        P4SEL0.x
  // P4.0       I/O             0/1     0               0
  //            TB2.CCI0B       0       0               1
  //            TB2.0           1       0               1
  // P4.1       I/O             0/1     0               0
  //---------------------------------------------------------------------
  // Configure PORT 4
  // Port 4 has only two pins
  // Port 4 Pins
  // SW1 (0x01) // Switch 1
  // SW2 (0x02) // Switch 2
  //---------------------------------------------------------------------
  P4SEL0 = 0x00; // P4 set as I/0
  P4SEL1 = 0x00; // P4 set as I/0
  P4DIR = 0x00; // Set P4 direction to input
  P4OUT = 0x00;
  
  // SW1
  P4SEL0 &= ~SW1; // SW1 set as I/0
  P4SEL1 &= ~SW1; // SW1 set as I/0
  P4OUT |= SW1; // Configure pullup resistor
  P4DIR &= ~SW1; // Direction = input
  P4REN |= SW1; // Enable pullup resistor
  
  // SW2
  P4SEL0 &= ~SW2; // SW2 set as I/0
  P4SEL1 &= ~SW2; // SW2 set as I/0
  P4OUT |= SW2; // Configure pullup resistor
  P4DIR &= ~SW2; // Direction = input
  P4REN |= SW2; // Enable pullup resistor
  
  // Interrupt Configuration
//  P4IES |= SW1; // SW1 Hi/Lo edge interrupt
//  P4IES |= SW2; // SW2 Hi/Lo edge interrupt
 // P4IFG &= ~SW1; // IFG SW1 cleared 
  //P4IFG &= ~SW2; // IFG SW2 cleared 
//  
//  // Enabling Interrupt 
  //P4IE |= SW1;  // SW1 interrupt enabled   
  //P4IE |= SW2;  // SW2 interrupt enabled 
}

//***********************************************************************
//      Function name: Init_Port_J 
//      Description: Initializes Port J
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Init_PortJ(void){
  //----------------------------------------------------------------------
  // Pin Name   Function        PJDIR.x PJSEL1.x        PJSEL0.x
  // PJ.0       I/O             0/1     0               0
  //            TD0             X       X               X
  //            TB0OUTH         0       0               1
  //            SMCLK           1       0               1
  //            CD6             X       1               1
  // PJ.1       I/O             0/1     0               0
  //            TDI/TCLK        X       X               X
  //            TB1OUTH         0       0               1
  //            MCLK            1       0               1
  //            CD7             X       1               1
  // PJ.2       I/O             0/1     0               0
  //            TMS             X       X               X
  //            TB2OUTH         0       0               1
  //            ACLK            1       0               1
  //            CD8             X       1               1
  // PJ.3       I/O             0/1     0               0
  //            TCK             X       X               X
  //            CD9             X       1               1       
  //----------------------------------------------------------------------
  // Port J Pins
  // LED1 (0x01) 
  // LED2 (0x02) 
  // LED3 (0x04) 
  // LED4 (0x08) 
  // XINR (0x10) // XINR
  // XOUTR (0x20) // XOUTR
  //----------------------------------------------------------------------
  PJSEL0 = CLEAR_REGISTER; // PJ set as I/0
  PJSEL1 = CLEAR_REGISTER; // PJ set as I/0
  PJOUT = CLEAR_REGISTER; 
  PJDIR = CLEAR_REGISTER; // Set PJ direction to output
  
  PJSEL0 &= ~IOT_FACTORY;
  PJSEL1 &= ~IOT_FACTORY;
  PJOUT &= ~IOT_FACTORY;
  PJDIR |= IOT_FACTORY; // Set PJ Pin 1 direction to output
  
  PJSEL0 &= ~IOT_WAKEUP;
  PJSEL1 &= ~IOT_WAKEUP;
  PJOUT &= ~IOT_WAKEUP;
  PJDIR |= IOT_WAKEUP; // Set PJ Pin 2 direction to output
  
  PJSEL0 &= ~IOT_STA_MINIAP;
  PJSEL1 &= ~IOT_STA_MINIAP;
  PJOUT &= ~IOT_STA_MINIAP;
  PJDIR |= IOT_STA_MINIAP; // Set PJ Pin 3 direction to output
  
  PJSEL0 &= ~RESET;
  PJSEL1 &= ~RESET;
  PJOUT &= ~RESET;
  PJDIR |= RESET; // Set P3 Pin 4 direction to output
  
  // XT1 Setup
  PJSEL0 |= XINR;
  PJSEL0 |= XOUTR;
  PJOUT &= ~IOT_FACTORY;
  PJOUT |= IOT_WAKEUP;
  PJOUT |= IOT_STA_MINIAP;
  PJOUT &= ~RESET;
}

//***********************************************************************
//      Function name: Init_ADC 
//      Description: Initializes ADC Configuration 
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Init_ADC(void){
   ADC10CTL0 = CLEAR_REGISTER; // Clear ADC10CTL0
   ADC10CTL0 |= ADC10SHT_2;    // 16 ADC clocks
   ADC10CTL0 &= ~ADC10MSC;     // Single Sequence
   ADC10CTL0 |= ADC10ON;       // ADC ON - Core Enabled
   
   ADC10CTL1 = CLEAR_REGISTER; // Clear ADC10CTL1
   ADC10CTL1 |= ADC10SHS_0;    // ADC10SC bit
   ADC10CTL1 |= ADC10SHP;      // SAMPCON signal sourced from sampling timer
   ADC10CTL1 &= ~ADC10ISSH;    // The sample-input signal is not inverted.
   ADC10CTL1 |= ADC10DIV_0;    // ADC10_B clock divider – Divide by 1.
   ADC10CTL1 |= ADC10SSEL_0;   // MODCLK
   ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion
   
   ADC10CTL2 = CLEAR_REGISTER; // Clear ADC10CTL2
   ADC10CTL2 |= ADC10DIV_0;    // Pre-divide by 1
   ADC10CTL2 |= ADC10RES;      // 10-bit resolution
   ADC10CTL2 &= ~ADC10DF;      // Binary unsigned
   ADC10CTL2 &= ~ADC10SR;      // supports up to approximately 200 ksps
   
   ADC10MCTL0 = CLEAR_REGISTER; // Clear ADC10MCTL0
   ADC10MCTL0 |= ADC10SREF_0;  // V(R+) = AVCC and V(R-) = AVSS
   ADC10MCTL0 |= ADC10INCH_3;  // Channel A3 Thumb Wheel
   
   ADC10IE |= ADC10IE0;        // Enable ADC conversion complete interrupt
}