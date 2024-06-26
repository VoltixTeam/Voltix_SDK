
#include "voltix.h"
#include "voltix_gpio.h"
#include "voltix_timing.h"
#include "printf.h"

static unsigned int counter = 0;

/* Executes after every reset */
void lateinit(void) {
  voltix_gpio_cfg_output(PIN_LED_CTRL);
  printf("reset\r\n");
}

/* Executes when capacitor voltage gets low */
void suspend(void) {
  voltix_gpio_clear(PIN_LED_CTRL);
  printf("suspend\r\n");
}

/* Executes when capacitor voltage has recovered and after reset */
void resume(void) {
  voltix_gpio_set(PIN_LED_CTRL);
  printf("resume\r\n");
}

/* Executes once after programming the device */
void bootstrap(void) {
  printf("bootstrap\r\n");
}

int main(void) {
  voltix_gpio_set(PIN_LED_CTRL);
  printf("main start\r\n");
  for (;;) {
    voltix_sleep_ms(1000);
    printf("main loop %u\r\n", counter++);
  }
}
