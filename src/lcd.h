#ifndef _lcd_
#define _lcd_ 

#define LCD_Dir  DDRD			/* Define LCD data port direction */
#define LCD_Port PORTD		/* Define LCD data port */

#define RS_EN_Dir  DDRB		/* Define RS and En data port direction */
#define RS_EN_Port PORTB  /* Define RS and En port */
#define RS PB0				    /* Define Register Select pin */
#define EN PB1 				    /* Define Enable signal pin */

void lcd_Send (unsigned char char_data);
void lcd_Init (void);
void lcd_String (char *str);
void lcd_StringXY (char *str, char row, char pos);
void lcd_Clear();

#endif 
