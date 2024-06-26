#include "voltix.h"
#include "voltix_timing.h"
#include "printf.h"
#include "voltix_uart.h"
#include "voltix_stella.h"
#include "voltix_adc.h"
#include "voltix_gpio.h"

#include "shtc3.h"
#include "vm1010.h"

/* Pin D10 enables/disables microphone on the Voltix Sensor Shield (low active) */
#define PIN_MICROPHONE_DISABLE PIN_D5

void earlyinit(void) {
  /* Call this early to put SHTC3 into low power mode */
  shtc3_init();
  /* Disable microphone to reduce current consumption. */
  voltix_gpio_cfg_output(PIN_MICROPHONE_DISABLE);
  voltix_gpio_set(PIN_MICROPHONE_DISABLE);
}

/* This gets called after every reset */
void lateinit(void) {
  voltix_stella_init();

  vm1010_cfg_t cfg = {.pin_vout = PIN_D2, .pin_vbias = PIN_D3, .pin_mode = PIN_D10, .pin_dout = PIN_D4};
  vm1010_init(&cfg);
}

void suspend(void) {
  /* Disable the microphone */
  voltix_gpio_set(PIN_MICROPHONE_DISABLE);
  vm1010_exit();
}

int16_t samples[120];

int main(void) {
  int rc;
  printf("Startup!\r\n");

  for (;;) {
    voltix_wait_cap_charged();

    /* Switch on microphone */
    voltix_gpio_clear(PIN_MICROPHONE_DISABLE);
    /* Wait for 2ms for V_BIAS to come up */
    voltix_sleep_ticks(70);

    /* Wait for wake-on-sound signal from microphone */
    if ((rc = vm1010_wait4sound()) != VOLTIX_SUCCESS) {
      printf("Error while waiting for sound: %d", rc);
      voltix_gpio_set(PIN_MICROPHONE_DISABLE);
      continue;
    }

    /* Wait until microphone can be sampled (see VM1010 datasheet)*/
    voltix_sleep_ticks(5);
    printf("Sampling..");
    rc = vm1010_sample(samples, 120, 4);
    /* Disable the microphone */
    voltix_gpio_set(PIN_MICROPHONE_DISABLE);
    if (rc != VOLTIX_SUCCESS) {
      printf("Error during sampling: %d", rc);
    }

    /* Re-charge before trying to send result */
    voltix_wait_cap_charged();
    printf("Sending..");
    rc = voltix_stella_send((uint8_t *)samples, sizeof(samples));
    printf("Sending done: %d\r\n", rc);
  }
}
