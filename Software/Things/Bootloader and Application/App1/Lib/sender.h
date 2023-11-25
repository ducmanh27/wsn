#ifndef __SENDER_H
#define __SENDER_H
#include "stdint.h"
#include "string.h"
#include "stm32f1xx_hal.h"
void send_data(uint8_t node_id, uint32_t unixtime, uint8_t temp, uint8_t x_axis, uint8_t y_axis, uint8_t room_id);
#endif
