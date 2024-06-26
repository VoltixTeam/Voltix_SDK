#include <stdint.h>
#include "nrf.h"
#include "voltix_gpio.h"

#include "FreeRTOS.h"
#include "task.h"

#include "voltix_uart.h"

void voltix_uart_init(uint32_t pseltxd, voltix_uart_baudrate_t baudrate) {
  NRF_UART0->PSEL.TXD = pseltxd;
  voltix_gpio_cfg_input(pseltxd, VOLTIX_GPIO_IN_PULLUP);
  NRF_UART0->BAUDRATE = baudrate;
}

void voltix_uart_set_baudrate(voltix_uart_baudrate_t baudrate) {
  NRF_UART0->BAUDRATE = baudrate;
}

void _putchar(char character) {
  taskENTER_CRITICAL();
  NRF_UART0->ENABLE = UART_ENABLE_ENABLE_Enabled;
  NRF_UART0->TXD = character;
  NRF_UART0->TASKS_STARTTX = 1UL;
  while (NRF_UART0->EVENTS_TXDRDY == 0) {
  };
  NRF_UART0->EVENTS_TXDRDY = 0;
  NRF_UART0->TASKS_STOPTX = 1UL;
  NRF_UART0->ENABLE = UART_ENABLE_ENABLE_Disabled;
  taskEXIT_CRITICAL();
}