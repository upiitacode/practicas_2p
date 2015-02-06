/*
PINES USADOS
PB0 PB1 PB2 PB3 PB4 PB5 PB6 PB7
*/

#include "TM4C123.h"                    // Device header

int terminado=0;

int main(){
	unsigned char valor=0;
	SYSCTL->RCGCGPIO|=(0x1<<1);//Habilitar periferico GPIOB
	GPIOB->DEN|=0xFF;//Configurar pines PB[0..7] con funciones digitales
	GPIOB->DIR|=0xFF;//Configurar pines PB[0..7] como salidas
	GPIOB->DATA=0;//sacar 0 por pines PB[0..7]
	/**/
	SysTick_Config(12500000);//desbordarse cada t=(f/c)=(50*10^6)/(12.5*10^6)= 0.25s 
	while(1){
		GPIOB->DATA=(0xFF)&(~(GPIOB->DATA));//invertir leds
		terminado=0;
		while(!terminado);
		valor++;
	}
	//return 0;
}
//rutina de interrupcion
void SysTick_Handler(void){
	static int contador;
	contador++;
	contador%=0x4;//cada cuatro interrupciones desbordamiento (1s) poner la bandera de terminado en 1
	if(contador==0x0){
		terminado=1;
	}
}

