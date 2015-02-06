/*
PINES USADOS
PB0 PB1 PB2 PB3 PB4 PB5 PB6 PB7
*/

#include "TM4C123.h"                    // Device header

int terminado=0;

//posicion de la bandera de desbordamiento del SysTick
#define COUNTFLAG (0x1<<16)

int main(){
	unsigned char valor=0;
	SYSCTL->RCGCGPIO|=(0x1<<1);//Habilitar periferico GPIOB
	GPIOB->DEN|=0xFF;//Configurar pines PB[0..7] con funciones digitales
	GPIOB->DIR|=0xFF;//Configurar pines PB[0..7] como salidas
	GPIOB->DATA=0;//sacar 0 por pines PB[0..7]
	
	//SysTick es un timer descendete de 24 caracteristico de los 
	//procesadores ARM Cortex M
	SysTick->LOAD=12500000;//valor de recarga
	SysTick->VAL=12500000;//valor de comienzo de conteo
	SysTick->CTRL=0;//Limpiar bits del registro de control
	SysTick->CTRL|=((0x1<<2) //bit 2 CLKSOURCE 1: usar reloj del procesador
									|(0x0<<1)//bit 1 TICKINT 0: interrupcion por timer desabilitada
									|(0x1<<0)//bit 0 ENABLE 1: Activar timer
									); 
	while(1){
		GPIOB->DATA=(0xFF)&(~(GPIOB->DATA));//invertir leds
		while(!(SysTick->CTRL&COUNTFLAG));//Esperar hasta que la bandera de desbordamiento se active
																			//una vez leída la badera se limpia de manera automatica
		valor++;
	}
}
