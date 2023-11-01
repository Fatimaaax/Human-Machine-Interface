#include "Adc_pot.h"
#include <assert.h>
#include "uart.h"


int main(){

  while (1){
    //test ADC_init function
    Adc_Init();
    assert(ADMUX & (1<<REFS0) !=0);
    uart_SendString("REFS0 is correct",);
    assert(ADCSRA & (1<<ADEN) !=0 );
    uart_SendString("ADEN is correct",);
    assert(ADCSRA & (1<<ADPS2) !=0 );
    uart_SendString("ADPS2 is correct",);
    assert(ADCSRA & (1<<ADPS1) !=0 );
    uart_SendString("ADPS1 is correct",);
    assert(ADCSRA & (1<<ADPS0) !=0 );
    
  }
}