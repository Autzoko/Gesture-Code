#include "gyroFunctions.h"

#include "spiFunctions.h"

extern SPI spi;
extern DigitalOut cs;

void gyroRead(int16_t* data) {
    uint8_t raw_data[6];

    cs = 0;

    spi.write(READ_COMMAND | MULTI_BYTE_CMD | I3G4250D_OUT_X_L);

    for (unsigned int i = 0; i < 6; ++i) {
        raw_data[i] = spi.write(0x00);
    }

    cs = 1;

    // Get x
    data[0] = (int16_t)((raw_data[1] << 8) | raw_data[0]);
    // Get Y
    data[1] = (int16_t)((raw_data[3] << 8) | raw_data[2]);
    // Get Z
    data[2] = (int16_t)((raw_data[5] << 8) | raw_data[4]);

}

bool initGyro() {
    spi.format(8, 3);
    spi.frequency(100000);

    cs = 1;

    /* Set 100Hz, PD=1, X+Y+Z Enabled */
    spiWriteRegister(I3G4250D_CTRL_REG1, 0x4F);
    ThisThread::sleep_for(2ms);

    /* Check WHO_AM_I */
    uint8_t whoami = spiReadRegister(I3G4250D_WHO_AM_I);
    if (whoami != I3G4250D_DEFAULT_WHO_AM_I) {
        // Init failed
        return false;
    }

    spiWriteRegister(I3G4250D_CTRL_REG3, 0x00);
    ThisThread::sleep_for(2ms);

    spiWriteRegister(I3G4250D_CTRL_REG4, 0x80);
    ThisThread::sleep_for(2ms);

    spiWriteRegister(I3G4250D_CTRL_REG5, 0x00);
    ThisThread::sleep_for(2ms);

    return true;
}