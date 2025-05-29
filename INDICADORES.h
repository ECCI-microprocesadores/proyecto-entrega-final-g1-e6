#ifndef INDICADORES_H
#define	INDICADORES_H

#include <xc.h>
#define _XTAL_FREQ 64000000UL

// Definición de pines para LEDs
#define LED_VERDE LATBbits.LATB0
#define LED_AMARILLO LATBbits.LATB1
#define LED_ROJO LATBbits.LATB2
#define BUFFER LATBbits.LATB3
#define Ventilador LATBbits.LATB4

// Umbrales en voltios
#define UMBRAL_BAJO 1.0
#define UMBRAL_MEDIO 2.0
#define UMBRAL_ALTO 3.0

void configurarLEDs(void);
float convertirVoltaje(unsigned int adcValue);
void controlarLEDs(float voltaje);

#endif