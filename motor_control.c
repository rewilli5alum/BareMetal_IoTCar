//******************************************************************************
//   Name: motor_control.c
//   Author: Rachel E. Williams
//   Date Created: September 9 2015 (9/9/2015)
//   Last Updated: 2/17/2025
//   Description: This file handles motor control for Left and Right motors, 
//                tied to LEDs
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
//      Function name: All_Off
//      Description: Turns off all motors   
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void All_Off(void){
  Left_Forward_Off();
  Right_Forward_Off();
  Left_Reverse_Off();
  Right_Reverse_Off(); 
}

//------------------------------------------------------------------------------
//      Function name: Left_Forward_On
//      Description: Turns on forward motion of left motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Left_Forward_On(void){
  P3OUT |= LED7;
 }

//------------------------------------------------------------------------------
//      Function name: Left_Forward_Off
//      Description: Turns off forward motion of left motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Left_Forward_Off(void){
  P3OUT &= ~LED7;
 }

//------------------------------------------------------------------------------
//      Function name: Left_Reverse_On
//      Description: Turns on reverse motion of left motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Left_Reverse_On(void){
  P3OUT |= LED8;
 }

//------------------------------------------------------------------------------
//      Function name: Left_Reverse_Off
//      Description: Turns off reverse motion of left motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Left_Reverse_Off(void){
  P3OUT &= ~LED8;
 }

//------------------------------------------------------------------------------
//      Function name: Right_Forward_On
//      Description: Turns on forward motion of right motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Right_Forward_On(void){
  P3OUT |= LED5;
}

//------------------------------------------------------------------------------
//      Function name: Right_Forward_Off
//      Description: Turns off forward motion of right motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Right_Forward_Off(void){
  P3OUT &= ~LED5;
}

//------------------------------------------------------------------------------
//      Function name: Right_Reverse_On
//      Description: Turns on reverse motion of right motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Right_Reverse_On(void){
  P3OUT |= LED6;
 }

//------------------------------------------------------------------------------
//      Function name: Right_Reverse_Off
//      Description: Turns off reverse motion of right motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//------------------------------------------------------------------------------
void Right_Reverse_Off(void){
  P3OUT &= ~LED6;
}
