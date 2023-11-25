#include "lm35.h"

uint8_t LM35_GetTemp(channel_t channel)
{
	float temp = 10;
	if (channel == 0)
			temp = 20;
	if (channel == 1)
			temp = 50;
	return temp;
}
