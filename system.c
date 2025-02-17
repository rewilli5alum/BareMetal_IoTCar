//******************************************************************************
//   Name: system.c
//   Author: Rachel E. Williams
//   Date Created: September 9 2015 (9/9/2015)
//   Last Updated: 2/17/2025
//   Description: This file handles system-wide configuration 
//   Originally built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//   Updated revisions built with IAR Embedded Workbench - MSP430 V8.10.3
//******************************************************************************  

// #includes 
#include "msp430.h"
#include "functions.h"

// Global Variables 

// Constant Variables 

//------------------------------------------------------------------------------
// System Configurations
// Description: Tells the compiler to provide the value in reg as an input to an 
//              inline assembly block.  Even though the block contains no 
//              instructions, the compiler may not optimize it away, and is 
//              told that the value may change and should not be relied upon.
//------------------------------------------------------------------------------

/*
inline void READ_AND_DISCARD(unsigned int reg) __attribute__((always_inline));
void READ_AND_DISCARD(unsigned int reg){
  asm volatile ("" : "=m" (reg) : "r" (reg));
}
*/

//inline void enable_interrupts(void) __attribute__((always_inline));
void enable_interrupts(void){
  __bis_SR_register(GIE);              // enable interrupts
//  asm volatile ("eint \n");
}

/*
inline void disable_interrupts(void) __attribute__((always_inline));
void disable_interrupts(void){
//  asm volatile ("dint \n");
}
*/
