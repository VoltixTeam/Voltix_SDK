
#include "voltix.h"
#include "voltix_timing.h"
#include "voltix_adc.h"
#include "printf.h"

void lateinit(void) {
  voltix_adc_init();
}

int main(void) {
  for (;;) {
    int16_t val = voltix_adc_read(VOLTIX_ADC_INPUT_A0);
    printf("ADC value: %d\r\n", val);
    voltix_sleep_ms(1000);
  }
}
