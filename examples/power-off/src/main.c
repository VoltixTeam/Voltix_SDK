
#include "nrf.h"

#include "voltix.h"
#include "voltix_gpio.h"
#include "voltix_timing.h"
#include "voltix_thresholds.h"
#include "voltix_am1805.h"
#include "printf.h"

/* This gets called after every reset */
void lateinit(void) {
  int rc;
  if ((rc = voltix_am1805_init()) != 0)
    printf("Error initializing RTC: %d\r\n", rc);
}

void bootstrap(void) {
  /* Reset RTC once after programming. */
  voltix_am1805_reset();
}

void am1805_poweroff(unsigned int seconds) {
  int rc;
  struct tm date_off;

  /* Read current date from the RTC. */
  voltix_am1805_get_datetime(&date_off);
  /* Add seconds. */
  date_off.tm_sec += seconds;
  /* Ensure that this is a correct date. */
  mktime(&date_off);
  printf("Setting alarm at %02d:%02d:%02d\r\n", date_off.tm_hour, date_off.tm_min, date_off.tm_sec);

  /* Clear interrupt from previous alarm. */
  voltix_am1805_clear_alarm();

  /* Set an alarm that will re-enable the power supply. */
  voltix_am1805_set_alarm(&date_off);
  printf("Power off\r\n");

  /* Disable the power supply with the p-MOSFET. */
  if ((rc = voltix_am1805_disable_power()) != 0)
    printf("Error disabling power: %d\r\n", rc);
}

int main(void) {
  struct tm now;

  voltix_am1805_get_datetime(&now);
  printf("Startup at %02d:%02d:%02d\r\n", now.tm_hour, now.tm_min, now.tm_sec);

  while (1) {
    voltix_wait_cap_charged();
    /* Checkpoint here -> will wake up here after power is restored*/
    voltix_checkpoint();
    voltix_am1805_get_datetime(&now);
    printf("It is now %02d:%02d:%02d\r\n", now.tm_hour, now.tm_min, now.tm_sec);
    am1805_poweroff(15);
    voltix_sleep_ms(1000);
  }
}
