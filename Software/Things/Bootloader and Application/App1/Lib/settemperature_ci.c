#include "settemperature_ci.h"
#include "response_ci.h"
#include "stdlib.h"
// setTempMax {room_id} {node_id} {temp_set}
extern uint8_t temp_threshold ;

void setTemperatureMax(char **argv, uint8_t arg_num)
{
	if (arg_num < 4)
	{
		response_print("[Error]: Not enough argument = %d", arg_num);
		return ;
	}
	if (arg_num > 4)
	{
		response_print("[Error]: too much argument = %d", arg_num);
		return ;
	}
	uint8_t chanel = atoi(argv[3]);
	response_print("value: %d\n", chanel);
	temp_threshold = chanel;
	response_print("[Success]: Temperature is changed, value = %d", temp_threshold);
}
void setTemperatureMin(char **argv, uint8_t arg_num)
{
}
