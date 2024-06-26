#include "VoltixBLE.h"
#include "voltix_ble.h"

#include <cstring>

const uint8_t adv_address[] = {0x01, 0xEE, 0xC0, 0xFF, 0x03, 0x02};

void VoltixBLE::begin(const char adv_name[], void *data, size_t data_len) {
  voltix_ble_init();
  voltix_ble_adv_cfg_t cfg = {.addr = adv_address,
                              .name = adv_name,
                              .name_len = strlen(adv_name) - 1,
                              .data = data,
                              .data_len = data_len,
                              .manufacturer_id = VOLTIX_BLE_ADV_MNF_NORDIC};
  voltix_ble_adv_cfg(&cfg);
}

void VoltixBLE::advertise() {
  voltix_ble_advertise(ADV_CH_ALL);
}

VoltixBLE BLE;