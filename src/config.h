#ifndef __config__ 
#define __config__

#define BAUD 9600 //uart baud rate

#define ADC_VOLT_PER_STEP 5.0/1024.0 

//LCD config
#define LCD_Dir  DDRD	
#define LCD_Port PORTD
#define RS_EN_Dir  DDRB		
#define RS_EN_Port PORTB  
#define RS PB0	
#define EN PB1 

#endif
