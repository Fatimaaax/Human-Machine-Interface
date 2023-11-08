#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include "lcd.h"
#include "dio.h"
#include "config.h"

void intToString(int num, char* arr, int base);

int8_t getButton();


int main() {

  //initialization
  adc_Init(); 
  lcd_Init();
  
  dio_SetDirection(LED_PORT, LED_PIN, OUTPUT);

  int16_t maxVal= LUX_MAX;

  while (1) {

    int8_t button = getButton();

    if (button == 1) {
      maxVal = (maxVal + 10) % MAX_LIMIT; //increase max
    } else if (button == -1){
      maxVal = (maxVal - 10) / MIN_LIMIT; //decrease max
    }


    uint16_t adcVal = adc_ReadChannel(LDR_CHANNEL); //unresolved value read from adc
    uint16_t lux = (250.0/(adcVal*ADC_VOLT_PER_STEP)) - 50.0; //resolved value in lux

    if (lux > maxVal) dio_SetPin(LED_PORT, LED_PIN, 1); //turn led on 

    // convert and output to lcd
    
    lcd_Clear();

    char lcd_string[14];

    char tmp[4]; //to store converted strings from decimal values
    
    intToString(maxVal, tmp, 10);

    snprintf(lcd_string, sizeof(lcd_string), "Button: %s", tmp); //string formatting
    lcd_StringXY(lcd_string, 0, 2); //output on lcd

    intToString(lux, tmp, 10);

    snprintf(lcd_string, sizeof(lcd_string), "Current: %s", tmp);
    lcd_StringXY(lcd_string, 1, 2);

    _delay_ms(DELAY_LOOP);
  }
}


void intToString(int num, char *arr, int base)
{
    char tmp[16];
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (base == 10 && num < 0);    

    //make sure value is positive
    if (sign) v = -num;
    else v = (unsigned)num;


    //convert digits to char
    while (v || tp == tmp)
    {
        i = v % base;
        v /= base;
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    //length is last char pointer - first char pointer
    int len = tp - tmp;

    //add negative sign before copying rest of string
    if (sign) 
    {
        *arr++ = '-';
        len++;
    }

    //copy in reverse order from temp to output array
    while (tp > tmp)
        *arr++ = *--tp;

    
    //add terminating character
    *arr = '\0';
}


int8_t getButton(){
  uint16_t button = adc_ReadChannel(BUTTON_CHANNEL);

  if(button > BUTTON_NONE_VAL) return 0;
  if(button > BUTTON_RIGHT_VAL) return -1;

  return 1;
}
