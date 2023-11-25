#ifndef DS3231_H
#define DS3231_H
#include "stdint.h"
#define DS3231_ADDRESS 0x68<<1
typedef struct{
	uint8_t hours;
	uint8_t min;
	uint8_t sec;
	uint8_t date;
	uint8_t day;
	uint8_t month;
	uint8_t year;
}DS3231_t;
uint8_t BCD_to_DEC(uint8_t data);
uint8_t DEC_to_BCD(uint8_t data);
#endif
