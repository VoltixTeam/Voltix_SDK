
#include "voltix.h"
#include "voltix_stella.h"
#include "voltix_timing.h"
#include "printf.h"

static unsigned int counter = 0;

/* Buffer for receiving incoming packet. */
uint8_t rx_buf[VOLTIX_STELLA_MAX_DATA];

void lateinit(void) {
  voltix_stella_init();
}

int main() {
  voltix_rc_t rc;
  for (;;) {
    voltix_wait_cap_charged();
    rc = voltix_stella_transceive(rx_buf, sizeof(rx_buf), &counter, sizeof(counter));
    if (rc < 0)
      printf("Error %d\r\n", rc);
    else if (rc == 0)
      printf("Successful transmission. No data received.\r\n");
    else
      printf("Successful transmission. Received %d bytes from basestation.\r\n");

    counter++;
  }
}
