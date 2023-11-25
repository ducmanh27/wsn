#include "gettemperature_ci.h"
#include "response_ci.h"
#include "lm35.h"
#include "stdlib.h"
extern uint8_t temp_from_LM35;
// setTempMax {room_id} {node_id} {channel}
void gettemperature(char **argv, uint8_t arg_num)
{
	if (arg_num < 4)
	{
		response_print("[Error]: Not enough argument = %d\n", arg_num);
		return ;
	}
	if (arg_num > 4)
	{
		response_print("[Error]: Too much argument = %d\n", arg_num);
		return ;
	}
	uint8_t chanel = atoi(argv[3]);
	//Neu de nhiet do dang so thap phan %f thi no bi treo khong chay nua, chua tim ra cach khac phuc
	response_print("[Success]: Temperature = %d", temp_from_LM35);
}
