#ifndef LM35_H
#define	LM35_H
#include "stdint.h"
typedef enum 
{
	CHANNEL_1 = 1,
	CHANNEL_2,
	CHANNEL_3
}channel_t;
uint8_t LM35_GetTemp(channel_t channel);
#endif
