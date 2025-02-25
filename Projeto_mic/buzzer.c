/*
 * buzzer.c
 *
 * Created: 24/02/2025 11:07:11
 *  Author: Guilherme
 */ 

#include "buzzer.h"

// Configura o pino do buzzer como sa�da
void setupBuzzer() {
	DDRC |= (1 << BUZZER); // Configura PC1 como sa�da
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

// Tr�s bipes curtos (senha correta)
void beepCorreto() {
	for (int i = 0; i < 3; i++) {
		PORTC |= (1 << BUZZER);
		_delay_ms(100);
		PORTC &= ~(1 << BUZZER);
		_delay_ms(100);
	}
}