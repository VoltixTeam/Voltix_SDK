#include "voltix.h"
#include "voltix_timing.h"
#include "voltix_spic.h"
#include "printf.h"

uint8_t tx_data[] = {0xCA, 0xFE, 0xD0, 0x0D};
uint8_t rx_data[sizeof(tx_data)];

void lateinit(void) {
  voltix_spic_cfg_t cfg = {.frequency = VOLTIX_SPIC_FREQUENCY_M8,
                           .mode = VOLTIX_SPIC_MODE0_CPOL0_CPHA0,
                           .order = VOLTIX_SPIC_ORDER_LSBFIRST,
                           .pin_cs = PIN_D7,
                           .pin_sck = PIN_D8,
                           .pin_copi = PIN_D10,
                           .pin_cipo = PIN_D9};
  voltix_spic_init(&cfg);
}

int main(void) {
  for (;;) {
    voltix_spic_transfer(tx_data, sizeof(tx_data), rx_data, sizeof(rx_data));
    for (int i = 0; i < 4; i++) {
      printf("%02X", rx_data[i]);
    }
    printf("\r\n");
    voltix_sleep_ms(1000);
  }
}