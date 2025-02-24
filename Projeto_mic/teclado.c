/*
 * teclado.c
 *
 * Created: 04/02/2025 11:15:06
 *  Author: Guilherme
 */ 
#include "teclado.h"
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000  // Frequência do microcontrolador


// Definição dos pinos das linhas (saída)
#define ROW1 PB1
#define ROW2 PB0
#define ROW3 PD7
#define ROW4 PD6

// Definição dos pinos das colunas (entrada)
#define COL1 PB2
#define COL2 PB3
#define COL3 PB4
#define COL4 PB5

// Mapeamento das teclas do teclado matricial
char keys[4][4] = {
	{'C', 'D', 'E', 'F'},
	{'8', '9', 'A', 'B'},
	{'4', '5', '6', '7'},
	{'0', '1', '2', '3'}
};

void setupKeypad() {
	// Configura as colunas como entrada (com pull-up)
	DDRB &= ~((1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4));
	PORTB |= (1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4);

	// Configura as linhas como saída
	DDRB |= (1 << ROW1) | (1 << ROW2);
	DDRD |= (1 << ROW3) | (1 << ROW4);

	// Desativa todas as linhas (estado alto)
	PORTB |= (1 << ROW1) | (1 << ROW2);
	PORTD |= (1 << ROW3) | (1 << ROW4);
}

void setupInterrupts() {
	PCICR |= (1 << PCIE0);   // Habilita interrupções de mudança de estado no PCINT
	PCMSK0 |= (1 << PCINT2) | (1 << PCINT3) | (1 << PCINT4) | (1 << PCINT5); // Habilita interrupção nas colunas do teclado
	sei(); // Habilita interrupções globais
}

char scanKeypad() {
	char key = '\0'; // Nenhuma tecla pressionada por padrão

	// Percorre cada linha e verifica qual coluna está pressionada
	for (int i = 0; i < 4; i++) {
		// Ativa uma linha por vez
		if (i == 0) { PORTB &= ~(1 << ROW1); PORTB |= (1 << ROW2); PORTD |= (1 << ROW3) | (1 << ROW4); }
		if (i == 1) { PORTB |= (1 << ROW1); PORTB &= ~(1 << ROW2); PORTD |= (1 << ROW3) | (1 << ROW4); }
		if (i == 2) { PORTB |= (1 << ROW1) | (1 << ROW2); PORTD &= ~(1 << ROW3); PORTD |= (1 << ROW4); }
		if (i == 3) { PORTB |= (1 << ROW1) | (1 << ROW2); PORTD |= (1 << ROW3); PORTD &= ~(1 << ROW4); }

		_delay_ms(5); // Pequeno atraso para estabilizar

		// Verifica qual coluna foi ativada
		if (!(PINB & (1 << COL1))) key = keys[i][0];
		if (!(PINB & (1 << COL2))) key = keys[i][1];
		if (!(PINB & (1 << COL3))) key = keys[i][2];
		if (!(PINB & (1 << COL4))) key = keys[i][3];

		// Desativa todas as linhas antes de passar para a próxima verificação
		PORTB |= (1 << ROW1) | (1 << ROW2);
		PORTD |= (1 << ROW3) | (1 << ROW4);

		if (key != '\0') { // Se uma tecla foi detectada, aguarda soltar
			while (!(PINB & (1 << COL1)) || !(PINB & (1 << COL2)) || !(PINB & (1 << COL3)) || !(PINB & (1 << COL4)));
			break;
		}
	}

	return key; // Retorna a tecla pressionada
}




