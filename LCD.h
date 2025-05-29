#ifndef LCD_H
#include <xc.h>
#define _XTAL_FREQ 64000000UL  // Frecuencia del oscilador interno

// Definición de pines del LCD
#define RS LATCbits.LATC0  
#define EN LATCbits.LATC1
#define D4 LATCbits.LATC2
#define D5 LATCbits.LATC3
#define D6 LATCbits.LATC4
#define D7 LATCbits.LATC5

// Prototipos de funciones
void LCD_Init(void);
void LCD_Command(unsigned char cmd);
void LCD_Char(unsigned char data);
void LCD_String(const char *str);
void LCD_SetCursor(unsigned char row, unsigned char col);
void LCD_Clear(void);
void LCD_CREATECHAR(unsigned char location, unsigned char *charMap);
void LCD_Enable(void);
void LCD_PrintNumber(unsigned int num);

#endif