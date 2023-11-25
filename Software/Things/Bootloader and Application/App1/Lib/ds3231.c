#include "ds3231.h"
uint8_t BCD_to_DEC(uint8_t data)
{
	return (data>>4)*10 + (data&0x0f);
}
uint8_t DEC_to_BCD(uint8_t data)
{
	return (data/10)<<4 | (data%10);
}
