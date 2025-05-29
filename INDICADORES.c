#include "INDICADORES.h"

void configurarLEDs(void) {
    TRISB = 0x00;       // Configurar PORTB como salida para los LEDs
    LATB = 0x00;        // Apagar todos los LEDs inicialmente
}

// Conversión ADC (0-1023) a voltaje (0.0 - 5.0V)
float convertirVoltaje(unsigned int adcValue) {
    return ((float)adcValue * 5.0) / 1023.0;
}

void controlarLEDs(float voltaje) {
    // Leer botón en RA1 (entrada digital)
    TRISAbits.TRISA1 = 1;       // RA1 como entrada
    ANSELA &= ~(1 << 1);        // RA1 como entrada digital (no analógica)

    LED_VERDE = 0;
    LED_AMARILLO = 0;
    LED_ROJO = 0;
    BUFFER = 0;
    Ventilador = 0;

    if (voltaje < UMBRAL_BAJO) {
        LED_VERDE = 1;
    } else if ((voltaje > UMBRAL_BAJO) && (voltaje < UMBRAL_MEDIO)) {
        LED_AMARILLO = 1;
    } else if ((voltaje > UMBRAL_MEDIO) && (voltaje < UMBRAL_ALTO)) {
        LED_AMARILLO = 1;
        __delay_ms(500);
        LED_AMARILLO = 0;
        __delay_ms(500);
    } else {
        LED_ROJO = 1;
        __delay_ms(250);
        LED_ROJO = 0;
        __delay_ms(250);
        BUFFER = 1;
        Ventilador = 1;
    }

    // ? Activación adicional por botón en RA1
    if (PORTAbits.RA1 == 1) {
        BUFFER = 1;
        Ventilador = 1;
    }
}
