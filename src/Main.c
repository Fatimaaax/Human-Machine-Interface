#include <util/delay.h>
#include "Adc.h"
#include "Uart.h"
#include "lcd.h"
#include <stdlib.h>
#include "dio.h"
#define BAUD 9600  // define baud

int main() {

  uart_init(BAUD);
  Adc_Init(); 
  lcd_Init();
  
  dio_SetDirection('b', 0, INPUT_PULLUP);
  //port B pin 8
  dio_SetDirection('b', 1, INPUT_PULLUP);
  //port B pin 9
  dio_SetDirection('b', 2, OUTPUT);

  //led pin 10
  int madmax= 300;


  while (1) {


    if ((dio_GetPin('b', 0 !=0 )) {

      madmax+=10;
      //increase max

  }  

    else if ((dio_GetPin('b', 1)!=0)){

      madmax-=10;
      //decrease max
  }

  int light=Adc_ReadChannel(1);
  //reading the value from pin 1 in the analog pin
  int analog=light*(5/2*10);
  int lux=(250/(analog))-50.000000;
  //lux value for ldr

  if (lux > madmax){ 
    PORTB |= 0b00000100;
    //turn led on 

    //convert to string
    char madmax_str[10];
    itoa(madmax, madmax_str, 10);
    char lux_str[10];
    itoa(lux, lux_str, 10);
    //prep string to display on lcd
    char lcd_string[32];
    snprintf(lcd_string, sizeof(lcd_string), "Button: %s   Lux: %s", madmax_str, lux_str);

    lcd_Clear();
    lcd_String(lcd_string);

    _delay_ms(200);

  } 
return 0; 
}
}
