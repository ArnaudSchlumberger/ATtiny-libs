#ifndef CLOCK_MANAGEMENT_H
#define CLOCK_MANAGEMENT_H
#include <Arduino.h>

#define F_CPU 5000000

void setClk32k();
void setClk20M();
void setClk5M();
void setClk2M();

uint8_t ClkStable();

#endif