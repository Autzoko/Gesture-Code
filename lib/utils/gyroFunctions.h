#ifndef GYRO_FUNCTIONS_H
#define GYRO_FUNCTIONS_H

#include "settings.h"
#include <mbed.h>

void gyroRead(int16_t* data);

bool initGyro();

#endif