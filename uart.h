#ifndef __UART_H_
#define __UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

void uart1_init(void);
char uart1_Rx(void);
void uart1_Tx(int ch);

#endif