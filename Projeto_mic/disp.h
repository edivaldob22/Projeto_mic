/*
 * disp.h
 *
 * Created: 11/02/2025 10:16:40
 *  Author: Edivaldo
 */ 


#ifndef DISP_H_
#define DISP_H_

//declarar a(s) funções do display
void disp_inicial();
void disp_clear();
void disp_set(int linha, int col);
void disp_w(char msg[16]);

#endif /* DISP_H_ */