//******************************************************************************
//      Title: IOT.c
//      Description: This file handles interaction with IOT 
//      Rachel Williams
//      November 2015
//      Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

//******************************************************************************
//      Function name: IOT_config
//      Description: Configuration for IOT device on ncsu wifi  
//      Global variables: IOT_Char_Rx[]
//      Local variables: i,j,k 
//      Return: VOID
//******************************************************************************
void IOT_config(void){
  int i = POSIT_0;
  
  Out_To_LCD(" ",POSIT_0," ",POSIT_0," ",POSIT_0," ",POSIT_0);
  lcd_4line();
  Display_Process(); 
  Five_Msec_Delay(20); 
  
  //----------Set SSID---------------------------------------------------------- 
  Set_SSID(); 
  
  // Waiting until "OK" is received 
  while(IOT_Char_Rx[i] != 'O')i++;
  i = POSIT_0;
  X_Seconds_Delay(POSIT_1);
  
  //----------Get SSID----------------------------------------------------------
  Get_SSID(); 
  
  // Waiting until "OK" is received 
  while(IOT_Char_Rx[i] != 'O')i++;
  i = POSIT_0;
  X_Seconds_Delay(POSIT_1);
    
  //----------Set host name----------------------------------------------------- 
  Set_HostN(); 
  
  // Waiting until "OK" is received 
  while(IOT_Char_Rx[i] != 'O')i++;
  i = POSIT_0;
  X_Seconds_Delay(POSIT_1);
  
  //----------Get host name-----------------------------------------------------
  Get_HostN(); 
  
  // Waiting until "OK" is received 
  while(IOT_Char_Rx[i] != 'O')i++;
  i = POSIT_0;
  X_Seconds_Delay(POSIT_1);
  
  //----------Set network privacy mode------------------------------------------
  Set_NetP(); 
  
  // Waiting until "OK" is received 
  while(IOT_Char_Rx[i] != 'O')i++;
  i = POSIT_0;
  X_Seconds_Delay(POSIT_1);
  
  //----------Get network privacy mode------------------------------------------ 
  Get_NetP(); 
  
  // Waiting until "OK" is received 
  while(IOT_Char_Rx[i] != 'O')i++;
  i = POSIT_0;
  X_Seconds_Delay(POSIT_1);
  
  //----------Set network mode-------------------------------------------------- 
  Set_NetM(); 
  
  // Waiting until "OK" is received 
  while(IOT_Char_Rx[i] != 'O')i++;
  i = POSIT_0;
  X_Seconds_Delay(POSIT_1); 
  
  //----------Get network mode-------------------------------------------------- 
  Get_NetM(); 
  
  // Waiting until "OK" is received 
  while(IOT_Char_Rx[i] != 'O')i++;
  i = POSIT_0;
  X_Seconds_Delay(POSIT_1); 
  
  //----------Save settings on flash module-------------------------------------
  Save_All(); 
  
  // Waiting until "OK" is received 
  while(IOT_Char_Rx[i] != 'O')i++;
  i = POSIT_0;
  X_Seconds_Delay(POSIT_1); 
  
  //----------Reset module------------------------------------------------------
  Reconnect(); 
  
  //---------Ping lab computer-------------------------------------------------- 
  Ping(); 
  cpu_rx_ring_wr = POSIT_0;
  i = POSIT_0;
  X_Seconds_Delay(POSIT_1);
  
  // Waiting until "OK" has been received 
  i = POSIT_0;
  while(IOT_Char_Rx[i] != 'O')i++; 
  X_Seconds_Delay(POSIT_1);
  i = POSIT_0;
  
  //---------Opening Socket-Server Connection-----------------------------------
  Socket(); 
  
  // Waiting until "OK" has been received 
  i = POSIT_0;
  while(IOT_Char_Rx[i] != 'O')i++; 
  X_Seconds_Delay(POSIT_1);
  i = POSIT_0;
  
  while(!i){
    if (!(P4IN & SW2)){
      i = POSIT_1; 
      Switches_Process(); 
    }
  }
}

//******************************************************************************
//      Function name: Listen
//      Description: Configuration for IOT device on ncsu wifi  
//      Global variables: IOT_Char_Rx
//      Local variables: inc, i, j, time, t, result
//      Return: VOID
//******************************************************************************
void Listen(void){
  int inc = POSIT_0;
  char j = '1'; 
  unsigned int t; 
  _Bool result = POSIT_0;
  
  while(!result){
    // Checks if command sequence identifier is seen. If seen, returns 1, else 0
    result = Check_Str();
  }
  
  Out_To_LCD("Waiting",POSIT_0,"For",POSIT_0,"Input...",POSIT_0," ",POSIT_0);
  Display_Process();
  Five_Msec_Delay(BIG_DELAY);
  
  // Continue to listen unless SW2 is pressed
  while(P4IN & SW2){
    
    // Turns off all motors (precaution) 
    All_Off(); 
    
    // re-initializing receive buffer
    for(int j1=POSIT_0; j1<SMALL_RING_SIZE; j1++)IOT_Char_Rx[j1]='1';
    
    // default driving time for each command 
    t = 65;
    
    // re-initializing variables 
    j = '1'; 
    inc = POSIT_0; 
    
    // going through array to find appropriate driving commands 
    j = IOT_Char_Rx[inc];
    
    switch(j){
      
    //---------Forward motion--------------------------------------------------- 
    case 'W': 
      Out_To_LCD(" ",POSIT_0,"Forward",POSIT_0," ",POSIT_0," ",POSIT_0);
      Display_Process();
      
      // Reset timer for timer interrupt 
      Time_Sequence = POSIT_0;
      
      // Count up to time unit 
      while(Time_Sequence < t){  
        Left_Forward_On();
        Right_Forward_On();
      }
      
      // Turning off after reached time unit 
      Left_Forward_Off();
      Right_Forward_Off();
      break; 
      
    //---------Reverse motion--------------------------------------------------- 
    case 'S':  
      Out_To_LCD(" ",POSIT_0,"Reverse",POSIT_0," ",POSIT_0," ",POSIT_0);
      Display_Process();
      
      // Reset timer for timer interrupt
      Time_Sequence = POSIT_0;
      
      // Count up to time unit
      while(Time_Sequence < t){
        Left_Reverse_On();
        Right_Reverse_On();
      }
      
      // Turning off after reached time unit
      Left_Reverse_Off();
      Right_Reverse_Off();
      break; 
      
    //---------Clockwise motion-------------------------------------------------  
    case 'D': 
      Out_To_LCD(" ",POSIT_0,"CW",POSIT_0," ",POSIT_0," ",POSIT_0);
      Display_Process();
      
      // Reset timer for timer interrupt
      Time_Sequence = POSIT_0;
      
      // Count up to time unit
      while(Time_Sequence < t){
        Left_Forward_On();
        Right_Reverse_On();
      }
      
      // Turning off after reached time unit
      Left_Forward_Off();
      Right_Reverse_Off();
      break; 
      
    //---------Counterclockwise motion------------------------------------------        
    case 'A':  
      Out_To_LCD(" ",POSIT_0,"CCW",POSIT_0," ",POSIT_0," ",POSIT_0);
      Display_Process();
      
      // Reset timer for timer interrupt
      Time_Sequence = POSIT_0;
      
      // Count up to time unit
      while(Time_Sequence < t){
        Left_Reverse_On();
        Right_Forward_On();
      }
      // Turning off after reached time unit
      Left_Reverse_Off();
      Right_Forward_Off();
      break; 
      
    //--------Left Turn (forward)-----------------------------------------------       
    case 'Q':  
      Out_To_LCD(" ",POSIT_0,"Left",POSIT_0,"Turn",POSIT_0," ",POSIT_0);
      Display_Process();
      
      // Reset timer for timer interrupt
      Time_Sequence = POSIT_0;
      
      // Count up to time unit
      while(Time_Sequence < t){
        Right_Forward_On();
      }
      // Turning off after reached time unit
      Right_Forward_Off();
      break; 
      
    //---------Right Turn (forward)---------------------------------------------        
    case 'E': 
      Out_To_LCD(" ",POSIT_0,"Right",POSIT_0,"Turn",POSIT_0," ",POSIT_0);
      Display_Process();
      
      // Reset timer for timer interrupt
      Time_Sequence = POSIT_0;
      
      // Count up to time unit
      while(Time_Sequence < t){
        Left_Forward_On();
      }
      // Turning off after reached time unit
      Left_Forward_Off();
      break; 
      
    //---------Left Turn (backward)---------------------------------------------        
    case 'Z': 
      Out_To_LCD(" ",POSIT_0,"Left",POSIT_0,"Turn",POSIT_0,"R",POSIT_0);
      Display_Process();
      
      // Reset timer for timer interrupt
      Time_Sequence = POSIT_0;
      
      // Count up to time unit
      while(Time_Sequence < t){
        Right_Reverse_On();
      }
      // Turning off after reached time unit
      Right_Reverse_Off();
      break; 
      
    //---------Right Turn (backward)--------------------------------------------
    case 'C': // Turn reverse right
      Out_To_LCD(" ",POSIT_0,"Right",POSIT_0,"Turn",POSIT_0,"R",POSIT_0);
      Display_Process();
      
      // Reset timer for timer interrupt
      Time_Sequence = POSIT_0;
      
      // Count up to time unit
      while(Time_Sequence < t){
        Left_Reverse_On();
      }
      // Turning off after reached time unit
      Left_Reverse_Off();
      break; 
    default: break; 
    }
    
    if(inc == (SMALL_RING_SIZE-POSIT_1)){
      inc = POSIT_0;
    }else{
      inc++;
    } 
  }
}

//*****************************************************************************
//      Function name: Set_SSID 
//      Description: Setting SSID 
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Set_SSID(void){
  int i = POSIT_0;
  char sSSID[SMALL_RING_SIZE] = "AT+S.SSIDTXT=ncsu\r"; 
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Updating display 
  Out_To_LCD("Set SSID", POSIT_0, "", POSIT_0, "", POSIT_0, "", POSIT_0); 
  Display_Process();
  
  // Transmitting commands
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = sSSID[i]; 
    if(sSSID[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
}

//*****************************************************************************
//      Function name: Get_SSID
//      Description: Getting SSID 
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Get_SSID(void){
  int i = POSIT_0;
  char gSSID[SMALL_RING_SIZE] = "AT+S.SSIDTXT\r"; 
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Updating display 
  Out_To_LCD("Get SSID", POSIT_0, "", POSIT_0, "", POSIT_0, "", POSIT_0); 
  Display_Process();
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = gSSID[i]; 
    if(gSSID[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_2);
}

//*****************************************************************************
//      Function name: Set_HostN
//      Description: Sets host name 
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Set_HostN(void){
  int i = POSIT_0;
  char sHostN[SMALL_RING_SIZE] = "AT+S.SCFG=ip_hostname,ECE-306_02_R\r";
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Updating display 
  Out_To_LCD("Set", POSIT_0, "hostname", POSIT_0, "", POSIT_0, "", POSIT_0); 
  Display_Process();
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = sHostN[i]; 
    if(sHostN[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
} 

//*****************************************************************************
//      Function name: Get_HostN
//      Description: Gets host name 
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Get_HostN(void){
  int i = POSIT_0;
  char gHostN[SMALL_RING_SIZE] = "AT+S.SCFG=ip_hostname\r";  
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Updating display 
  Out_To_LCD("Get", POSIT_0, "hostname", POSIT_0, "", POSIT_0, "", POSIT_0); 
  Display_Process();
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = gHostN[i]; 
    if(gHostN[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
}

//*****************************************************************************
//      Function name: Set_NetP
//      Description: Setting network privacy mode 
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Set_NetP(void){
  int i = POSIT_0;
  char sNetP[SMALL_RING_SIZE] = "AT+S.SCFG=wifi_priv_mode,0\r";
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Updating display 
  Out_To_LCD("Set", POSIT_0, "network", POSIT_0, "privacy", POSIT_0, "", POSIT_0); 
  Display_Process();
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = sNetP[i]; 
    if(sNetP[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
} 

//*****************************************************************************
//      Function name: Get_NetP
//      Description: Get network privacy mode  
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Get_NetP(void){
  int i = POSIT_0;
  char gNetP[SMALL_RING_SIZE] = "AT+S.SCFG=wifi_priv_mode\r";
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Updating display 
  Out_To_LCD("Get", POSIT_0, "network", POSIT_0, "privacy", POSIT_0, "", POSIT_0); 
  Display_Process();
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = gNetP[i]; 
    if(gNetP[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
} 

//*****************************************************************************
//      Function name: Set_NetM
//      Description: Setting network mode 
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Set_NetM(void){
  int i = POSIT_0;
  char sNetM[SMALL_RING_SIZE] = "AT+S.SCFG=wifi_mode,1\r";
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Updating display 
  Out_To_LCD("Set", POSIT_0, "network", POSIT_0, "mode", POSIT_0, "", POSIT_0); 
  Display_Process();
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = sNetM[i]; 
    if(sNetM[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
} 

//*****************************************************************************
//      Function name: Get_NetM
//      Description: Getting network mode 
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Get_NetM(void){
  int i = POSIT_0;
  char gNetM[SMALL_RING_SIZE] = "AT+S.SCFG=wifi_mode\r";
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Updating display 
  Out_To_LCD("Get", POSIT_0, "network", POSIT_0, "mode", POSIT_0, "", POSIT_0); 
  Display_Process();
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = gNetM[i]; 
    if(gNetM[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
} 

//*****************************************************************************
//      Function name: Save_All
//      Description: Save the settings on the flash memory   
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Save_All(void){
  int i = POSIT_0;
  char save[SMALL_RING_SIZE] = "AT&W\r";
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Updating display 
  Out_To_LCD("Save", POSIT_0, "settings", POSIT_0, "", POSIT_0, "", POSIT_0); 
  Display_Process();
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = save[i]; 
    if(save[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
} 

//*****************************************************************************
//      Function name: Reset_All 
//      Description: Resets the module 
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Reset_All(void){
  int i = POSIT_0;
  char reset[SMALL_RING_SIZE] = "AT+CFUN=1\r";
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Updating display 
  Out_To_LCD("Reset", POSIT_0, "module", POSIT_0, "", POSIT_0, "", POSIT_0); 
  Display_Process();
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = reset[i]; 
    if(reset[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
} 

//*****************************************************************************
//      Function name: Roam
//      Description: Sets up roaming for wifi 
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Roam(void){
  int i = POSIT_0;
  char roam[SMALL_RING_SIZE] = "AT+S.ROAM\r";
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Updating display 
  Out_To_LCD("Roaming...", POSIT_0, "", POSIT_0, "", POSIT_0, "", POSIT_0); 
  Display_Process();
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = roam[i]; 
    if(roam[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
}

//*****************************************************************************
//      Function name: Check_Status
//      Description: Gets ip address  
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Check_Status(void){
  int i = POSIT_0;
  char check[SMALL_RING_SIZE] = "AT+S.STS=ip_ipaddr\r";
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = check[i]; 
    if(check[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
}

//*****************************************************************************
//      Function name: Ping
//      Description: Pings lab computer   
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Ping(void){
  int i = POSIT_0;
  char ping[SMALL_RING_SIZE] = "AT+S.PING= 152.14.99.126\r";
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = ping[i]; 
    if(ping[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
}

//*****************************************************************************
//      Function name: Check_Str
//      Description: Checks to see if string is allowed to be received  
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
int Check_Str(void){
  int inc = POSIT_0; 
  int i = POSIT_0;
  char pin[POSIT_4];
  
  Out_To_LCD(" ",POSIT_0,"Checking",POSIT_0,"Pin...",POSIT_0," ",POSIT_0);
  lcd_4line();
  Display_Process();
  X_Seconds_Delay(POSIT_1);
  
  // Pin to be recognized 
  pin[POSIT_0] = '0';
  pin[POSIT_1] = '1';
  pin[POSIT_2] = '2';
  pin[POSIT_3] = '4';
  
  Five_Msec_Delay(BIG_DELAY); 
  
  // Checking for '*'
  while(ALWAYS){
    if(IOT_Char_Rx[inc] == '*')break; 
    if(inc >= SMALL_RING_SIZE)inc=POSIT_0;
    inc++;
  }
  inc = POSIT_0;
  
  // Examining for unique pin
  Five_Msec_Delay(BIG_DELAY); 
  while(ALWAYS){
    if(i)break;
    if(inc >= SMALL_RING_SIZE)inc=POSIT_0;
    if(IOT_Char_Rx[inc] == pin[POSIT_0]){
      if(IOT_Char_Rx[inc+POSIT_1] == pin[POSIT_1]){
        if(IOT_Char_Rx[inc+POSIT_2] == pin[POSIT_2]){
          if(IOT_Char_Rx[inc+POSIT_3] == pin[POSIT_3]){
            i = ALWAYS;
          }
        }
      }
    }
    inc++;
  }
  Out_To_LCD(" ",POSIT_0,"Pin",POSIT_0,"Approved",POSIT_0," ",POSIT_0);
  lcd_4line();
  Display_Process();
  X_Seconds_Delay(POSIT_1);
  return i; 
}

//*****************************************************************************
//      Function name: Reconnect
//      Description: Reconnects to Wifi   
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Reconnect(void){
    int i; 
    int j; 
    int k; 
    Reset_All();
  
  // Reset, delayed for one second, brought back
  PJOUT |= RESET;
  X_Seconds_Delay(POSIT_1); 
  PJOUT &= ~RESET;
  
  // Another 1 second delay, then re-initialize LCD 
  X_Seconds_Delay(POSIT_1); 
  Init_LCD(); 
  
  // Clearing LCD 
  Out_To_LCD("Reset", POSIT_0, "Complete", POSIT_0, "", POSIT_0, "", POSIT_0); 
  Display_Process();
  X_Seconds_Delay(POSIT_2);
  
  //----------Connecting to network---------------------------------------------
  Out_To_LCD("Connecting", POSIT_0, "to", POSIT_0, "network...", POSIT_0, "",
             POSIT_0);
  Display_Process();
  Five_Msec_Delay(FITTY); 
  
  // Checking if connection is successful by looking out for "Handshake" 
  i = POSIT_0;
  cpu_rx_ring_wr = POSIT_0;
  while(ALWAYS){
    if(i)break; 
    if(IOT_Char_Rx[cpu_rx_ring_wr]== 'H'){
      if(IOT_Char_Rx[cpu_rx_ring_wr+POSIT_1]== 'a'){
        if(IOT_Char_Rx[cpu_rx_ring_wr+POSIT_2]== 'n'){
          i = ALWAYS;
        }
      }
    }
  }
    
  Out_To_LCD("Successful", POSIT_0, "connection", POSIT_0, "", POSIT_0, "",
             POSIT_0);
  Display_Process(); 
  X_Seconds_Delay(POSIT_2);
  
  //----------Roaming----------------------------------------------------------- 
  //  Roam(); 
  //  Five_Msec_Delay(POSIT_10);
  
  //---------Get SSID and display to LCD----------------------------------------
  Get_SSID(); 
  cpu_rx_ring_wr = POSIT_0;
  i = POSIT_0;
  X_Seconds_Delay(POSIT_1);
  
  // Parsing through Rx array until "ncsu" is reached 
  while(ALWAYS){
    if(i)break;
    
    // Finds "u" first and then backtracks to "n"
    if(IOT_Char_Rx[cpu_rx_ring_wr] == 'u'){
      if(IOT_Char_Rx[cpu_rx_ring_wr - POSIT_1] == 's'){
        i = ALWAYS;
      }
    }
    // Keeping value of IOT_Char_Rx counter 
    k = cpu_rx_ring_wr;
    cpu_rx_ring_wr++;
  }
  
  // Output SSID to LCD 
  display_1[POSIT_0] = ' '; 
  display_1[POSIT_1] = ' ';
  display_1[POSIT_2] = ' ';
  display_1[POSIT_3] = IOT_Char_Rx[k-POSIT_3];
  display_1[POSIT_4] = IOT_Char_Rx[k-POSIT_2];
  display_1[POSIT_5] = IOT_Char_Rx[k-POSIT_1];
  display_1[POSIT_6] = IOT_Char_Rx[k];
  display_1[POSIT_7] = ' ';
  display_1[POSIT_8] = ' ';
  display_1[POSIT_9] = ' ';
  Display_Process();
  
  // Re-initializing values 
  cpu_rx_ring_wr = POSIT_0;
  k = POSIT_0;
  Five_Msec_Delay(BIG_DELAY);
  
  
  //---------Get ip address-----------------------------------------------------
  display_2 = "          ";
  display_2[POSIT_0] = ' '; 
  display_2[POSIT_1] = ' ';
  display_2[POSIT_2] = 'i';
  display_2[POSIT_3] = 'p';
  display_2[POSIT_4] = 'a';
  display_2[POSIT_5] = 'd';
  display_2[POSIT_6] = 'd';
  display_2[POSIT_7] = 'r';
  display_2[POSIT_8] = ' ';
  display_2[POSIT_9] = ' ';
  Display_Process(); 
  X_Seconds_Delay(POSIT_2);
  
  // Function to get ip address 
  Check_Status(); 
  Five_Msec_Delay(BOOT_DELAY);
  
  // Reset ring buffer increment 
  cpu_rx_ring_wr = POSIT_0;
  i = POSIT_0;
  
  // Disabling RX interrupt
  UCA1IE &= ~UCRXIE;             
  
  // Parsing through Rx array until ip_addr is reached 
  while(ALWAYS){
    if(i)break; 
    if(IOT_Char_Rx[cpu_rx_ring_wr] == 'i'){
      if(IOT_Char_Rx[cpu_rx_ring_wr+POSIT_1] == 'p'){
        if(IOT_Char_Rx[cpu_rx_ring_wr+POSIT_2] == 'a'){
          i = ALWAYS; 
          j = cpu_rx_ring_wr; 
          Display_Process(); 
          Five_Msec_Delay(WAIT_TIME);
        }
      } 
    }
    cpu_rx_ring_wr++;
  }
  cpu_rx_ring_wr = POSIT_0;
  
  // Offset increment by 9 to get to start of ip address (from ip_addr) in array 
  k = j + POSIT_9;
  
  // Clearing array to prepare for new data 
  for(int inc=POSIT_0; inc<=POSIT_9; inc++)display_3[inc] = ' '; 
  Display_Process(); 
  X_Seconds_Delay(POSIT_2);
  
  // Output ip address to LCD 
  display_3[POSIT_0] = ' '; 
  display_3[POSIT_1] = ' ';
  display_3[POSIT_2] = IOT_Char_Rx[k];
  display_3[POSIT_3] = IOT_Char_Rx[k+POSIT_1];
  display_3[POSIT_4] = IOT_Char_Rx[k+POSIT_2];
  display_3[POSIT_5] = IOT_Char_Rx[k+POSIT_3];
  display_3[POSIT_6] = IOT_Char_Rx[k+POSIT_4];
  display_3[POSIT_7] = IOT_Char_Rx[k+POSIT_5];
  display_3[POSIT_8] = ' ';
  display_3[POSIT_9] = ' '; 
  Display_Process();
  X_Seconds_Delay(POSIT_2); 
  Five_Msec_Delay(BIG_DELAY);
  
  display_4 = "          ";
  display_4[POSIT_0] = ' '; 
  display_4[POSIT_1] = ' ';
  display_4[POSIT_2] = IOT_Char_Rx[k+POSIT_6];
  display_4[POSIT_3] = IOT_Char_Rx[k+POSIT_7];
  display_4[POSIT_4] = IOT_Char_Rx[k+POSIT_8];
  display_4[POSIT_5] = IOT_Char_Rx[k+POSIT_9];
  display_4[POSIT_6] = IOT_Char_Rx[k+POSIT_10];
  display_4[POSIT_7] = IOT_Char_Rx[k+POSIT_11];
  display_4[POSIT_8] = IOT_Char_Rx[k+POSIT_12];
  display_4[POSIT_9] = ' ';
  Display_Process();
  
  // Re-enable RX interrupt
  UCA1IE |= UCRXIE;                 
  Five_Msec_Delay(BIG_DELAY);
  
  // Waiting until "OK" has been received 
  i = POSIT_0;
  while(IOT_Char_Rx[i] != 'O')i++; 
}

//*****************************************************************************
//      Function name: Socket
//      Description: Socket-Server connection    
//      Global variables: 
//      Local variables:  
//      Return: VOID
//*****************************************************************************
void Socket(void){
  int i = POSIT_0;
  char socket[SMALL_RING_SIZE] = "AT+S.SOCKD=9001\r";
  
  // initializing receive buffer
  for(int j=POSIT_0; j<SMALL_RING_SIZE; j++)IOT_Char_Rx[j]=POSIT_0;
  
  // Transmitting commands 
  while(ALWAYS){
    UCA1TXBUF = UCA0TXBUF = socket[i]; 
    if(socket[i] == CAR_RET)break; 
    Five_Msec_Delay(POSIT_1); 
    i++;
  }
  Five_Msec_Delay(POSIT_5);
}