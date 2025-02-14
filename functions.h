//******************************************************************************
//   Name: functions.h
//   Author: Rachel E. Williams
//   Date Created: September 9 2015 (9/9/2015)
//   Last Updated: 2/14/2025
//   Description: This file contains all function declarations (prototypes) used 
//                across the entire project 
//   
//******************************************************************************   

//------------------------------------------------------------------------------
//                               MAIN.C 
//------------------------------------------------------------------------------
void ADC_Process(void);
void Switches_Process(void);
void Init_Conditions(void);
void Init_Timers(void);
void Init_Clocks(void);
void Init_Ports(void);
void Init_LCD(void);
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void); 

//------------------------------------------------------------------------------
//                               DISPLAY.C 
//------------------------------------------------------------------------------
void ClrDisplay(void);
void lcd_out(char *s, char line, char position);

//------------------------------------------------------------------------------
//                               INIT.C 
//------------------------------------------------------------------------------
void enable_interrupts(void);
void Init_Timer_A0(void);
void Init_Timer_B2(void);

//------------------------------------------------------------------------------
//                               IOT.C 
//------------------------------------------------------------------------------
void X_Seconds_Delay(unsigned int sec);
void lcd_4line(void);
void Left_Forward_On(void);
void Left_Forward_Off(void);
void Left_Reverse_On(void);
void Left_Reverse_Off(void);
void Right_Forward_On(void);
void Right_Forward_Off(void);
void Right_Reverse_On(void);
void Right_Reverse_Off(void);
void All_Off(void);
void IOT_config(void);
void Set_SSID(void);
void Get_SSID(void); 
void Set_HostN(void); 
void Get_HostN(void); 
void Set_NetP(void); 
void Get_NetP(void); 
void Set_NetM(void); 
void Get_NetM(void); 
void Save_All(void); 
void Reset_All(void); 
void Check_Status(void);
void Ping(void);
int Check_Str(void);
void Reconnect(void);
void Socket(void);

//------------------------------------------------------------------------------
//                               PORTS.C 
//------------------------------------------------------------------------------
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(void);
void Init_ADC(void);

//------------------------------------------------------------------------------
//                               SWITCH.C 
//------------------------------------------------------------------------------
void Five_Msec_Delay(unsigned int fivemsec); 
void lcd_BIG_mid(void);
void Display_Process(void);
void Out_To_LCD(char L1_line[], int L1pos, char L2_line[], int L2pos, 
                char L3_line[], int L3pos, char L4_line[], int L4pos);
void Listen(void);
