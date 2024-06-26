#include "voltix.h"
#include "voltix_gpio.h"

#include "Arduino.h"
#include "external/ArduinoCore-API/api/Common.h"

void pinMode(pin_size_t pinNumber, PinMode pinMode) {
  switch (pinMode) {
    case INPUT:
      voltix_gpio_cfg_input(pinNumber, VOLTIX_GPIO_IN_NOPULL);
      break;

    case INPUT_PULLUP:
      voltix_gpio_cfg_input(pinNumber, VOLTIX_GPIO_IN_PULLUP);

      break;

    case INPUT_PULLDOWN:
      voltix_gpio_cfg_input(pinNumber, VOLTIX_GPIO_IN_PULLDOWN);

      break;

    case OUTPUT:
      voltix_gpio_cfg_output(pinNumber);

      break;

    default:
      break;
  }
}

void digitalWrite(pin_size_t pinNumber, PinStatus status) {
  switch (status) {
    case LOW:
      voltix_gpio_clear(pinNumber);
      break;

    default:
      voltix_gpio_set(pinNumber);
      break;
  }

  return;
}