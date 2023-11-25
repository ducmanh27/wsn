#ifndef UART_H
#define UART_H

#include "string.h"
#include "stdint.h"



void recv_data(uint8_t data_rx);
void uart_handle(void);
void uart_init(void);
#endif
