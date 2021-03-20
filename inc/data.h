#include <bme280.h>
#include <uart.h>

#ifndef DATA_H_
#define DATA_H_

typedef struct {
  float internal;
  float external;
  float reference;
  float control;
} Data;

void data_init();
Data read_data();

#endif /* DATA_H_ */