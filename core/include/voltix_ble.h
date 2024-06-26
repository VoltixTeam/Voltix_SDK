/**
 * @defgroup ble Bluetooth Low Energy
 *  @{
 */
#ifndef __VOLTIX_BLE_H__
#define __VOLTIX_BLE_H__

#include <stdint.h>
#include <stdio.h>

#include "voltix.h"

#define VOLTIX_BLE_ADV_MNF_NORDIC 0x0059

/**
 * @brief Type of advertisement
 *
 */
typedef enum {
  /** Undirected, connectable advertisement. */
  ADV_IND = 0,
  /** Directed, connectable advertisement. */
  ADV_DIRECT_IND = 1,
  /** Undirected, unconnectable advertisement. */
  ADV_NONCONN_IND = 2,
  /** Scan request. */
  SCAN_REQ = 3,
  /** Scan response. */
  SCAN_RSP = 4,
  /** Connection request. */
  CONNECT_REQ = 5,
  /** Scannable undirected advertisement. */
  ADV_SCAN_IND = 6,
} voltix_adv_pdu_type_t;

typedef enum { ADV_CH_37 = 37, ADV_CH_38 = 38, ADV_CH_39 = 39, ADV_CH_ALL = 255 } voltix_adv_ch_t;

typedef struct {
  uint8_t addr_bytes[6];
} __attribute__((__packed__)) voltix_ble_adv_addr_t;

typedef struct {
  voltix_adv_pdu_type_t pdu_type : 4;
  unsigned int rfu : 1;
  unsigned int chsel : 1;
  unsigned int txadd : 1;
  unsigned int rxadd : 1;
  uint8_t len;
} __attribute__((__packed__)) voltix_ble_adv_header_t;

/**
 * @brief Common packet format for some ADV PDU types
 *
 */
typedef struct {
  voltix_ble_adv_header_t header;
  uint8_t adv_addr[6];
  uint8_t payload[31];
} __attribute__((__packed__)) voltix_adv_pck_t;

/** BLE advertising configuration. */
typedef struct {
  /** Pointer to advertising address. */
  const uint8_t *addr;
  /** Advertising name of the device. */
  const char *name;
  /** Size of 'name' in bytes. */
  size_t name_len;
  /** Pointer to custom payload data. */
  void *data;
  /** Size of 'data' in bytes. */
  size_t data_len;
  /** Manufacturer ID. */
  uint16_t manufacturer_id;
} voltix_ble_adv_cfg_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Sets up the internal packet buffer for advertisting with given name, address and payload size.
 *
 * @param adv_addr Pointer to address buffer.
 * @param adv_name Advertising name of the device.
 * @param data Pointer to payload.
 * @param data_len Size of the payload.
 *
 * @retval VOLTIX_SUCCESS       Successfully prepared advertisement.
 * @retval VOLTIX_ERR_OVERFLOW  At least one argument is too long.
 */
voltix_rc_t voltix_ble_adv_cfg(voltix_ble_adv_cfg_t *cfg);

/**
 * @brief Advertises the given payload on the selected channel(s)
 *
 * @param ch Channel(s) on which advertisement should be sent.
 *
 * @retval VOLTIX_SUCCESS       Advertisement successfully sent.
 * @retval VOLTIX_ERR_RESET     Reset occured while sending advertisement.
 * @retval VOLTIX_ERR_TEARDOWN  Teardown occured while sending advertisement.
 */
voltix_rc_t voltix_ble_advertise(voltix_adv_ch_t ch);

/**
 * @brief Initializes BLE driver.
 *
 */
void voltix_ble_init(void);

#ifdef __cplusplus
}
#endif

#endif /** @} __VOLTIX_BLE_H__ */