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
  
1 dio_SetDirection('b', 0, INPUT_PULLUP);
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

  if (lux>max){
    PORTB |= 0b00000100;
    //turn led on 

  } 

}
}