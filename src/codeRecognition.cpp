#include "codeRecognition.h"

extern SPI spi;
extern DigitalOut cs;
extern LCD_DISCO_F429ZI lcd;
extern "C" uint32_t HAL_GetTick();

int password[4] = {0, 0, 0, 0};
int16_t data[3] = {0};

void initialize() {
    rewriteAllCenter(&lcd, 6, "Initializing...");
    ThisThread::sleep_for(3s);

    stepCount = 0;
    codeStored = false;

    if (initGyro()) return;
    else {
        rewriteAllCenter(&lcd, 6, "Init Failed!");
        while(true) {}
    } 
}

bool detect2shakes() {
    int count = 0;

    while (true) {
        ThisThread::sleep_for(100ms);

        gyroRead(data);

        bool detected = (
            abs(data[0]) > SHAKE_THRESH ||
            abs(data[1]) > SHAKE_THRESH ||
            abs(data[2]) > SHAKE_THRESH
        );

        if (detected) {
            if (++count >= 2) return true;
        }
    }
}

int axis2code(int16_t x, int16_t y, int16_t z) {
    int absX = abs(x), absY = abs(y), absZ = abs(z);

    if (absX > absY && absX > absZ) {
        return x > 0 ? 1 : -1;
    } else if (absY > absX && absY > absZ) {
        return y > 0 ? 2 : -2;
    } else {
        return z > 0 ? 3 : -3;
    }
}

static int inputPassword() {
    while (true) {
        ThisThread::sleep_for(100ms);
        gyroRead(data);

        if (
            abs(data[0]) > PWD_MOVMNT_THRESH ||
            abs(data[1]) > PWD_MOVMNT_THRESH ||
            abs(data[2]) > PWD_MOVMNT_THRESH
        ) {
            uint32_t _start = HAL_GetTick();
            int32_t sumX = 0, sumY = 0, sumZ = 0;
            int count = 0;

            while (HAL_GetTick() - _start < ACTION_DURATION_MS) {
                gyroRead(data);
                sumX += data[0];
                sumY += data[1];
                sumZ += data[2];
                count++;
                ThisThread::sleep_for(10ms);
            }

            int16_t avgX = sumX / count;
            int16_t avgY = sumY / count;
            int16_t avgZ = sumZ / count;

            return axis2code(avgX, avgY, avgZ);
        }
    }
}

static void showPwdInput(int obtained) {
    char buffer[64];
    const char* placeHolder = "_";
    char pwd_str[32];
    char part[8];

    pwd_str[0] = '\0';

    for (unsigned int i = 0; i < 4; ++i) {
        if (i < obtained) {
            sprintf(part, "%d ", password[i]);
        } else {
            sprintf(part, "%s ", placeHolder);
        }
        strcat(pwd_str, part);
    }

    sprintf(buffer, "Password: %s", pwd_str);
    writeCenter(&lcd, 7, buffer);
}

void record() {
    for (unsigned int i = 0; i < 4; ++i) {
        password[i] = inputPassword();
        showPwdInput(i + 1);
    }
}

void inputPwd(int code[4]) {
    for (unsigned int i = 0; i < 4; ++i) {
        code[i] = inputPassword();
        
    } 
}