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

  adc_Init(); 
  lcd_Init();
  
  dio_SetDirection('d', 2, OUTPUT);

  int16_t maxVal= 500;


  while (1) {

    int8_t button = getButton();

    if (button == 1) {

      maxVal+=10;
      //increase max

    } else if (button == -1){

      maxVal-=10;
      //decrease max
    }

    uint16_t adcVal = adc_ReadChannel(1);
    //reading the value from pin 1 in the analog pin
    uint16_t lux = (250.0/(adcVal*ADC_VOLT_PER_STEP)) - 50.0;
    //lux value for ldr

    if (lux > maxVal){ 
      dio_SetPin('d', 3, 1);
      //turn led on 
    } 
    //convert to string
    char maxValStr[4];
    intToString(maxVal, maxValStr, 10);
    // itoa(madmax, madmax_str, 10);
    char luxStr[4];
    intToString(lux, luxStr, 10);
    //prep string to display on lcd
    char lcd_string[14];
    snprintf(lcd_string, sizeof(lcd_string), "Button: %s", maxValStr);

    lcd_Clear();
    lcd_StringXY(lcd_string, 0, 2);

    snprintf(lcd_string, sizeof(lcd_string), "Current: %s", luxStr);
    lcd_StringXY(lcd_string, 1, 2);
    _delay_ms(200);
  }
}


void intToString(int num, char *arr, int base)
{
    char tmp[16];
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (base == 10 && num < 0);    
    if (sign)
        v = -num;
    else
        v = (unsigned)num;

    while (v || tp == tmp)
    {
        i = v % base;
        v /= base;
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    int len = tp - tmp;

    if (sign) 
    {
        *arr++ = '-';
        len++;
    }

    while (tp > tmp)
        *arr++ = *--tp;

    
    *arr = '\0';
}

int8_t getButton(){
  uint16_t button = adc_ReadChannel(0);
  if(button > 900) return 0;

  if(button > 300) return -1;

  return 1;
}
