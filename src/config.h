#ifndef __config__ 
#define __config__

//uart baud rate
#define BAUD 9600 

#define ADC_VOLT_PER_STEP 5.0/1024.0 

//lux value limits
#define LUX_MAX 150
#define MAX_LIMIT 1000
#define MIN_LIMIT 10

//LCD config
#define LCD_Dir  DDRD	
#define LCD_Port PORTD
#define RS_EN_Dir  DDRB		
#define RS_EN_Port PORTB  
#define RS PB0	
#define EN PB1 

//button config 
#define BUTTON_CHANNEL 0
#define BUTTON_NONE_VAL 900
#define BUTTON_RIGHT_VAL 300

//pin config
#define LDR_CHANNEL 1 
#define LED_PIN 2
#define LED_PORT 'd'

//main loop delay
#define DELAY_LOOP 100
#endif
