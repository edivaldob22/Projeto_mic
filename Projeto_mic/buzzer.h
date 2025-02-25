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

// Defini��o do pino do buzzer
#define BUZZER PC1

// Prot�tipos das fun��es
void setupBuzzer();
void beepShort();
void beepLong();
void beepSuccess();

#endif