
#include "voltix.h"
#include "voltix_gpio.h"
#include "voltix_timing.h"
#include "printf.h"

int main(void) {
  unsigned int counter = 0;
  for (;;) {
    printf("Counter: %u\r\n", counter++);
    voltix_sleep_ms(100);
  }
}
