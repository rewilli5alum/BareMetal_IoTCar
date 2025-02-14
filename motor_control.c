//***********************************************************************
//      Title: motor_control.c 
//      Description: This file handles control for left and right motors
//      Rachel Williams
//      November 2015
//      Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//***********************************************************************

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

//***********************************************************************
//      Function name: Left_Forward_On
//      Description: Turns on forward motion of left motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Left_Forward_On(void){
  P3OUT |= LED7;
 }

//***********************************************************************
//      Function name: Left_Forward_Off
//      Description: Turns off forward motion of left motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Left_Forward_Off(void){
  P3OUT &= ~LED7;
 }

//***********************************************************************
//      Function name: Left_Reverse_On
//      Description: Turns on reverse motion of left motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Left_Reverse_On(void){
  P3OUT |= LED8;
 }

//***********************************************************************
//      Function name: Left_Reverse_Off
//      Description: Turns off reverse motion of left motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Left_Reverse_Off(void){
  P3OUT &= ~LED8;
 }

//***********************************************************************
//      Function name: Right_Forward_On
//      Description: Turns on forward motion of right motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Right_Forward_On(void){
  P3OUT |= LED5;
}

//***********************************************************************
//      Function name: Right_Forward_Off
//      Description: Turns off forward motion of right motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Right_Forward_Off(void){
  P3OUT &= ~LED5;
}

//***********************************************************************
//      Function name: Right_Reverse_On
//      Description: Turns on reverse motion of right motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Right_Reverse_On(void){
  P3OUT |= LED6;
 }

//***********************************************************************
//      Function name: Right_Reverse_Off
//      Description: Turns off reverse motion of right motor  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void Right_Reverse_Off(void){
  P3OUT &= ~LED6;
}

//***********************************************************************
//      Function name: All_Off
//      Description: Turns off all motors   
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//***********************************************************************
void All_Off(void){
  Left_Forward_Off();
  Right_Forward_Off();
  Left_Reverse_Off();
  Right_Reverse_Off(); 
}