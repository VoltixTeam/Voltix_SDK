
#include "voltix.h"
#include "voltix_gpio.h"
#include "voltix_timing.h"

/* This gets called after every reset */
void lateinit(void) {
  voltix_gpio_cfg_output(PIN_LED_CTRL);
}

/* This gets called when capacitor voltage gets low */
void suspend(void) {
  voltix_gpio_clear(PIN_LED_CTRL);
}

int main(void) {
  for (;;) {
    voltix_wait_cap_charged();
    voltix_gpio_set(PIN_LED_CTRL);
  }
}
