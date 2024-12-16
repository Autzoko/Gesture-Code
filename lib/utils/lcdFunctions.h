#ifndef LCD_FUNCTIONS_H
#define LCD_FUNCTIONS_H

#include "settings.h"
#include <mbed.h>

/* Clear and Write Data on LCD (Centered) */
void rewriteAllCenter(LCD_DISCO_F429ZI* lcd, int line, const char* data);

/* Write Data on LCD Without Clearing (Centered)*/
void writeCenter(LCD_DISCO_F429ZI* lcd, int line, const char* data);

/* Clear Screen */
void clearLCD(LCD_DISCO_F429ZI* lcd);

#endif