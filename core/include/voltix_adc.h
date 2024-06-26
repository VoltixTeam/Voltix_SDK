/**
 * @defgroup adc ADC driver
 * @{
 */

#ifndef __VOLTIX_ADC_H_
#define __VOLTIX_ADC_H_

#include <stdint.h>
#include "voltix.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  /** Input not connected. */
  VOLTIX_ADC_INPUT_NC = 0,
  /** Capacitor voltage. */
  VOLTIX_ADC_INPUT_VCAP = 6,
  /** Analog input A0 */
  VOLTIX_ADC_INPUT_A0 = 3,
  /** Analog input A1 */
  VOLTIX_ADC_INPUT_A1 = 4,
} voltix_adc_input_t;

typedef enum {
  /** 8 bit resolution */
  VOLTIX_ADC_RESOLUTION_8BIT = 0UL,
  /** 10 bit resolution */
  VOLTIX_ADC_RESOLUTION_10BIT = 1UL,
  /** 12 bit resolution */
  VOLTIX_ADC_RESOLUTION_12BIT = 2UL,
  /** 14 bit resolution */
  VOLTIX_ADC_RESOLUTION_14BIT = 3UL
} voltix_adc_resolution_t;

typedef enum {
  /** No oversampling. */
  VOLTIX_ADC_OVERSAMPLE_DISABLED = 0UL,
  /** Oversample 2x. */
  VOLTIX_ADC_OVERSAMPLE_2X = 1UL,
  /** Oversample 4x. */
  VOLTIX_ADC_OVERSAMPLE_4X = 2UL,
  /** Oversample 8x. */
  VOLTIX_ADC_OVERSAMPLE_8X = 3UL,
  /** Oversample 16x. */
  VOLTIX_ADC_OVERSAMPLE_16X = 4UL,
  /** Oversample 32x. */
  VOLTIX_ADC_OVERSAMPLE_32X = 5UL,
  /** Oversample 64x. */
  VOLTIX_ADC_OVERSAMPLE_64X = 6UL,
  /** Oversample 128x. */
  VOLTIX_ADC_OVERSAMPLE_128X = 7UL,
  /** Oversample 256x. */
  VOLTIX_ADC_OVERSAMPLE_256X = 8UL
} voltix_adc_oversample_t;

typedef enum {
  /** Gain factor 1/6. */
  VOLTIX_ADC_GAIN1_6 = 0UL,
  /** Gain factor 1/5. */
  VOLTIX_ADC_GAIN1_5 = 1UL,
  /** Gain factor 1/4. */
  VOLTIX_ADC_GAIN1_4 = 2UL,
  /** Gain factor 1/3. */
  VOLTIX_ADC_GAIN1_3 = 3UL,
  /** Gain factor 1/2. */
  VOLTIX_ADC_GAIN1_2 = 4UL,
  /** Gain factor 1. */
  VOLTIX_ADC_GAIN1 = 5UL,
  /** Gain factor 2. */
  VOLTIX_ADC_GAIN2 = 6UL,
  /** Gain factor 4. */
  VOLTIX_ADC_GAIN4 = 7UL,
} voltix_adc_gain_t;

typedef enum {
  /** Internal reference (0.6 V). */
  VOLTIX_ADC_REFERENCE_INTERNAL = 0UL,
  /** VDD/4 reference. */
  VOLTIX_ADC_REFERENCE_VDD4 = 1UL
} voltix_adc_reference_t;

typedef enum {
  /** 3us acquisition time. */
  VOLTIX_ADC_ACQTIME_3US = 0UL,
  /** 5us acquisition time. */
  VOLTIX_ADC_ACQTIME_5US = 1UL,
  /** 10us acquisition time. */
  VOLTIX_ADC_ACQTIME_10US = 2UL,
  /** 15us acquisition time. */
  VOLTIX_ADC_ACQTIME_15US = 3UL,
  /** 20us acquisition time. */
  VOLTIX_ADC_ACQTIME_20US = 4UL,
  /** 40us acquisition time. */
  VOLTIX_ADC_ACQTIME_40US = 5UL
} voltix_adc_acqtime_t;

typedef enum {
  /** No pullup on ADC input. */
  VOLTIX_ADC_RES_NOPULL = 0UL,
  /** Pulldown on ADC input. */
  VOLTIX_ADC_RES_PULLDOWN = 1UL,
  /** Pullup on ADC input. */
  VOLTIX_ADC_RES_PULLUP = 2UL,
  /** Pullup and pulldown (VDD/2) on ADC input. */
  VOLTIX_ADC_RES_VDD1_2 = 3UL,
} voltix_adc_res_t;

typedef struct {
  /** Gain of ADC pre-amplifier. */
  voltix_adc_gain_t gain;
  /** ADC reference. */
  voltix_adc_reference_t reference;
  /** Acquisition time. */
  voltix_adc_acqtime_t acq_time;
  /** ADC positive input. */
  voltix_adc_input_t input_pos;
  /** ADC negative input. */
  voltix_adc_input_t input_neg;
  /** Positive input resistor config. */
  voltix_adc_res_t res_pos;
  /** Negative input resistor config. */
  voltix_adc_res_t res_neg;
  /** Oversampling factor. */
  voltix_adc_oversample_t oversampling;
  /** Number of samples to be taken. */
  unsigned int n_samples;
  /**  Sample interval in ticks on a 32kHz clock. */
  unsigned int sample_interval_ticks32;
} voltix_adc_cfg_t;

/**
 * @brief Initializes ADC. Must be called once after reset before ADC can be used.
 *
 */
void voltix_adc_init(void);

/**
 * @brief Reads multiple samples from the ADC.
 *
 * Periodically samples the ADC with a specified sampling interval storing the samples in the provided buffer. Blocks
 * until all samples are taken or until the operation is aborted due to low energy.
 *
 * @param dst Buffer where samples are stored.
 * @param cfg ADC and sampling configuration.
 *
 * @retval VOLTIX_SUCCESS       Sampling completed.
 * @retval VOLTIX_ERR_RESET    Reset occured while sampling.
 * @retval VOLTIX_ERR_TEARDOWN Teardown occured while sampling.
 */
voltix_rc_t voltix_adc_sample(int16_t *dst, voltix_adc_cfg_t *cfg);

/**
 * @brief Reads a sample from the ADC.
 *
 * Reads one sample from the ADC with a preconfigured configuration. Blocks until sample is taken. Gain and reference
 * settings are chosen such that the full 12-bit input range equals the supply voltage.
 *
 * @param in Analog input.
 * @return int16_t ADC sample as 12-bit value w.r.t. the supply voltage.
 */
int16_t voltix_adc_read(voltix_adc_input_t in);

/**
 * @brief Converts a raw binary value sampled from the ADC to a voltage value.
 *
 * @param adc 12-bit ADC sample.
 * @param cfg ADC configuration that was used for taking the sample.
 * @return float Voltage value.
 */
float voltix_adc_adc2vadc(int16_t adc, voltix_adc_cfg_t *cfg);

/**
 * @brief Converts ADC input voltage to capacitor voltage based on amplifier gain.
 *
 * @param v_adc ADC input voltage.
 * @return float Capacitor voltage.
 */
static inline float voltix_adc_vadc2vcap(float v_adc) {
  /* A capacitor voltage of 4.8V produces 1.727V on the ADC input */
  return v_adc / 1.727f * 4.8f;
}

/**
 * @brief Translates digital pin to analog input channel.
 *
 * @param input Pointer where ADC input gets stored.
 * @param pin Pin number.
 *
 * @retval VOLTIX_SUCCESS         Successfully converted.
 * @retval VOLTIX_ERR_INVALIDARG Pin is not an ADC input.
 */
static inline voltix_rc_t voltix_adc_pin2input(voltix_adc_input_t *input, unsigned int pin) {
  switch (pin) {
    case PIN_D2:
      *input = VOLTIX_ADC_INPUT_A0;
      return VOLTIX_SUCCESS;
    case PIN_D3:
      *input = VOLTIX_ADC_INPUT_A1;
      return VOLTIX_SUCCESS;
    default:
      return VOLTIX_ERR_INVALIDARG;
  }
}

#ifdef __cplusplus
}
#endif

#endif /** @} __VOLTIX_ADC_H_ */
