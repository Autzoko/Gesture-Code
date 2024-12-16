#ifndef CODE_RECOGNITION_H
#define CODE_RECOGNITION_H

#include "gyroFunctions.h"
#include "spiFunctions.h"
#include "lcdFunctions.h"

static uint16_t stepCount = 0;
static bool codeStored = false;

void initialize();

bool detect2shakes();

void record();

void inputPwd(int code[4]);

#endif

