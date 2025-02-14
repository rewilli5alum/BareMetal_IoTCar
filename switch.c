//******************************************************************************
//      Title: switch.c 
//      Description: This file contains code for handling switches 
//      Rachel Williams
//      September 2015
//      Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

//******************************************************************************
//      Function name: Switches_Process
//      Description: Handles cases for SW1 and SW2  
//      Global variables: NONE
//      Local variables: NONE
//      Return: VOID
//******************************************************************************
void Switches_Process(void){
  if (!(P4IN & SW1)){ 
    // menu type is a variable that determines which menu is called 
    switch(menu_type){
    case POSIT_1: 
      Five_Msec_Delay(POSIT_1);
      IOT_config();
      break; 
    case POSIT_2:
      Five_Msec_Delay(POSIT_1);
      Listen();   
      break; 
    case POSIT_3: 
      Five_Msec_Delay(POSIT_1); 
      Reconnect(); 
      break; 
    default: break; 
    }
  }
  if (!(P4IN & SW2)) {
    lcd_BIG_mid(); 
    Out_To_LCD(" ",POSIT_0," ",POSIT_0," ",POSIT_0," ",POSIT_0);
    Display_Process(); 
    Five_Msec_Delay(20); 
    
    while((P4IN & SW1)){
      lcd_BIG_mid();
      
      // going through ADC process to update thumb wheel 
      ADC_Process();ADC_Process();ADC_Process();
      
      if(ADC_Thumb <= (TEN23/POSIT_3)){
        // displaying menu item 
        Out_To_LCD("Reset",POSIT_2,"IOT NCSU",POSIT_1,"Listen",POSIT_2," ",POSIT_0); 
        Display_Process();
        menu_type = POSIT_1;
      } else if(ADC_Thumb <= ((TEN23/POSIT_3)*POSIT_2)){
        Out_To_LCD("IOT Ncsu",POSIT_1,"LISTEN",POSIT_2,"Reset",POSIT_2," ",POSIT_0); 
        Display_Process(); 
        menu_type = POSIT_2;
      } else if(ADC_Thumb <= ((TEN23/POSIT_3)*POSIT_3)){
        Out_To_LCD("Listen",POSIT_2,"RESET",POSIT_2,"IOT Ncsu",POSIT_1," ",POSIT_0); 
        Display_Process(); 
        menu_type = POSIT_3;
      }
    }  
  }
}     