// Function prototypes main
void main(void);
void Init_Conditions(void);
void Switches_Process(void);
void Init_Timers(void);

// ADC prototypes 
void ADC_Process(void);
void ADC_Convert(void);
void Display_Char(char num);
void Detection(void);
void Calibration(void);

// Function prototypes clocks
void Init_Clocks(void);
void Five_Msec_Delay(unsigned int fivemsec); 
void X_Seconds_Delay(unsigned int sec);

// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
__interrupt void TIMER2_B1_ISR(void);
__interrupt void Timer0_A0_ISR(void);
__interrupt void TIMER0_A1_ISR(void); 
__interrupt void switch_interrupt(void);
void Init_Timer_A0(void);
void Init_Timer_B2(void);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(void);
void Init_ADC(void);

// LCD
void Init_LCD(void);
void WriteIns(char instruction);
void WriteData(char data);
void ClrDisplay(void);
void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void Display_Process(void);
void Menu_Display(int itemNumber);
void Out_To_LCD(char L1_line[], int L1pos, char L2_line[], int L2pos, 
                char L3_line[], int L3pos, char L4_line[], int L4pos);

// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);

// Motors
void Left_Forward_On(void);
void Left_Forward_Off(void);
void Left_Reverse_On(void);
void Left_Reverse_Off(void);
void Right_Forward_On(void);
void Right_Forward_Off(void);
void Right_Reverse_On(void);
void Right_Reverse_Off(void);
void All_Off(void);

// Transmission/Receive 
void Init_Port_Coms(void);
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void); 
__interrupt void USCI_A0_ISR(void);
__interrupt void USCI_A1_ISR(void);

// Conversions 
void Convert_H2I(void);

// IOT 
void IOT_config(void);
void IOT_home(void);
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
void Roam(void);
void Check_Status(void);
void Ping(void);
void Listen(void);
int Check_Str(void);
void Reconnect(void);
void Socket(void);