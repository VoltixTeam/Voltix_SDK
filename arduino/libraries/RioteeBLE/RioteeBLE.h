#ifndef __VoltixBLE_H_
#define __VoltixBLE_H_

#include <cstddef>

class VoltixBLE {
 public:
  void begin(const char adv_name[], void *data, size_t data_len);
  void advertise();
};

extern VoltixBLE BLE;

#endif /* __VoltixBLE_H_ */