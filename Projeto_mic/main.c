/*
 * main.c
 *
 * Created: 2/4/2025 9:19:04 AM
 *  Author: Guilherme
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "teclado.h"

#define F_CPU 8000000  // Frequência do microcontrolador

volatile char lastKeyPressed = '\0';
char armazenaKey[6] = "";  // Armazena até 6 teclas
int keyIndex = 0;

int main() {
	while (1) {
		if (lastKeyPressed != '\0') {
			// Armazena a tecla pressionada
			if (keyIndex < 6) {
				armazenaKey[keyIndex++] = lastKeyPressed;
				armazenaKey[keyIndex] = '\0'; // Mantém a string terminada corretamente
			}
			lastKeyPressed = '\0';  // Limpa a variável após uso
		}
		if (armazenaKey[0] == '1') {
		PORTB |= 0b00000010;
		_delay_ms(1000);
		PORTB &= ~0b00000010;
		}
	}

	return 0;
}

// Rotina de interrupção para detectar pressionamento de teclas
ISR(PCINT0_vect) {
	lastKeyPressed = scanKeypad();
}