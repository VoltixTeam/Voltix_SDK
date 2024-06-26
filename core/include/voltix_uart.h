/**
 * @defgroup uart UART driver
 * @{
 */

#ifndef __VOLTIX_UART_H_
#define __VOLTIX_UART_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  /** 1200 baud (actual rate: 1205) */
  VOLTIX_UART_BAUDRATE_1200 = 0x0004F000UL,
  /** 2400 baud (actual rate: 2396) */
  VOLTIX_UART_BAUDRATE_2400 = 0x0009D000UL,
  /** 4800 baud (actual rate: 4808) */
  VOLTIX_UART_BAUDRATE_4800 = 0x0013B000UL,
  /** 9600 baud (actual rate: 9598) */
  VOLTIX_UART_BAUDRATE_9600 = 0x00275000UL,
  /** 14400 baud (actual rate: 14414) */
  VOLTIX_UART_BAUDRATE_14400 = 0x003B0000UL,
  /** 19200 baud (actual rate: 19208) */
  VOLTIX_UART_BAUDRATE_19200 = 0x004EA000UL,
  /** 28800 baud (actual rate: 28829) */
  VOLTIX_UART_BAUDRATE_28800 = 0x0075F000UL,
  /**  31250 baud */
  VOLTIX_UART_BAUDRATE_31250 = 0x00800000UL,
  /** 38400 baud (actual rate: 38462) */
  VOLTIX_UART_BAUDRATE_38400 = 0x009D5000UL,
  /** 56000 baud (actual rate: 55944) */
  VOLTIX_UART_BAUDRATE_56000 = 0x00E50000UL,
  /** 57600 baud (actual rate: 57762) */
  VOLTIX_UART_BAUDRATE_57600 = 0x00EBF000UL,
  /** 76800 baud (actual rate: 76923) */
  VOLTIX_UART_BAUDRATE_76800 = 0x013A9000UL,
  /** 115200 baud (actual rate: 115942) */
  VOLTIX_UART_BAUDRATE_115200 = 0x01D7E000UL,
  /** 230400 baud (actual rate: 231884) */
  VOLTIX_UART_BAUDRATE_230400 = 0x03AFB000UL,
  /** 250000 baud */
  VOLTIX_UART_BAUDRATE_250000 = 0x04000000UL,
  /** 460800 baud (actual rate: 470588) */
  VOLTIX_UART_BAUDRATE_460800 = 0x075F7000UL,
  /** 921600 baud (actual rate: 941176) */
  VOLTIX_UART_BAUDRATE_921600 = 0x0EBED000UL,
  /** 1Mega baud */
  VOLTIX_UART_BAUDRATE_1000000 = 0x10000000UL,
} voltix_uart_baudrate_t;

/**
 * @brief Initializes UART peripheral.
 *
 * @param pseltxd UART TX pin.
 * @param baudrate UART baudrate.
 */
void voltix_uart_init(uint32_t pseltxd, voltix_uart_baudrate_t baudrate);

/**
 * @brief Sets baudrate of UART peripheral.
 *
 * @param baudrate UART baudrate.
 */
void voltix_uart_set_baudrate(voltix_uart_baudrate_t baudrate);

/**
 * @brief Outputs a character over UART.
 *
 * Blocks in a critical section until done.
 *
 */
void _putchar(char character);

/**
 * @brief Outputs a character over UART.
 *
 * Blocks in a critical section until done.
 *
 */
#define voltix_putc(x) _putchar(x)

#ifdef __cplusplus
}
#endif

#endif /** @} __VOLTIX_UART_H_ */