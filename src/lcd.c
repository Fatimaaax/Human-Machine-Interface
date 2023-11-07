#include <avr/io.h>
#include <util/delay.h>	  
#include "lcd.h"

void lcd_Send(uint8_t data)
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	RS_EN_Port |= (1<<RS);		/* RS=1, data reg. */
	RS_EN_Port|= (1<<EN);
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	RS_EN_Port |= (1<<EN);
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void lcd_Cmd(uint8_t cmnd)
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	RS_EN_Port &= ~ (1<<RS);		/* RS=0, command reg. */
	RS_EN_Port |= (1<<EN);		/* Enable pulse */
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	RS_EN_Port |= (1<<EN);
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void lcd_Init (void)			/* LCD Initialize function */
{
	LCD_Dir |= 0xFF;			    /* Make LCD port direction as o/p */
  RS_EN_Dir |= (1 << EN) | (1 << RS);

	_delay_ms(20);			    /* LCD Power ON delay always >15ms */
	
	lcd_Cmd(0x02);		  /* send for 4 bit initialization of LCD  */
	lcd_Cmd(0x28);      /* 2 line, 5*7 matrix in 4-bit mode */
	lcd_Cmd(0x0c);      /* Display on cursor off*/
	lcd_Cmd(0x06);      /* Increment cursor (shift cursor to right)*/
	lcd_Cmd(0x01);      /* Clear display screen*/
	_delay_ms(2);
}

void lcd_String (char* str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		lcd_Send(str[i]);
	}
}

void lcd_StringXY (char* str, char row, char pos)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	  lcd_Cmd((pos & 0x0F)|0x80);	                  /* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	  lcd_Cmd((pos & 0x0F)|0xC0);	                  /* Command of first row and required position<16 */
    
	lcd_String(str);	                              	/* Call LCD string function */
}

void lcd_Clear()
{
	lcd_Cmd (0x01);		/* Clear display */
	_delay_ms(2);
	lcd_Cmd (0x80);		/* Cursor at home position */
}
