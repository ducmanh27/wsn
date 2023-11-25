#include "cli_command.h"
#include "stdint.h"
#include "response_ci.h"
#include "gettemperature_ci.h"
#include "settemperature_ci.h"
#include "cli_types.h"
 
extern const cli_command_entry_t command_entry_talbe[];

const cli_command_info_t* find_command_infor(char *cmd)
{
	const cli_command_entry_t *command_entry = command_entry_talbe;
	while (command_entry->command_info != NULL)
	{
		if (strcmp(command_entry->name, cmd) == 0)
		{
			 return command_entry->command_info;
		}
		
		command_entry++; 
	}
	return NULL;
	
}
void cli_command_excute(char *uart_buff, uint8_t length)
{
		if (uart_buff[0] == '{')
			return ;
		char *argv[20];
		uint8_t arg_num = 0;
		char *token;
	  token = strtok(uart_buff, " ");
		while (token != NULL)
		{
			argv[arg_num++] = token;
			token = strtok(NULL, " ");
		}
		const cli_command_info_t *command_infor = find_command_infor(argv[0]);
		if (command_infor != NULL)
		{
			command_infor->function(argv, arg_num);
		}
		else
		{
			response_print("[Error]: Find not found your command\n");
		}
		
}
