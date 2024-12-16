#include "lcdFunctions.h"


void rewriteAllCenter(LCD_DISCO_F429ZI* lcd, int line, const char* data) {
    lcd->Clear(LCD_COLOR_WHITE);
    lcd->SetBackColor(LCD_COLOR_WHITE);
    lcd->SetTextColor(LCD_COLOR_BLACK);
    lcd->DisplayStringAt(0, LINE(line), (uint8_t*)data, CENTER_MODE);
}

void writeCenter(LCD_DISCO_F429ZI* lcd, int line, const char* data) {
    lcd->ClearStringLine(line);
    lcd->DisplayStringAt(0, LINE(line), (uint8_t*)data, CENTER_MODE);
}

void clearLCD(LCD_DISCO_F429ZI* lcd) {
    lcd->Clear(LCD_COLOR_WHITE);
    lcd->SetBackColor(LCD_COLOR_WHITE);
    lcd->SetTextColor(LCD_COLOR_BLACK);
}