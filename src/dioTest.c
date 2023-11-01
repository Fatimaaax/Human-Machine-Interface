#include <assert.h>
#include "uart.h"
#include "dio.h"

int main(){
  //test BitToBitmask

  while(1){
    uart_SendString("BitToBitmask(1) == 2", 20);
    assert(BitToBitmask(1) == 2);
    uart_SendString("BitToBitmask(3) == 8", 20);
    assert(BitToBitmask(3) == 8);

    //test CharToPort
    uart_SendString("CharToPort('b', INPUT) == PINB", 30);
    assert(CharToPort('b', INPUT) == ((volatile uint8_t*)0x23));
    uart_SendString("CharToPort('b', DIRECTION_REG) == DDRB", 38);
    assert(CharToPort('b', DIRECTION_REG) == ((volatile uint8_t*)0x24));
    uart_SendString("CharToPort('b', DIRECTION_REG) == PORTB", 39);
    assert(CharToPort('b', OUTPUT) == ((volatile uint8_t*)0x25));
    uart_SendString("CharToPort('b', INTERRUPT_REG) == PCINT0", 40);
    assert(CharToPort('b', INTERRUPT_REG) == ((volatile uint8_t*)0x6B));

    //test dio_SetPin and dio_GetPin
    uart_SendString("dio_SetPin('b', 2, 1), dio_GetPin('b', 2) == 4", 46);
    dio_SetPin('b', 2, 1);
    assert(dio_GetPin('b', 2) == 1);

    uart_SendString("dio_SetPin('b', 2, 1), dio_GetPin('b', 2) == 0", 46);
    dio_SetPin('b', 2, 0);
    assert(dio_GetPin('b', 2) == 0);
  }
}
