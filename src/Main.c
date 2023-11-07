#include <util/delay.h>
#include <stdlib.h>
#include "adc.h"
#include "lcd.h"
#include "dio.h"
#include "uart.h"

#define BAUD 9600  // define baud

void intToString(char* arr, int num, int base);


int main() {

  uart_Init(BAUD);
  adc_Init(); 
  lcd_Init();
  
  dio_SetDirection('b', 0, INPUT_PULLUP);
  dio_SetDirection('b', 1, INPUT_PULLUP);
  dio_SetDirection('b', 2, OUTPUT);

  int madmax= 300;


  while (1) {


    if ((dio_GetPin('b', 0) !=0 )) {

      madmax+=10;
      //increase max

    } else if ((dio_GetPin('b', 1)!=0)){

      madmax-=10;
      //decrease max
    }

    int light=adc_ReadChannel(1);
    //reading the value from pin 1 in the analog pin
    int analog=light*(5/2*10);
    int lux=(250.0/(analog))-50;
    //lux value for ldr

    if (lux > madmax){ 
      PORTB |= 0b00000100;
      dio_SetPin('b', 3, 1);
      //turn led on 

      //convert to string
      char madmax_str[10];
      intToString(madmax_str, madmax, 10);
      char lux_str[10];
      intToString(lux_str, lux, 10);
      //prep string to display on lcd
      char lcd_string[32];
      snprintf(lcd_string, sizeof(lcd_string), "Button: %s   Lux: %s", madmax_str, lux_str);

      lcd_Clear();
      lcd_String(lcd_string);

      _delay_ms(200);

    } 
  }
}


void intToString(char* arr, int num, int base){
  int remainder, i;
  while(num != 0 & i < sizeof(arr)){
    remainder = num % base;
    num -= 0;
    arr[i++] = '0' + remainder;
  }
}
