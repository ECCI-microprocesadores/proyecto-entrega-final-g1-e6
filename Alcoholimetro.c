#include <xc.h>
#include "LCD.h"
#include "ADC.h"
#include "INDICADORES.h"
#include "UART.h"

#pragma config FOSC = INTIO67
#pragma config PLLCFG = ON
#pragma config WDTEN = OFF
#pragma config LVP = OFF

void main(void) {
    // Configurar reloj interno a 64 MHz
    OSCCON = 0b11110000;       // Configura el reloj interno a 16 MHz
    OSCTUNEbits.PLLEN = 1;     // Activa el PLL para alcanzar 64 MHz

    setupADC();
    LCD_Init();
    configurarLEDs();
    UART_Init();

    // Calentar el sensor (el MQ-3 necesita precalentamiento)
    LCD_SetCursor(1, 0);
    LCD_String("Calentando...");
    UART_WriteString("Calentando sensor MQ-3...\r\n");

    // Barra de progreso simple
    for (int i = 0; i < 20; i++) {
        LCD_SetCursor(2, i);
        LCD_Char(255);  // Carácter de bloque
        __delay_ms(1000); // 20 segundos total
    }

    LCD_Clear();
    UART_WriteString("Listo para leer voltaje...\r\n");

    while (1) {
        unsigned int adcValue = readADC();
        float voltaje = convertirVoltaje(adcValue);
        
        // Mostrar valor ADC
        LCD_SetCursor(1, 0);
        LCD_String("Volt: ");
        int entero = (int)voltaje;
        int decimal = (int)((voltaje - entero) * 100);  // dos decimales

        LCD_PrintNumber(entero);
        LCD_Char('.');
        if (decimal < 10) LCD_Char('0'); // Asegura 2 dígitos
        LCD_PrintNumber(decimal);
        LCD_String("V ");

        // Enviar por UART
        UART_WriteString("Voltaje: ");
        UART_WriteVoltage(voltaje);
        UART_WriteString(" V\r\n");

        // Mostrar nivel de alerta
        LCD_SetCursor(2, 0);
        if (voltaje < UMBRAL_BAJO) {
            LCD_String("Nivel:  BAJO ");
            UART_WriteString("Nivel: BAJO\r\n");
        } else if ((voltaje > UMBRAL_BAJO) && (voltaje < UMBRAL_MEDIO)) {
            LCD_String("Nivel: MEDIO");
            UART_WriteString("Nivel: MEDIO\r\n");
        } else if ((voltaje > UMBRAL_MEDIO) && (voltaje < UMBRAL_ALTO)) {
            LCD_String("Nivel: ALTO ");
            UART_WriteString("Nivel: ALTO\r\n");
        } else {
            LCD_String("Nivel: PELIG");
            UART_WriteString("Nivel: PELIGRO\r\n");
        }

        controlarLEDs(voltaje);

        __delay_ms(500);
    }
}
