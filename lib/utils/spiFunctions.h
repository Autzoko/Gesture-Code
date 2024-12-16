#ifndef SPI_FUNCTIONS_H
#define SPI_FUNCTIONS_H

#include "settings.h"
#include <mbed.h>

/* SPI Read Register */
uint8_t spiReadRegister(uint8_t reg);

/* SPI Write Register */
void spiWriteRegister(uint8_t reg, uint8_t value);

#endif