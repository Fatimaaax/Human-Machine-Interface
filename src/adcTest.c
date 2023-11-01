#include "Adc_pot.h"
#include <assert.h>
#include "uart.h"


int main(){

  while (1){
    //test ADC_init function
    Adc_Init();
    assert(ADMUX & (1<<REFS0) !=0);
    uart_SendString("REFS0 is correct",16);
    assert(ADCSRA & (1<<ADEN) !=0 );
    uart_SendString("ADEN is correct",15);
    assert(ADCSRA & (1<<ADPS2) !=0 );
    uart_SendString("ADPS2 is correct",16);
    assert(ADCSRA & (1<<ADPS1) !=0 );
    uart_SendString("ADPS1 is correct",16);
    assert(ADCSRA & (1<<ADPS0) !=0 );
    uart_SendString("ADPS0 is correct",16);
    
  }
}