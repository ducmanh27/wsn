#include "cli_command_table.h"
#include "cli_types.h"
#include "gettemperature_ci.h"
#include "settemperature_ci.h"
#include "setdatetime_ci.h"
#include "setinfornode_ci.h"

const cli_command_info_t command_info_gettemp =
{
	gettemperature,
	"get temp from LM35"
};

const cli_command_info_t command_info_settemp_max =
{
	setTemperatureMax,
	"set temp from LM35"
};
const cli_command_info_t command_info_setdate_time =
{
	setDateTime,
	"set time for sensor node"
};
const cli_command_info_t command_info_set_infor_node =
{
	setInforNode,
	"set infor about node_id, room_id, x_axis, y_axis for node"
};
const cli_command_entry_t command_entry_talbe[] = 
{
	{"gettemp", &command_info_gettemp},
	{"setTempMax",&command_info_settemp_max},
	{"setDateTime",&command_info_setdate_time},
	{"setInfoNode",&command_info_set_infor_node},
	{NULL, NULL}
	
};
