#include "ADC.h"

// -------- Configuración ADC para potenciómetro --------
void setupADC(void) {
    TRISA1 |= 1;                     // RA0 como entrada (AN0)
    ANSELA |= 1;           // Configurar RA0 como analógico (CORRECCIÓN)
    ADCON0 = 0b00000001;            // ADC ON, canal AN0
    ADCON1 = 0b00110000;            // Justificación derecha, Fosc/64
    ADCON2 = 0b10101110;            // Tiempo de adquisición 12 TAD, Fosc/64
}

// -------- Leer valor del potenciómetro --------
unsigned int readADC(void) {
    ADCON0bits.GO = 1;              // Iniciar conversión
    while(ADCON0bits.GO);           // Esperar fin de conversión
    return ((ADRESH << 8) | ADRESL); // Devolver valor de 10 bits
}