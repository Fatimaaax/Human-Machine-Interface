#include <avr/io.h>
#include "lcd.h" 
#include "adc.h"
#include "dio.h:


// constants and limits 
const int lightUpperLimit = 800; //random value(adjust)

// current values
int currentLightLevel = 0;

int main{
// Intitalizations 
    lcd_Init();
    adc_Init();
   
    
}
