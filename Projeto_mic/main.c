/*
 * main.c
 *
 * Created: 2/4/2025 9:19:04 AM
 *  Author: Edivaldo e Guilherme
 */
#define F_CPU 16000000

#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "teclado.h"
#include "disp.h"
#include "buzzer.h"

#define tam_Senha 6

char senha_correta[7] = "123456";
int f_senhaCorreta = 0;
int c_erro = 0;
uint8_t f_ax = 1;
uint8_t f_buzzer = 1;
uint8_t f_key = 0;
char armazenaKey[7];  // Armazena até 6 teclas

int main(void)
{
	DDRC = 0b00111111; //PC1 Buzzer PC2 a 5 disp
	DDRB = 0b00000011; //PB2 a 5 entrada teclado (coluna)
	DDRD = 0b11111111; //PD0 a 5 disp
	//PB0 e 1 e PD6 e 7 saida teclado.
	
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;

	setupKeypad();
	setupInterrupts();
	
	disp_inicial();
	disp_clear();
	while (1) {
		char mensagem[16] = "Digite a Senha";
		
		if (f_ax && (c_erro < 3)) {
			f_ax = 0;
			disp_clear();
			disp_set(1);
			disp_w(mensagem, 14);      
			int i = 0;
			while (i < tam_Senha) {
				char tecla = scanKeypad();
				if (tecla != '\0') {
					armazenaKey[i++] = tecla; // Armazena a tecla no vetor
					armazenaKey[i] = '\0';    // Finaliza a string
					_delay_ms(50);
					disp_set(2);              // Define a segunda linha do display
					disp_w(armazenaKey, i);   // Exibe a senha digitada
				}
			
			}
			if(i == tam_Senha) f_key = 1;
		}
		if(c_erro >= 3){
			disp_clear();
			disp_set(1);
			strcpy(mensagem, "Cofre bloqueado");
			disp_w(mensagem,15);
			_delay_ms(10000);
			disp_clear();
			c_erro = 0;
		}
		if(f_key){
			for (int i = 0; i < tam_Senha; i++) {
				if ((armazenaKey[i]) != (senha_correta[i])) f_senhaCorreta++;
			}

			if(f_senhaCorreta > 0) {
				beepLongo();
				disp_clear();
				disp_set(1);
				strcpy(mensagem, "Senha incorreta");
				disp_w(mensagem,15);
				if(c_erro == 0){
					disp_set(2);
					strcpy(mensagem, "2 tentativas");
					disp_w(mensagem,12);
				}
				if(c_erro == 1){
					disp_set(2);
					strcpy(mensagem, "1 tentativa");
					disp_w(mensagem,11);
				}
				if(c_erro == 2){
					disp_set(2);
					strcpy(mensagem, "0 tentativa");
					disp_w(mensagem,11);
				}
				_delay_ms(2000);
				disp_clear();
				f_ax = 1;
				f_key = 0;
				f_senhaCorreta = 0;
				c_erro++;
			}
			else {
				if(f_buzzer) {
					f_buzzer = 0;
					beepCorreto();
				}
				disp_clear();
				disp_set(1);
				strcpy(mensagem, "Senha correta");
				disp_w(mensagem,13);
				disp_set(2);
				strcpy(mensagem, "Cofre aberto");
				disp_w(mensagem,12);
				_delay_ms(1000);
			}
		}
	}
	
	return 0;
}
ISR(PCINT0_vect) {
	
	PORTC ^= 0b00000001;
	beepCurto();
}