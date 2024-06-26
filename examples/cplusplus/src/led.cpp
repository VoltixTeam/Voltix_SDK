#include "voltix_gpio.h"
#include "led.hpp"

LED::LED(unsigned int pin) : _pin(pin) {
  voltix_gpio_cfg_output(_pin);
};

void LED::on(void) {
  voltix_gpio_set(_pin);
}

void LED::off(void) {
  voltix_gpio_clear(_pin);
}