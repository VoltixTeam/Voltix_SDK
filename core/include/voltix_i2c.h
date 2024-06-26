/**
 * @defgroup i2c I2C controller driver
 * @{
 */

#ifndef __VOLTIX_I2C_H_
#define __VOLTIX_I2C_H_

#include <stddef.h>
#include <stdint.h>

#include "voltix.h"

/** I2C SCL frequency. */
typedef enum {
  /** 100kHz SCL frequency. */
  VOLTIX_I2C_FREQ_100K = 0x01980000UL,
  /** 250kHz SCL frequency. */
  VOLTIX_I2C_FREQ_250K = 0x04000000UL,
  /** 400kHz SCL frequency. */
  VOLTIX_I2C_FREQ_400K = 0x06400000UL,

} voltix_i2c_freq_t;

enum {
  /** I2C communication error. */
  VOLTIX_ERR_COMMI2C = -(VOLTIX_RC_I2C_BASE + 1),
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes I2C peripheral. Must be called once after reset before I2C is used.
 */
void voltix_i2c_init(void);

/**
 * @brief Transmits the given data to an I2C peripheral.
 *
 * @param dev_addr I2C address of peripheral device.
 * @param data Pointer to data.
 * @param n_data Size of data buffer.
 *
 * @retval VOLTIX_SUCCESS           Write completed successfully.
 * @retval VOLTIX_ERR_COMMI2C  I2C communication error.
 */
voltix_rc_t voltix_i2c_write(uint8_t dev_addr, uint8_t* data, size_t n_data);

/**
 * @brief Reads the specified number of bytes from an I2C peripheral.
 *
 * @param buffer Pointer to a destination buffer where data gets stored.
 * @param n_data Number of bytes to read.
 * @param dev_addr I2C address of peripheral device.
 *
 * @retval VOLTIX_SUCCESS           Read completed successfully.
 * @retval VOLTIX_ERR_COMMI2C  I2C communication error.
 */
voltix_rc_t voltix_i2c_read(uint8_t* buffer, size_t n_data, uint8_t dev_addr);

/**
 * @brief Transmits the given data to an I2C peripheral.
 *
 * Transmits the given data to an I2C peripheral within a critical section. Should only be used for short transfers as
 * it will drain the capacitor and sink the system without checkpointing if energy becomes low.
 *
 * @param dev_addr I2C address of peripheral device.
 * @param data Pointer to data.
 * @param n_data Size of data buffer.
 *
 * @retval VOLTIX_SUCCESS           Write completed successfully.
 * @retval VOLTIX_ERR_COMMI2C  I2C communication error.
 */
voltix_rc_t voltix_i2c_write_atomic(uint8_t dev_addr, uint8_t* data, size_t n_data);

/**
 * @brief Reads the specified number of bytes from an I2C peripheral.
 *
 * Reads the specified number of bytes from an I2C peripheral within a critical section. Should only be used for short
 * transfers as it will drain the capacitor and sink the system without checkpointing if energy becomes low.
 *
 * @param buffer Pointer to a destination buffer where data gets stored.
 * @param n_data Number of bytes to read.
 * @param dev_addr I2C address of peripheral device.
 *
 * @retval VOLTIX_SUCCESS           Read completed successfully.
 * @retval VOLTIX_ERR_COMMI2C  I2C communication error.
 */
voltix_rc_t voltix_i2c_read_atomic(uint8_t* buffer, size_t n_data, uint8_t dev_addr);

/**
 * @brief Sets the I2C clock frequency.
 *
 * @param freq
 */
void voltix_i2c_set_freq(voltix_i2c_freq_t freq);

#ifdef __cplusplus
}
#endif

#endif /* @} __VOLTIX_I2C_H_ */