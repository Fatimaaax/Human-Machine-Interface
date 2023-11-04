#include <avr/io.h>
#include <lcd.h>
#include <dio.h>
#include <adc.h>
#include <uart.h>


// constants and limits 
const int tempUpperLimit = ;
const int tempLowerLimit = ;
const int humidityUpperLimit = ;
const int humidityLowerLimit = ;

// current values
int currentTemp = 0;
int currentHumidity = 0;

int main{
// Intitalizations 
    lcd_Init();
    sensor_Init();
    buttons_Init();
    leds_Init();
}
