//******************************************************************************
//   Name: display.c
//   Author: Rachel E. Williams
//   Date Created: September 9 2015 (9/9/2015)
//   Last Updated: 2/15/2025
//   Description: This file handles displaying information to the LCD
//   Originally built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//   Updated revisions built with IAR Embedded Workbench - MSP430 V8.10.3
//******************************************************************************   

// #includes 
#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

// Global Variables 

// Constant Variables 

//------------------------------------------------------------------------------
//      Function name: Out_To_LCD
//      Description: Holds values for LCD before update  
//      Global variables: NONE
//      Local variables: L1_line[], L1pos, L2_line[], L2pos, 
//                       L3_line[], L3pos, L4_line[], L4pos
//      Return: VOID
//------------------------------------------------------------------------------
void Out_To_LCD(char L1_line[], int L1pos, char L2_line[], int L2pos, 
                char L3_line[], int L3pos, char L4_line[], int L4pos){
  display_1 = L1_line;
  posL1 = L1pos;
  display_2 = L2_line;
  posL2 = L2pos;
  display_3 = L3_line;
  posL3 = L3pos;
  display_4 = L4_line; 
  posL4 = L4pos; 
}

//------------------------------------------------------------------------------
//      Function name: Display_Process
//      Description: Updates display to LCD screen  
//      Global variables: display_1, display_2, display_3, display_4,
//                        LCD_HOME_L1, LCD_HOME_L2, LCD_HOME_L3, 
//                        LCD_HOME_L4, posL1, posL2, posL3, posL4
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Display_Process(void){
  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
 }