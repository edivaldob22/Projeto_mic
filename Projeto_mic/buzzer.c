/*
 * buzzer.c
 *
 * Created: 24/02/2025 11:07:11
 *  Author: Guilherme
 */ 

#include "buzzer.h"

// Configura o pino do buzzer como saída
void setupBuzzer() {
	DDRC |= (1 << BUZZER); // Configura PC1 como saída
}

// Bip curto (tecla pressionada)
void beepCurto() {
	PORTC |= (1 << BUZZER);
	_delay_ms(50);
	PORTC &= ~(1 << BUZZER);
}

// Bip longo (senha incorreta)
void beepLongo() {
	PORTC |= (1 << BUZZER);
	_delay_ms(500);
	PORTC &= ~(1 << BUZZER);
}

// Três bipes curtos (senha correta)
void beepCorreto() {
	for (int i = 0; i < 3; i++) {
		PORTC |= (1 << BUZZER);
		_delay_ms(100);
		PORTC &= ~(1 << BUZZER);
		_delay_ms(100);
	}
}