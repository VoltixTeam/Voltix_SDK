#ifndef __GPINT_H_
#define __GPINT_H_

#include <stdint.h>
#include "voltix_gpio.h"

typedef void (*GPINT_CALLBACK)(unsigned int);

#ifdef __cplusplus
extern "C" {
#endif

int gpint_register(unsigned int pin, voltix_gpio_level_t level, voltix_gpio_in_pull_t pull, GPINT_CALLBACK cb);
int gpint_unregister(unsigned int pin);

#ifdef __cplusplus
}
#endif

#endif /* __GPINT_H_ */