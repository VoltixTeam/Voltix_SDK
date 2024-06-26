
#include "voltix.h"
#include "voltix_gpio.h"
#include "voltix_timing.h"
#include "printf.h"
#include "voltix_max20361.h"
#include "voltix_i2c.h"

/* I2C device address of MAX20361. */
#define DEV_ADDR 0x15
/* Address of ID register. */
#define REG_ADDR 0x0

void lateinit(void) {
  voltix_i2c_init();
}

int main(void) {
  int rc;
  uint8_t rx_buf;
  uint8_t tx_buf = REG_ADDR;

  for (;;) {
    /* Write address of register to be read to device. */
    voltix_i2c_write(DEV_ADDR, &tx_buf, 1);
    /* Read register value. */
    rc = voltix_i2c_read(&rx_buf, 1, DEV_ADDR);
    printf("RC: %d, Value: %02X\r\n", rc, rx_buf);

    voltix_sleep_ms(1000);
  }
}
