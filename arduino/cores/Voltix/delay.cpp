#include "voltix.h"
#include "voltix_timing.h"

#include "external/ArduinoCore-API/api/Common.h"

void delay(long unsigned int ms) {
  voltix_sleep_ms(ms);
}

void delayMicroseconds(long unsigned us) {
  voltix_delay_us(us);
}