#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include "lcd.h"
#include "dio.h"

#define BAUD 9600  // define baud

void intToString(int num, char* arr, int base);


int main() {

  adc_Init(); 
  lcd_Init();
  
  dio_SetDirection('d', 0, INPUT_PULLUP);
  dio_SetDirection('d', 1, INPUT_PULLUP);
  dio_SetDirection('d', 2, OUTPUT);

  int madmax= 300;


  while (1) {


    if ((dio_GetPin('d', 0) ==0 )) {

      madmax+=10;
      //increase max

    } else if ((dio_GetPin('d', 1)==0)){

      madmax-=10;
      //decrease max
    }

    int light=adc_ReadChannel(1);
    //reading the value from pin 1 in the analog pin
    int analog=light*(5/2*10);
    int lux=(250.0/(analog))-50;
    //lux value for ldr

    if (lux > madmax){ 
      dio_SetPin('d', 3, 1);
      //turn led on 


    } 
    //convert to string
    char madmax_str[10];
    intToString(madmax, madmax_str, 10);
    // itoa(madmax, madmax_str, 10);
    char lux_str[10];
    intToString(lux, lux_str, 10);
    //prep string to display on lcd
    char lcd_string[32];
    snprintf(lcd_string, sizeof(lcd_string), "Button: %s", madmax_str);

    lcd_Clear();
    lcd_StringXY(lcd_string, 0, 2);

    snprintf(lcd_string, sizeof(lcd_string), "Current: %s", lux_str);
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
