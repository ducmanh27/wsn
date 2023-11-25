#ifndef SETTEMPERATURE_H
#define SETTEMPERATURE_H
#include "stm32f1xx_hal.h"
#include "settemperature_ci.h"
void setTemperatureMax(char **argv, uint8_t arg_num);
void setTemperatureMin(char **argv, uint8_t arg_num);
#endif
