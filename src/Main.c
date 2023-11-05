#include <avr/io.h>
#include "lcd.h" 
#include "ldr.h" 
#include "buttons.h" 
#include "leds.h"
#include "adc.h"



// constants and limits 
const int lightUpperLimit = 800; //random value(adjust)

// current values
int currentLightLevel = 0;

int main{
// Intitalizations 
    lcd_Init();
    ldr_Init();
    buttons_Init();
    leds_Init();
}
