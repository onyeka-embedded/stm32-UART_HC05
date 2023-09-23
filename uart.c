#include "uart.h"

#define	GPIOAEN				(1U<<0)	
#define	UART1EN				(1U<<4)	

#define CR1_RE				(1U<<2)
#define CR1_TE				(1U<<3)
#define CR1_UE				(1U<<13)

#define SR_TXE				(1U<<7)
#define SR_RXNE				(1U<<5)

#define SYS_FREQ					16000000
#define APB1_CLK					SYS_FREQ

#define BAUDRATE				9600

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudRate);
//static uint16_t compute_uart_div(uint32_t periphClk, uint32_t baudRate);

void uart1_init(void){

/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;
/* Set USART2_TX(PA9) Pins to Alternate function */
	GPIOA->MODER |= (1U<<19);
	GPIOA->MODER &= ~(1U<<18);
	/* Set USART2_RX(PA10) Pins to Alternate function */
	GPIOA->MODER |= (1U<<21);
	GPIOA->MODER &= ~(1U<<20);
	
/* Set USART2_RX(PA10) Pin to Alternate function type UART2 */
	GPIOA->AFR[1] |= (1U<<8);
	GPIOA->AFR[1] |= (1U<<9);
	GPIOA->AFR[1] |= (1U<<10);
	GPIOA->AFR[1] &= ~(1U<<11);
	/* Set USART2_=TX(PA9) Pin to Alternate function type UART2 */
	GPIOA->AFR[1] |= (1U<<4);
	GPIOA->AFR[1] |= (1U<<5);
	GPIOA->AFR[1] |= (1U<<6);
	GPIOA->AFR[1] &= ~(1U<<7);
	
/********Configure uart module********/
/* Enable clock access to UART */
	RCC->APB2ENR |= UART1EN;
	
	/* Set Baudrate */
	uart_set_baudrate(USART1, APB1_CLK, BAUDRATE);
	
/* Enable UART TX AND RX */
	USART1->CR1 |= (CR1_RE | CR1_TE);
	
	/* Enable UART module */
	USART1->CR1 |= CR1_UE;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudRate){

	USARTx->BRR = ((periphClk + (baudRate/2U))/baudRate); //compute_uart_div(periphClk, baudRate);
}

/*
static uint16_t compute_uart_div(uint32_t periphClk, uint32_t baudRate){
	
 return((periphClk + (baudRate/2U))/baudRate); 
		// return periphClk /  baudRate; 
} 
*/

char uart1_Rx(void){
	
	/* Wait till data is recieved */
	while(!(USART1->SR & SR_RXNE));
	/* Return the received data */
	return (char)(USART1->DR);
}

void uart1_Tx(int ch){
	 /* Make sure transmit data register is empty */
	 while(!(USART1->SR & SR_TXE));
	 /*Write to transfer resgister*/
	 USART1->DR = (ch & 0xFF);
 }

