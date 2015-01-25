/*
PINES USADOS
PB0 PB1 PB2 PB3 PB4 PB5 PB6 PB7
*/

#include "TM4C123.h"                    // Device header

void delay_ms(int delay_time);

int main(){
	unsigned char valor=0;
	SYSCTL->RCGCGPIO|=(0x1<<1);//Habilitar periferico GPIOB
	GPIOB->DEN|=0xFF;//Configurar pines PB[0..7] con funciones digitales
	GPIOB->DIR|=0xFF;//Configurar pines PB[0..7] como salidas
	GPIOB->DATA=0;//sacar 0 por pines PB[0..7]
	while(1){
		GPIOB->DATA=valor;
		delay_ms(0x1FFFFF);
		valor++;
	}
	//return 0;
}

void delay_ms(int delay_time){
	int i;
	for(i=0; i<delay_time; i++);
}
