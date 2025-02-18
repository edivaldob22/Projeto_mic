/*
 * main.c
 *
 * Created: 2/4/2025 9:19:04 AM
 *  Author: Edivaldo e Guilherme
 */ 

#include <xc.h>
#include "teclado.h"
#include "disp.h"

int main(void)
{
	DDRC = 0b00111110; //PC1 Buzzer PC2 a 5 disp
	DDRB = 0b00000011; //PB2 a 5 entrada teclado (coluna)
	DDRD = 0b11111111; //PD0 a 5 disp
	//PB0 e 1 e PD6 e 7 saida teclado.
	
	PORTC = 0x00;
	PORTD = 0x00;
	
    while(1)
    {
        //
    }
}