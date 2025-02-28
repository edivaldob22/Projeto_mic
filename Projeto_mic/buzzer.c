/*
 * buzzer.c
 *
 * Created: 24/02/2025 11:07:11
 *  Author: Guilherme
 */ 

#define F_CPU 16000000

#include "buzzer.h"
#include <avr/io.h>
#include <util/delay.h>

// Definição do pino do buzzer (PC1)
#define BUZZER 0b00000010

// Bip curto (tecla pressionada)
void beepCurto() {
	PORTC |= (BUZZER);
	_delay_ms(50);
	PORTC &= ~(BUZZER);
}

// Bip longo (senha incorreta)
void beepLongo() {
	PORTC |= (BUZZER);
	_delay_ms(1000);
	PORTC &= ~(BUZZER);
}

// Três bipes curtos (senha correta)
void beepCorreto() {
	for (int i = 0; i < 3; i++) {
		PORTC |= (BUZZER);
		_delay_ms(100);
		PORTC &= ~(BUZZER);
		_delay_ms(100);
	}
}