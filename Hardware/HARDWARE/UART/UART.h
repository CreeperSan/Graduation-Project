#ifndef __UART_H
#define __UART_H

#include "stm32f4xx.h"
#include "stdio.h"
#include "sys.h"

void UART_Init(void);
void UART_Send_Byte(uint8_t dat);
void UART_Send_String(char *dat);
int fputc(int ch, FILE *f);
void UART_Reset(void);

#endif
