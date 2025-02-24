/*
 * disp.c
 *
 * Created: 11/02/2025 11:15:06
 *  Author: Edivaldo
 */

#include <xc.h>
#include <util/delay.h>
#include "disp.h"

#define F_CPU 8000000

void disp_inicial()
{
	char pChar;
	//CONFIGURA MODO 8 BITS
	pChar = 0b00111000;
	uint8_t db0 = (pChar & 0b00000001) >> 0;
	uint8_t db1 = (pChar & 0b00000010) >> 1;
	uint8_t db2 = (pChar & 0b00000100) >> 2;
	uint8_t db3 = (pChar & 0b00001000) >> 3;
	uint8_t db4 = (pChar & 0b00010000) >> 4;
	uint8_t db5 = (pChar & 0b00100000) >> 5;
	uint8_t db6 = (pChar & 0b01000000) >> 6;
	uint8_t db7 = (pChar & 0b10000000) >> 7;
	
	uint8_t en = 0;
	uint8_t rs = 0;
	
	if(db3 == 0) PORTD &= ~(1 << 0);
	if(db3 == 1) PORTD |= db3 << 0;
	if(db2 == 0) PORTD &= ~(1 << 1);
	if(db2 == 1) PORTD |= db2 << 1;
	if(db1 == 0) PORTD &= ~(1 << 2);
	if(db1 == 1) PORTD |= db1 << 2;
	if(db0 == 0) PORTD &= ~(1 << 3);
	if(db0 == 1) PORTD |= db0 << 3;
	if(en == 0) PORTD &= ~(1 << 4);
	if(en == 1) PORTD |= en << 4;
	if(rs == 0) PORTD &= ~(1 << 5);
	if(rs == 1) PORTD |= rs << 5;
	if(db7 == 0) PORTC &= ~(1 << 2);
	if(db7 == 1) PORTC |= db7 << 2;
	if(db6 == 0) PORTC &= ~(1 << 3);
	if(db6 == 1) PORTC |= db6 << 3;
	if(db5 == 0) PORTC &= ~(1 << 4);
	if(db5 == 1) PORTC |= db5 << 4;
	if(db4 == 0) PORTC &= ~(1 << 5);
	if(db4 == 1) PORTC |= db4 << 5;
	
	_delay_ms(2);
	en = 1;
	PORTD |= en << 4;
	_delay_ms(2);
	PORTD &= ~(en << 4); //limpa bit en
	_delay_ms(2);
	
	//liga display
	pChar = 0b00001110; 
	db0 = (pChar & 0b00000001) >> 0;
	db1 = (pChar & 0b00000010) >> 1;
	db2 = (pChar & 0b00000100) >> 2;
	db3 = (pChar & 0b00001000) >> 3;
	db4 = (pChar & 0b00010000) >> 4;
	db5 = (pChar & 0b00100000) >> 5;
	db6 = (pChar & 0b01000000) >> 6;
	db7 = (pChar & 0b10000000) >> 7;
	
	en  = (0b00000000 & 0b00000001) >> 0;
	rs  = (0b00000000 & 0b00000001) >> 0;
	
	if(db3 == 0) PORTD &= ~(1 << 0);
	if(db3 == 1) PORTD |= db3 << 0;
	if(db2 == 0) PORTD &= ~(1 << 1);
	if(db2 == 1) PORTD |= db2 << 1;
	if(db1 == 0) PORTD &= ~(1 << 2);
	if(db1 == 1) PORTD |= db1 << 2;
	if(db0 == 0) PORTD &= ~(1 << 3);
	if(db0 == 1) PORTD |= db0 << 3;
	if(en == 0) PORTD &= ~(1 << 4);
	if(en == 1) PORTD |= en << 4;
	if(rs == 0) PORTD &= ~(1 << 5);
	if(rs == 1) PORTD |= rs << 5;
	if(db7 == 0) PORTC &= ~(1 << 2);
	if(db7 == 1) PORTC |= db7 << 2;
	if(db6 == 0) PORTC &= ~(1 << 3);
	if(db6 == 1) PORTC |= db6 << 3;
	if(db5 == 0) PORTC &= ~(1 << 4);
	if(db5 == 1) PORTC |= db5 << 4;
	if(db4 == 0) PORTC &= ~(1 << 5);
	if(db4 == 1) PORTC |= db4 << 5;
	
	_delay_ms(2);
	en = 1;
	PORTD |= en << 4;
	_delay_ms(2);
	PORTD &= ~(en << 4);
	_delay_ms(2);
	
	//modo set
	pChar = 0b00000110;
	db0 = (pChar & 0b00000001) >> 0;
	db1 = (pChar & 0b00000010) >> 1;
	db2 = (pChar & 0b00000100) >> 2;
	db3 = (pChar & 0b00001000) >> 3;
	db4 = (pChar & 0b00010000) >> 4;
	db5 = (pChar & 0b00100000) >> 5;
	db6 = (pChar & 0b01000000) >> 6;
	db7 = (pChar & 0b10000000) >> 7;
	
	en  = (0b00000000 & 0b00000001) >> 0;
	rs  = (0b00000000 & 0b00000001) >> 0;
	
	if(db3 == 0) PORTD &= ~(1 << 0);
	if(db3 == 1) PORTD |= db3 << 0;
	if(db2 == 0) PORTD &= ~(1 << 1);
	if(db2 == 1) PORTD |= db2 << 1;
	if(db1 == 0) PORTD &= ~(1 << 2);
	if(db1 == 1) PORTD |= db1 << 2;
	if(db0 == 0) PORTD &= ~(1 << 3);
	if(db0 == 1) PORTD |= db0 << 3;
	if(en == 0) PORTD &= ~(1 << 4);
	if(en == 1) PORTD |= en << 4;
	if(rs == 0) PORTD &= ~(1 << 5);
	if(rs == 1) PORTD |= rs << 5;
	if(db7 == 0) PORTC &= ~(1 << 2);
	if(db7 == 1) PORTC |= db7 << 2;
	if(db6 == 0) PORTC &= ~(1 << 3);
	if(db6 == 1) PORTC |= db6 << 3;
	if(db5 == 0) PORTC &= ~(1 << 4);
	if(db5 == 1) PORTC |= db5 << 4;
	if(db4 == 0) PORTC &= ~(1 << 5);
	if(db4 == 1) PORTC |= db4 << 5;
	
	_delay_ms(2);
	en = 1;
	PORTD |= en << 4;
	_delay_ms(2);
	PORTD &= ~(en << 4);
	_delay_ms(2);
}
void disp_clear()
{
	
}
void disp_set(int linha, int col)
{
	
}
void disp_w(char msg[16])
{
	
}
