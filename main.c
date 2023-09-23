#include "uart.h"

#define PIN5								 (1U<<5)
#define LED_PIN 							PIN5

char rX;
int main(void){
	RCC->AHB1ENR |= (1U<<0);
	//Set PA5 as output 
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	
uart1_init();
	
while(1){
		rX = uart1_Rx();
	if(rX == 'A') GPIOA->ODR |= LED_PIN;
	else if(rX == 'B') GPIOA->ODR &= ~LED_PIN;
		
	}
}
