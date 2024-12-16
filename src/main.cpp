#include "gyroFunctions.h"
#include "lcdFunctions.h"
#include "codeRecognition.h"

/* Set Gyro SPI, MISO=PF_9, MOSI=PF_8, SCK=PF_7 */
SPI spi(PF_9, PF_8, PF_7);
/* Set Chip-Select */
DigitalOut cs(PC_1);
/* Set LCD */
LCD_DISCO_F429ZI lcd;

extern int password[4];
extern int16_t data[3];

/* Set Timer */
extern "C" uint32_t HAL_GetTick();

static bool shake2start() {
    writeCenter(&lcd, 7, "Shake twice");
    return detect2shakes();
}


int main() {
    // init
    initialize();

    while (true) {

        rewriteAllCenter(&lcd, 6, "Shake to record");
        ThisThread::sleep_for(1s);

        shake2start();

        rewriteAllCenter(&lcd, 4, "Recording start");
        writeCenter(&lcd, 5, "in 3 seconds");
        ThisThread::sleep_for(1s);

        writeCenter(&lcd, 7, "3");
        ThisThread::sleep_for(1s);
        writeCenter(&lcd, 7, "2");
        ThisThread::sleep_for(1s);
        writeCenter(&lcd, 7, "1");
        ThisThread::sleep_for(1s);

        rewriteAllCenter(&lcd, 4, "Record your 4 step");
        writeCenter(&lcd, 5, "gesture password");

        char pwd_display_buffer[32];
        sprintf(pwd_display_buffer, "Password: _ _ _ _");
        writeCenter(&lcd, 7, pwd_display_buffer);

        record();

        ThisThread::sleep_for(2s);

        rewriteAllCenter(&lcd, 5, "Password recorded!");
        ThisThread::sleep_for(3s);

        while (true) {
            rewriteAllCenter(&lcd, 4, "Enter your");
            writeCenter(&lcd, 5, "gesture code");

            int input_pwd[4] = {0};
            inputPwd(input_pwd);

            
            bool match = true;
            for (unsigned int i = 0; i < 4; ++i) {
                if (password[i] != input_pwd[i]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                rewriteAllCenter(&lcd, 5, "PWD CORRECT!");
                break;
            } else {
                rewriteAllCenter(&lcd, 5, "INCORRECT!");
                writeCenter(&lcd, 6, "TRY AGAIN!");
                ThisThread::sleep_for(1s);
            }
        }

        while (true) {

        }
    }
}
