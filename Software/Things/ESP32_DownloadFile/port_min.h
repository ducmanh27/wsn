#include "esp32-hal.h"
extern "C"
{
  #include "min.h"
}
#define MIN_Serial Serial2


void min_tx_start(uint8_t port)
{
	
}
void min_tx_finished(uint8_t port)
{
	
}
void min_tx_byte(uint8_t port, uint8_t byte)
{
  MIN_Serial.write(byte);
  
}
uint16_t min_tx_space(uint8_t port)
{
	return 512;
}
uint32_t min_time_ms(void)
{
	return millis();
}