#include "TM4C123.h"                    // Device header

#define DLY_TIME 0x2FFFFF





void uart_init(void);
void uart_send(char c);
void delay_ms(int time_ms);
int a;
int main(){
	SystemCoreClockUpdate();
	a=SystemCoreClock;
	uart_init();
	while(1){
		uart_send('g');
		uart_send('\n');
		delay_ms(DLY_TIME);
	}
}

void delay_ms(int time_ms){
	int i=0;
	for(i=0;i<time_ms;i++);
}

#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_LCRH_WLEN_8        0x00000060  // 8 bit word length
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_CTL_UARTEN         0x00000001  // UART Enable
#define SYSCTL_RCGC1_UART0      0x00000001  // UART0 Clock Gating Control
#define SYSCTL_RCGC2_GPIOA      0x00000001  // port A Clock Gating Control

void uart_init(void){
	SYSCTL->RCGC1|= SYSCTL_RCGC1_UART0; 	// Encender periferico UART0
  SYSCTL->RCGC2|= SYSCTL_RCGC2_GPIOA; 	// Encender periferico GPIOA
  UART0->CTL &= ~UART_CTL_UARTEN;      	// Desabilitar UART0 (para configurar)
  UART0->IBRD = 27;                   	// Divisor de frecuencia Entero 
																				// IBRD = int(50,000,000 / (16 * 115200)) = int(27.12673611)
  UART0->FBRD= 8;                    		// Divisor de frecuencia faccional
																				// FBRD = round(0.12673611 * 64) = 8                    
  UART0->LCRH = (UART_LCRH_WLEN_8|UART_LCRH_FEN); // 8 bits de datos (sin sin bit de paridad, un bit de paro)
  UART0->CTL|= UART_CTL_UARTEN;		// habiltar UART
  GPIOA->AFSEL |= 0x03;						// funcion alternativa en PA[1..0]
  GPIOA->DEN |= 0x03;             // usar drivers digitales en PA[1..0]
  GPIOA->PCTL = (GPIOA->PCTL&0xFFFFFF00)+0x00000011;// configurar  PA[1..0] como pines UART
  GPIOA->AMSEL &= ~0x03;          // deshabilitar funciones analogicas en PA[1..0]
}

void uart_send(char c){
	while((UART0->FR&UART_FR_TXFF) != 0){}//esperar hasta que el buffer no este lleno
  UART0->DR = c;//poner dato en el buffer de transmisison
}


