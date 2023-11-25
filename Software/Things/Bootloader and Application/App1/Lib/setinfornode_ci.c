#include "setinfornode_ci.h"

extern uint8_t node_id;
extern uint8_t x_axis;
extern uint8_t y_axis;
extern uint8_t room_id;

// setInfoNode room_id node_id x_axis y_axis
// Example setInfoNode 1 2 99 99
void setInforNode(char **argv, uint8_t arg_num)
{
	if (arg_num < 5)
	{
		response_print("[Error]: Not enough argument = %d", arg_num);
		return ;
	}
	if (arg_num > 5)
	{
		response_print("[Error]: Too much argument = %d", arg_num);
		return ;
	}
	x_axis = atoi(argv[3]);
	y_axis = atoi(argv[4]);
	
	response_print("[Success]: Infor was changed succesfully");
}
