/*
 * buzzer.h
 *
 * Created: 24/02/2025 11:07:29
 *  Author: Guilherme
 */ 


#ifndef BUZZER_H
#define BUZZER_H

#include <avr/io.h>
#include <util/delay.h>

// Definição do pino do buzzer
#define BUZZER PC1

// Protótipos das funções
void setupBuzzer();
void beepShort();
void beepLong();
void beepSuccess();

#endif