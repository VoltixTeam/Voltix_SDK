/**
 * @defgroup timing Timing functionality
 * @{
 */

#ifndef __VOLTIX_TIMING_H_
#define __VOLTIX_TIMING_H_

#include <stdint.h>
#include "voltix.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the LF clock. Must be called once after reset before any sleep/delay calls.
 *
 */
void voltix_timing_init(void);

/**
 * @brief Waits in a low power mode for the specified number of ticks on a 32kHz clock.
 *
 * Starts a timer and blocks on a notification. The idle task will keep the system in a low power mode. Function may
 * return earlier than requested if the power runs out and a reset occurs.
 *
 * @param ticks_32k Number of ticks on a 32kHz clock to sleep for.
 *
 * @retval VOLTIX_SUCCESS                 Successfully passed specified time sleeping.
 * @retval VOLTIX_ERR_RESET              Reset occured while sleeping.
 */
voltix_rc_t voltix_sleep_ticks(unsigned int ticks_32k);

/**
 * @brief Waits in a low power mode for the specified time.
 *
 * Starts a timer and blocks on a notification. The idle task will keep the system in a low power mode. Function may
 * return earlier than requested if the power runs out and a reset occurs.
 *
 * @param ms Number of milliseconds to sleep for.
 *
 * @retval VOLTIX_SUCCESS                 Successfully passed specified time sleeping.
 * @retval VOLTIX_ERR_RESET              Reset occured while sleeping.
 */
voltix_rc_t voltix_sleep_ms(unsigned int ms);

/**
 * @brief Busy waits for specified number of microseconds.
 *
 * Keeps the CPU busy for the specified time. Consumes significant energy while waiting. Note that the time passed in
 * the function can be much longer than specified when execution is suspended due to low energy.
 *
 * @param us Number of microseconds to wait.
 */
void voltix_delay_us(unsigned int us);

/**
 * @brief Busy waits for specified number of milliseconds.
 *
 * Keeps the CPU busy for the specified time. Consumes significant energy while waiting. Note that the time passed in
 * the function can be much longer than specified when execution is suspended due to low energy.
 *
 * @param ms Number of milliseconds to wait.
 */
void voltix_delay_ms(unsigned int ms);

/**
 * @brief Reads the current value of the internal RTC-driven timer.
 *
 * Reads a 56-bit wide counter driven by a 32kHz clock. Return code indicates whether a reset has occured since the last
 * call to the function.
 *
 * @param dst Pointer to destination buffer.
 *
 * @retval VOLTIX_SUCCESS   No reset since the last call to the function.
 * @retval VOLTIX_ERR_RESET Reset since the last call to the function.
 *
 */
voltix_rc_t voltix_timing_now(uint64_t *dst);

#ifdef __cplusplus
}
#endif

#endif /** @} __VOLTIX_TIMING_H_ */