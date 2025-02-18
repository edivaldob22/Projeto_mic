/*
 * teclado.c
 *
 * Created: 04/02/2025 11:15:06
 *  Author: Aluno
 */ 
#include "teclado.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <xc.h>

#define F_CPU 8000000  // Frequ�ncia do microcontrolador

// Defini��o dos pinos das linhas (sa�da)
#define ROW1 PB1
#define ROW2 PB0
#define ROW3 PD7
#define ROW4 PD6

// Defini��o dos pinos das colunas (entrada)
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

// Vari�vel para armazenar a tecla pressionada
volatile char lastKeyPressed = '\0';
char armazenaKey[6] = ""; // Armazena at� 6 teclas
int keyIndex = 0;

// Configura��o inicial do teclado
void setupKeypad() {
	// Configura as colunas como entrada (com pull-up)
	PORTB |= (1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4);

	// Desativa todas as linhas (estado alto)
	PORTB |= (1 << ROW1) | (1 << ROW2);
	PORTD |= (1 << ROW3) | (1 << ROW4);
	PCICR |= (1 << PCIE0);   // Habilita interrup��es de mudan�a de estado no PCINT
	PCMSK0 |= (1 << PCINT2) | (1 << PCINT3) | (1 << PCINT4) | (1 << PCINT5); // Habilita interrup��o nas colunas do teclado
	sei(); // Habilita interrup��es globais
}

// Rotina de interrup��o para detectar pressionamento de teclas
ISR(PCINT0_vect) {
	lastKeyPressed = scanKeypad();
}

// Fun��o para escanear o teclado matricial
char scanKeypad() {
	char key = '\0'; // Nenhuma tecla pressionada por padr�o

	// Percorre cada linha e verifica qual coluna est� pressionada
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

		// Desativa todas as linhas antes de passar para a pr�xima verifica��o
		PORTB |= (1 << ROW1) | (1 << ROW2);
		PORTD |= (1 << ROW3) | (1 << ROW4);

		if (key != '\0') { // Se uma tecla foi detectada, aguarda soltar
			while (!(PINB & (1 << COL1)) || !(PINB & (1 << COL2)) || !(PINB & (1 << COL3)) || !(PINB & (1 << COL4)));
			break;
		}
	}

	return key; // Retorna a tecla pressionada
}




