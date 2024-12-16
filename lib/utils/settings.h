#ifndef SETTINGS_H
#define SETTINGS_H

#include <mbed.h>

/* Support LCD Control */
#include "LCD_DISCO_F429ZI.h"

/* Other Supports*/
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

/* SPI Commands */
#define READ_COMMAND        0x80
#define WRITE_COMMAND       0x00
#define MULTI_BYTE_CMD      0x40

/* Gyro Register Address Mapping */
#define I3G4250D_WHO_AM_I       0x0F
#define I3G4250D_CTRL_REG1      0x20
#define I3G4250D_CTRL_REG2      0x21
#define I3G4250D_CTRL_REG3      0x22
#define I3G4250D_CTRL_REG4      0x23
#define I3G4250D_CTRL_REG5      0x24
#define I3G4250D_OUT_X_L        0x28
#define I3G4250D_OUT_X_H        0x29
#define I3G4250D_OUT_Y_L        0x2A
#define I3G4250D_OUT_Y_H        0x2B
#define I3G4250D_OUT_Z_L        0x2C
#define I3G4250D_OUT_Z_H        0x2D
#define I3G4250D_STATUS_REG     0x27

#define I3G4250D_DEFAULT_WHO_AM_I   0xD3

/* Functional Settings */
static const int PWD_MOVMNT_THRESH = 20000;
static const uint32_t ACTION_DURATION_MS = 500;
static const int SHAKE_THRESH = 15000;
static const int MAX_STEP = 65535;

#endif


