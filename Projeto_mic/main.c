/*
 * main.c
 *
 * Created: 2/4/2025 9:19:04 AM
 *  Author: Guilherme
 */ 

<<<<<<< HEAD
#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>
=======
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
>>>>>>> 229071333787caca1ed473632468f1d336671f1f
#include "teclado.h"

<<<<<<< HEAD
#define F_CPU 8000000

int main(void)
{
	DDRC = 0b00111110; //PC1 Buzzer PC2 a 5 disp
	DDRB = 0b00000011; //PB2 a 5 entrada teclado (coluna)
	DDRD = 0b11111111; //PD0 a 5 disp
	//PB0 e 1 e PD6 e 7 saida teclado.
	
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	
	disp_inicial();
	
    while(1)
    {
		//
    }
=======
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
>>>>>>> 229071333787caca1ed473632468f1d336671f1f
}