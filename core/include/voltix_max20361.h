#ifndef __VOLTIX_MAX20361_H_
#define __VOLTIX_MAX20361_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum max20361_reg_map {
  MAX20361_REG_DEV_ID,
  MAX20361_REG_STATUS,
  MAX20361_REG_INT,
  MAX20361_REG_INT_MSK,
  MAX20361_REG_SYS_REG_CFG,
  MAX20361_REG_WAKE_CFG,
  MAX20361_REG_MPPT_CFG,
  MAX20361_REG_MEAS_CFG,
  MAX20361_REG_DEV_CNTL,
  MAX20361_REG_VOC_MEAS,
  MAX20361_REG_HARV_CNT_H,
  MAX20361_REG_HARV_CNT_L,
  MAX20361_REG_SLEEP_THD,
};

enum max20361_wake_thr {
  MAX20361_THR_3V0,
  MAX20361_THR_3V1,
  MAX20361_THR_3V2,
  MAX20361_THR_3V3,
  MAX20361_THR_3V4,
  MAX20361_THR_3V5,
  MAX20361_THR_3V6,
  MAX20361_THR_3V7,
};

enum max20361_t_per {
  MAX20361_TMEAS_x64,
  MAX20361_TMEAS_x128,
  MAX20361_TMEAS_x256,
  MAX20361_TMEAS_DISABLED,
};

int voltix_max20361_init(void);
int voltix_max20361_id(uint8_t *dev_id);

#ifdef __cplusplus
}
#endif

#endif /* __VOLTIX_MAX20361_H_ */