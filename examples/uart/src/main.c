#include "voltix.h"
#include "voltix_timing.h"
#include "voltix_uart.h"
#include "printf.h"

/* This gets called after every reset */
void lateinit(void) {
  voltix_uart_init(PIN_D1, VOLTIX_UART_BAUDRATE_1000000);
  printf("Hello Voltix!\r\n");
}

int main(void) {
  int counter = 0;
  for (;;) {
    printf("Loop: %d\r\n", counter++);
    voltix_sleep_ms(1000);
  }
}