#include "spiFunctions.h"

extern SPI spi;
extern DigitalOut cs;

uint8_t spiReadRegister(uint8_t reg) {
    cs = 0;

    spi.write(READ_COMMAND | reg);
    uint8_t value = spi.write(0x00);

    cs = 1;

    return value;
}

void spiWriteRegister(uint8_t reg, uint8_t value) {
    cs = 0;

    spi.write(WRITE_COMMAND | reg);
    spi.write(value);

    cs = 1;
}