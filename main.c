
sbit LCD_RS at RC6_bit;
sbit LCD_EN at RC7_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB1_bit;

sbit LCD_RS_Direction at TRISC6_bit;
sbit LCD_EN_Direction at TRISC7_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB1_bit;


sbit SDA1 at RA2_bit;                 
sbit SCL1 at RA3_bit;                 
sbit SDA1_Direction at TRISA2_bit;
sbit SCL1_Direction at TRISA3_bit;

sbit SIG at RA1_bit;              
sbit ADJ at RA0_bit;  
sbit SIG_Direction at TRISA1_bit;
sbit ADJ_Direction at TRISA0_bit;   

sbit WS1 at RC0_bit;              
sbit HT1 at RC1_bit;
sbit LA at RC2_bit;
sbit WS1_Direction at TRISC0_bit;
sbit HT1_Direction at TRISC1_bit; 
sbit LA_Direction at TRISC2_bit; 

#include"Fuzzy.h"
#include"FuzzyComposition.h"
#include"FuzzyRuleAntecedent.h"
#include"FuzzyRuleConsequent.h"
#include"pic16f877.h"

const unsigned int C1 = 205;  
const unsigned int C2 = 367;  
const unsigned short C3 = 16; 

const unsigned int T1 = 1000; 
const unsigned int T2 = 8;    


const unsigned int D1 = 4010;            
const unsigned short D2 = 1;             

unsigned short i, j, Select;
long int temp, k, SOt, SOrh, Tmp_res, Rh_res;
char *Tmp = "000.0  ";
char *Rh = "00.0 ";

void SHT_Reset() {
  if(Select == 1) {
  SCL1 = 0;                              
  SDA1_Direction = 1;                    
  for (i = 1; i <= 20; i++)              
    SCL1 = ~SCL1;                        
  }
  if(Select == 2) {
  SCL2 = 0;                              
  SDA2_Direction = 1;                    
  for (i = 1; i <= 10; i++)              
    SCL2 = ~SCL2;                        
  }
  }


void Transmission_Start() {
  if(Select == 1){
  SDA1_Direction = 1;                    
  SCL1 = 1;                              
  Delay_1us();                           
  SDA1_Direction = 0;                    
  SDA1 = 0;                              
  Delay_1us();                           
  SCL1 = 0;                              
  Delay_1us();                           
  SCL1 = 1;                              
  Delay_1us();                           
  SDA1_Direction = 1;                    
  Delay_1us();                           
  SCL1 = 0;                              
  }

  if(Select == 2){
  SIG_Direction = 1;                     
  SIG = 1;                               
  Delay_1us();                      
                                                    
  SIG = 0;                              
  Delay_1us();                           
                      
  SIG_Direction = 1;                    
  Delay_1us();                                                      
  }
  
   if(Select == 3){
  ADJ_Direction = 1;                     
  ADJ = 1;                               
  Delay_1us();                      
                                                    
  ADJ = 0;                              
  Delay_1us();                           
                      
  ADJ_Direction = 1;                    
  Delay_1us();                                                      
  }
}


void MCU_ACK() {

  if(Select == 1){
  SDA1_Direction = 0;     
  SDA1 = 0;               
  SCL1 = 1;               
  Delay_1us();           
  SCL1 = 0;              
  Delay_1us();           
  SDA1_Direction = 1;     
  }
  if(Select == 2){
  SIG_Direction = 0;     
  SIG = 0;                             
  Delay_1us();           
          
  SIG_Direction = 1;    
  }
  if(Select == 3){
  ADJ_Direction = 0;     
  ADJ = 0;                             
  Delay_1us();           
          
  ADJ_Direction = 1;    
  }
}

long int Measure(short command) {
  j = command;                   
  SHT_Reset();                   
  Transmission_Start();          
  k = 0;   
  if(Select == 1){
   SDA1_Direction = 0;          
   SCL1 = 0;                    
   for(i = 1; i <= 8; i++) {    
    if (j.F7 == 1)              
     SDA1_Direction = 1;        
    else {                      
     SDA1_Direction = 0;        
     SDA1 = 0;                        
   }
    Delay_1us();                     
    SCL1 = 1;                        
    Delay_1us();                     
    SCL1 = 0;                        
    j <<= 1;                         
	}

   SDA1_Direction = 1;     
   SCL1 = 1;               
   Delay_1us();            
   SCL1 = 0;               
   Delay_1us();            
   while (SDA1 == 1)       
    Delay_1us();                     

  for (i = 1; i <=16; i++) {         
    k <<= 1;                         
    SCL1 = 1;                         
    if (SDA1 == 1)                    
    k = k | 0x0001;
    SCL1 = 0;
    if (i == 8)                      
      MCU_ACK();                     
   }
  }

    if(Select == 2){
   SIG_Direction = 0;               
                           
   for(i = 1; i <= 8; i++) {          
    if (j.F7 == 1)                   
     SIG_Direction = 1;             
    else {                           
     SIG_Direction = 0;             
     SIG = 0;                        
   }
    Delay_1us();                                           
    j <<= 1;                        
   }

   SIG_Direction = 1;                                  
   Delay_1us();                                           
   while (SIG == 1)                  
    Delay_1us();                     

  for (i = 1; i <=16; i++) {          
    k <<= 1;                                                
    if (SIG == 1)                    
    k = k | 0x0001;
    if (i == 8)                      
      MCU_ACK();                     
   }
  }
  
   if(Select == 3){
   ADJ_Direction = 0;               
                           
   for(i = 1; i <= 8; i++) {          
    if (j.F7 == 1)                   
     ADJ_Direction = 1;             
    else {                           
     ADJ_Direction = 0;             
     ADJ = 0;                        
   }
    Delay_1us();                                           
    j <<= 1;                        
   }

   ADJ_Direction = 1;                                  
   Delay_1us();                                           
   while (ADJ == 1)                  
    Delay_1us();                     

  for (i = 1; i <=16; i++) {          
    k <<= 1;                                                
    if (ADJ == 1)                    
    k = k | 0x0001;
    if (i == 8)                      
      MCU_ACK();                     
   }
  }

  return k;                          
}

void STartUpDelay(){
 Delay_ms(20);
}

void DisplayMeasurements(unsigned short rownumber){
 

    if(SOt > D1)                     
      Tmp_res = SOt * D2 - D1;       
    
	else                             
      Tmp_res = D1 - SOt * D2;       



    temp = SOrh * SOrh * C3 / 100000;             
    Rh_res = SOrh * C2 / 100 - temp - C1;         


    temp=(T1+(T2*SOrh))/1000;
    temp=((Tmp_res-2500)*temp)/100;
    Rh_res=temp+Rh_res;


    Tmp[0] = Tmp_res / 10000 + 48;                  
    Tmp[1] = Tmp_res % 10000 / 1000 + 48;           
    Tmp[2] = Tmp_res % 1000 / 100 + 48;             
    Tmp[4] = Tmp_res % 100 / 10 + 48;               



    Rh[0] = Rh_res % 10000 / 1000 + 48;           
    Rh[1] = Rh_res % 1000 / 100 + 48;             
    Rh[3] = Rh_res % 100 / 10 + 48;               

    La[0] = La_res % 10000 / 1000 + 48;           
    La[1] = La_res % 1000 / 100 + 48;             
    La[3] = La_res % 100 / 10 + 48;

    if (Tmp[0] == '0')                           
      Tmp[0] = ' ';                              
    if (Tmp[0] == ' ' && Tmp[1] == '0')          
      Tmp[1] = ' ';                              

    if (Rh[0] == '0')                             
      Rh[0] = ' ';                                
    if (Rh[0] == ' ' && Rh[1] == '0')             
      Rh[1] = ' ';                                


    Lcd_Out(rownumber, 4, Tmp);                            

    Lcd_Out(rownumber, 8, Rh);

    Lcd_Out(rownumber, 12, La);

}

void output_transmission()
{
	if (Tmp[0] == '0')                           
      		HT1 = 0;                              
    	if (Tmp[0] == ' ' && Tmp[1] == '0')          
      		HT1 = 1;
	
	if (Rh[0] == '0')                           
      		WS1 = 0;                              
    	if (Rh[0] == ' ' && Rh[1] == '0')          
      		WS1 = 1;
	
	if (La[0] == '0')                           
      		LT = 0;                              
    	if (La[0] == ' ' && Tmp[1] == '0')          
      		LT = 1;

}
void main()
{
  CMCON = 0x07;   
  ADCON1 = 0x0F;  
  TRISC = 0x00;
  TRISB = 0x00;
  TRISC = 0;
  SCL1_Direction = 0;  
  LCD_Init();          
  LCD_Cmd(_LCD_CURSOR_OFF);  
  LCD_Cmd(_LCD_CLEAR);       
  Lcd_Out(1,1, "1:");
  Lcd_Out(2,1, "2:");
  Tmp[5] = 223;      
  Tmp[6] = 'C';      
  Rh[4] = '%';       

  while (1) {
   
    Select = 1;
    STartUpDelay();
    SCL1_Direction = 0;              
    SOt = Measure(0x03);             
     
    SOrh = Measure(0x05);            
    SCL1_Direction = 1;               
    DisplayMeasurements(1);
    Delay_ms(2000);                  
     
    Select = 2;
    STartUpDelay();
    SIG_Direction = 0;              
    SOt = Measure(0x03);             
     
    SOrh = Measure(0x05);            
    SIG_Direction = 1;              
    DisplayMeasurements(2);
    Delay_ms(2000);  
	  
    Select = 3;
    STartUpDelay();
    ADJ_Direction = 0;              
    SOt = Measure(0x03);             
     
    SOrh = Measure(0x05);            
    ADJ_Direction = 1;               
    DisplayMeasurements(1);
    Delay_ms(2000);
	}
}
 
