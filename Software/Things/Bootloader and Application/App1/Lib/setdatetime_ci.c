#include "setdatetime_ci.h"
extern uint8_t SECOND;
extern uint8_t MINUTE;
extern uint8_t HOUR;
extern uint8_t WEEKDAY;
extern uint8_t MONTH;
extern uint8_t YEAR;
extern uint8_t DATE;
extern uint8_t flag_update_time;
// setDateTime room_id node_id (HOUR) (MINUTE) (SECOND) (WEEKDAY) DATE  MONTH YEAR
// Example: setDateTime 1 2 24 0 0 1 32 17 35
void setDateTime(char **argv, uint8_t arg_num)
{
	if (arg_num < 10)
	{
		response_print("[Error]: Not enough argument = %d", arg_num);
		return ;
	}
	if (arg_num > 10)
	{
		response_print("[Error]: too much argument = %d", arg_num);
		return ;
	}
	flag_update_time = 1;
	HOUR = atoi(argv[3]);
	MINUTE = atoi(argv[4]);
	SECOND = atoi(argv[5]);
	WEEKDAY = atoi(argv[6]);
	DATE = atoi(argv[7]);
	MONTH = atoi(argv[8]);
	YEAR = atoi(argv[9]);
	
	response_print("Time was changed succesfully");

}
