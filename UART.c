#include "UART.h"
#include <stdio.h>


void UART_Init(void) {
    TRISC6 = 0; // TX como salida
    TRISC7 = 1; // RX como entrada

    SPBRG1 = 25; // Baudrate 9600 para Fosc = 16MHz
    TXSTA1bits.BRGH = 0; // Baja velocidad (BRGH = 0)
    BAUDCON1bits.BRG16 = 0; // 8 bits del generador de baudrate

    RCSTA1bits.SPEN = 1; // Habilita el módulo serial
    TXSTA1bits.SYNC = 0; // Modo asíncrono
    TXSTA1bits.TXEN = 1; // Habilita transmisión
    RCSTA1bits.CREN = 1; // Habilita recepción

    
    PIE1bits.RC1IE = 1;   // Habilita interrupción por recepción UART
    PIR1bits.RC1IF = 0;   // Limpia bandera
    INTCONbits.PEIE = 1;  // Habilita interrupciones periféricas
    INTCONbits.GIE = 1;   // Habilita interrupciones globales
}

void UART_WriteChar(char data) {
    while (!TXSTA1bits.TRMT); // Espera a que se vacíe el buffer de transmisión
    TXREG1 = data;
}

void UART_WriteString(const char* str) {
    while (*str) {
        UART_WriteChar(*str++);
    }
}

void UART_WriteUInt(uint16_t value) {
    char buffer[6];
    sprintf(buffer, "%u", value);
    UART_WriteString(buffer);
}

void UART_WriteVoltage(float volts) {
    char buffer[10];
    sprintf(buffer, "%.2f", volts);  // Muestra el voltaje con 2 decimales
    UART_WriteString(buffer);
}