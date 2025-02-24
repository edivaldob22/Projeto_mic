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

#define F_CPU 8000000  // Frequ�ncia do microcontrolador

volatile char lastKeyPressed = '\0';
char armazenaKey[6] = "";  // Armazena at� 6 teclas
int keyIndex = 0;

int main() {
	while (1) {
		if (lastKeyPressed != '\0') {
			// Armazena a tecla pressionada
			if (keyIndex < 6) {
				armazenaKey[keyIndex++] = lastKeyPressed;
				armazenaKey[keyIndex] = '\0'; // Mant�m a string terminada corretamente
			}
			lastKeyPressed = '\0';  // Limpa a vari�vel ap�s uso
		}
		if (armazenaKey[0] == '1') {
		PORTB |= 0b00000010;
		_delay_ms(1000);
		PORTB &= ~0b00000010;
		}
	}

	return 0;
}

// Rotina de interrup��o para detectar pressionamento de teclas
ISR(PCINT0_vect) {
	lastKeyPressed = scanKeypad();
}