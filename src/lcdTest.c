#include <assert.h>
#include "lcd.h"
#include "uart.h"

int main() {
    while (1) {
        lcd_Init();
        assert(RS_EN_Dir & (1 << RS) != 0);
        uart_SendString("RS and EN pins are set correctly for LCD initialization", 47);

        char testString[] = "LCD Test";
        lcd_Clear();
        lcd_String(testString);

        lcd_Clear();

        char testString2[] = "Position Test";
        lcd_StringXY(testString2, 1, 5);

        _delay_ms(2000);
    }

    return 0;
}
