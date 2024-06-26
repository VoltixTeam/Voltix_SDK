
#include "voltix.h"
#include "voltix_ble.h"
#include "voltix_timing.h"

const uint8_t adv_address[] = {0x01, 0xEE, 0xC0, 0xFF, 0x03, 0x02};
const char adv_name[] = "VOLTIX";

static struct {
  unsigned int counter;
} ble_data;

void lateinit(void) {
  voltix_ble_init();
}

int main() {
  voltix_ble_adv_cfg_t adv_cfg = {.addr = adv_address,
                                  .name = adv_name,
                                  .name_len = 6,
                                  .data = &ble_data,
                                  .data_len = sizeof(ble_data),
                                  .manufacturer_id = VOLTIX_BLE_ADV_MNF_NORDIC};
  voltix_ble_adv_cfg(&adv_cfg);
  ble_data.counter = 0;
  for (;;) {
    voltix_wait_cap_charged();
    voltix_ble_advertise(ADV_CH_ALL);
    ble_data.counter++;
    /* Sleep at least 250ms before next advertising round */
    voltix_sleep_ms(250);
  }
}
