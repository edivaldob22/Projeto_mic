/*
 * main.c
 *
 * Created: 2/4/2025 9:19:04 AM
 *  Author: Edivaldo e Guilherme
 */ 

#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "teclado.h"
#include "disp.h"

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
}