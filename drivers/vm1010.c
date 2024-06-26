#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "runtime.h"

#include "vm1010.h"
#include "voltix_adc.h"
#include "gpint.h"
#include "voltix_gpio.h"
#include "voltix_timing.h"
#include "voltix.h"

static unsigned int pin_mode;
static unsigned int pin_dout;

voltix_adc_cfg_t adc_cfg = {.acq_time = VOLTIX_ADC_ACQTIME_3US,
                            .gain = VOLTIX_ADC_GAIN2,
                            .oversampling = VOLTIX_ADC_OVERSAMPLE_DISABLED,
                            .reference = VOLTIX_ADC_REFERENCE_INTERNAL};

int vm1010_init(vm1010_cfg_t *cfg) {
  int rc;
  pin_mode = cfg->pin_mode;
  pin_dout = cfg->pin_dout;

  if ((rc = voltix_adc_pin2input(&adc_cfg.input_pos, cfg->pin_vout)) != 0)
    return rc;

  if ((rc = voltix_adc_pin2input(&adc_cfg.input_neg, cfg->pin_vbias)) != 0)
    return rc;

  voltix_gpio_cfg_output(pin_mode);
  voltix_gpio_clear(pin_mode);
  voltix_gpio_cfg_input(pin_dout, VOLTIX_GPIO_IN_NOPULL);

  voltix_adc_init();
  return rc;
}

void vm1010_exit(void) {
  /* pin alone can power the microphone */
  voltix_gpio_clear(pin_mode);
}

voltix_rc_t vm1010_sample(int16_t *result, unsigned int n_samples, unsigned int sample_interval_ticks32) {
  adc_cfg.n_samples = n_samples;
  adc_cfg.sample_interval_ticks32 = sample_interval_ticks32;

  return voltix_adc_sample(result, &adc_cfg);
}

static void wos_callback(unsigned int pin) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  xTaskNotifyIndexedFromISR(usr_task_handle, 1, EVT_DRV, eSetBits, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

voltix_rc_t vm1010_wait4sound(void) {
  int rc;
  unsigned long notification_value;
  volatile unsigned int reset_counter = runtime_stats.n_reset;

  /* Enter Wake on Sound mode */
  voltix_gpio_set(pin_mode);

  /* Wait 5ms according to datasheet */
  if ((rc = voltix_sleep_ms(5)) != 0) {
    voltix_gpio_clear(pin_mode);
    return rc;
  }

  taskENTER_CRITICAL();
  /* Check if there was a reset since we entered WoS mode */
  if (reset_counter != runtime_stats.n_reset) {
    taskEXIT_CRITICAL();
    voltix_gpio_clear(pin_mode);
    return VOLTIX_ERR_RESET;
  }

  xTaskNotifyStateClearIndexed(usr_task_handle, 1);
  gpint_register(pin_dout, VOLTIX_GPIO_LEVEL_HIGH, VOLTIX_GPIO_IN_NOPULL, wos_callback);
  taskEXIT_CRITICAL();
  xTaskNotifyWaitIndexed(1, 0xFFFFFFFF, 0xFFFFFFFF, &notification_value, portMAX_DELAY);

  /* Exit Wake on Sound mode */
  voltix_gpio_clear(pin_mode);

  if (notification_value == EVT_RESET)
    return VOLTIX_ERR_RESET;

  if (notification_value == EVT_DRV)
    return VOLTIX_SUCCESS;

  return VOLTIX_ERR_GENERIC;
}