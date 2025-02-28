/*
 * teclado.c
 *
 * Created: 04/02/2025 11:15:06
 *  Author: Guilherme
 */

#define F_CPU 16000000  // Frequência do microcontrolador

#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "teclado.h"

// Definição dos pinos das linhas (saída)
#define ROW1 0b00000010 //PB1
#define ROW2 0b00000001 //PB0
#define ROW3 0b10000000 //PD7
#define ROW4 0b01000000 //PD6

// Definição dos pinos das colunas (entrada)
#define COL1 0b00000100 //PB2
#define COL2 0b00001000 //PB3
#define COL3 0b00010000 //PB4
#define COL4 0b00100000 //PB5

// Mapeamento das teclas do teclado matricial
char keys[4][4] = {
	{'C', 'D', 'E', 'F'},
	{'8', '9', 'A', 'B'},
	{'4', '5', '6', '7'},
	{'0', '1', '2', '3'}
};

void setupKeypad() {
	// Configura as colunas como entrada (com pull-up)
	
	PORTB |= (COL1 | COL2 | COL3 | COL4);

	// Desativa todas as linhas (estado alto)
	PORTB |= (ROW1 | ROW2);
	PORTD |= (ROW3 | ROW4);
}

void setupInterrupts() {
	PCICR = 0b00000001;   // Habilita interrupções de mudança de estado no PCINT
	PCMSK0 = 0b00111100; // Habilita interrupção nas colunas do teclado
	sei(); // Habilita interrupções globais
}

char scanKeypad() {
	char key;
	
	// Percorre cada linha e verifica qual coluna está pressionada
	for (int i = 0; i < 4; i++) {
		// Ativa uma linha por vez
		if (i == 0) { 
			PORTB &= ~(ROW1); 
			PORTB |= ROW2; 
			PORTD |= (ROW3 | ROW4); 
		}
		if (i == 1) { 
			PORTB |= ROW1; 
			PORTB &= ~(ROW2); 
			PORTD |= (ROW3 | ROW4); 
		}
		if (i == 2) { 
			PORTB |= (ROW1 | ROW2); 
			PORTD &= ~(ROW3); 
			PORTD |= ROW4;
		}
		if (i == 3) { 
			PORTB |= (ROW1 | ROW2);
			PORTD |= ROW3; 
			PORTD &= ~(ROW4);
		}

		_delay_ms(5); // Pequeno atraso para estabilizar

		// Verifica qual coluna foi ativada
		if (!(PINB & COL1)) key = keys[i][0];
		if (!(PINB & COL2)) key = keys[i][1];
		if (!(PINB & COL3)) key = keys[i][2];
		if (!(PINB & COL4)) key = keys[i][3];

		// Desativa todas as linhas antes de passar para a próxima verificação
		PORTB |= (ROW1 | ROW2);
		PORTD |= (ROW3 | ROW4);

		if (key != '\0') { // Se uma tecla foi detectada, aguarda soltar
			while (!(PORTB & COL1) || !(PORTB & COL2) || !(PORTB & COL3) || !(PORTB & COL4));
			break;
		}
	}

	return key; // Retorna a tecla pressionada
	
}
