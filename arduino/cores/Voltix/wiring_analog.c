#include <limits.h>
#include "voltix_adc.h"

#include "external/ArduinoCore-API/api/Common.h"

int analogRead(pin_size_t pinNumber) {
  voltix_adc_input_t in;
  if (voltix_adc_pin2input(&in, pinNumber) != 0)
    return INT_MIN;

  return (int)voltix_adc_read(in);
}