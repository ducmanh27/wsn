#include "sender.h"
#include "response_ci.h"
/**
 * @brief make msg that included measured values and send to esp32
 *{
  "operator": "sensorData",
  "status": 0,
  "id ": 3,
  "info": {
    "temp": 60.52,
    "x_axis": 50,
		"y_axis": 50,
		"room_id": 1,
    "time": 1655396252
  }
 */
void send_data(uint8_t node_id, uint32_t unixtime, uint8_t temp, uint8_t x_axis, uint8_t y_axis, uint8_t room_id)
{
		//format json
		char jsonBuffer[100];
		//sprintf(jsonBuffer,"{\"operator\": \"sensorData\",  \"status\": 0, \"id\": 3, \"info\":{\"node_id\":%d,\"unixtime\":%d,\"temp\":%d,\"x_axis\":%d,\"y_axis\":%d,\"room_id\":%d}}",node_id , unixtime, temp, x_axis, y_axis, room_id);
	  sprintf(jsonBuffer,"{\"node_id\":%d,\"unixtime\":%d,\"temp\":%d,\"x_axis\":%d,\"y_axis\":%d,\"room_id\":%d}",node_id , unixtime, temp, x_axis, y_axis, room_id);
	// ,\"temp\":%d}\"x_axis\":%d,\"y_axis\":%d,\"room_id\":%d\\n
		response_print(jsonBuffer);
		//send to esp by UART
}
