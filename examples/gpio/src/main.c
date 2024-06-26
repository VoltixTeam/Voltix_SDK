#include "voltix.h"
#include "voltix_gpio.h"
#include "voltix_timing.h"

#define PIN_BUTTON PIN_D6

void lateinit(void) {
  voltix_gpio_cfg_output(PIN_LED_CTRL);
}

int main(void) {
  for (;;) {
    /* Wait for low level on button */
    voltix_gpio_wait_level(PIN_BUTTON, VOLTIX_GPIO_LEVEL_LOW, VOLTIX_GPIO_IN_PULLUP);
    /* Disable the pullup to save energy */
    voltix_gpio_cfg_disable(PIN_BUTTON);

    /* Blink LED for ~150us */
    voltix_gpio_set(PIN_LED_CTRL);
    voltix_sleep_ticks(5);
    voltix_gpio_clear(PIN_LED_CTRL);
    /* Wait until capacitor is recharged */
    voltix_wait_cap_charged();
  }
}