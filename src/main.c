#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include "adc.h"
#include "lcd.h"
#include "dio.h"
#include "config.h"
#include "helpers.h"


int main() {

  //initialization
  adc_Init(); 
  lcd_Init();
  
  dio_SetDirection(LED_PORT, LED_PIN, OUTPUT);

  int16_t maxVal= LUX_MAX;

  lcd_String("Hi!");

  while (1) {

    int8_t button = getAdcButton();

    if (button == 1) {
      maxVal = (maxVal + 10); //increase max
    } else if (button == -1){
      maxVal = (maxVal - 10); //decrease max
    }

    maxVal = clamp(maxVal, MIN_LIMIT, MAX_LIMIT);

    double vOut = adc_ReadChannel(LDR_CHANNEL) * ADC_VOLT_PER_STEP; //unresolved value read from adc
    uint16_t lux = (250.0/vOut) - 50.0; //resolved value in lux

    if (lux > maxVal) dio_SetPin(LED_PORT, LED_PIN, 1); //turn led on 
    else dio_SetPin(LED_PORT, LED_PIN, 0);

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


