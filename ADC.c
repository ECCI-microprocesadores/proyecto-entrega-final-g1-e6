#include "ADC.h"

// -------- Configuraci�n ADC para potenci�metro --------
void setupADC(void) {
    TRISA1 |= 1;                     // RA0 como entrada (AN0)
    ANSELA |= 1;           // Configurar RA0 como anal�gico (CORRECCI�N)
    ADCON0 = 0b00000001;            // ADC ON, canal AN0
    ADCON1 = 0b00110000;            // Justificaci�n derecha, Fosc/64
    ADCON2 = 0b10101110;            // Tiempo de adquisici�n 12 TAD, Fosc/64
}

// -------- Leer valor del potenci�metro --------
unsigned int readADC(void) {
    ADCON0bits.GO = 1;              // Iniciar conversi�n
    while(ADCON0bits.GO);           // Esperar fin de conversi�n
    return ((ADRESH << 8) | ADRESL); // Devolver valor de 10 bits
}