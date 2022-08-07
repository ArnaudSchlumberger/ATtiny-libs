#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

//Waits for specified amount of time (microseconds, max 65535). 
void waitTimerA_micros(const uint16_t microsecondes);
//Waits for specified amount of time (milliseconds, max 65535). 
void waitTimerA_milli(const uint16_t milliseconds);
//Disable TimerA peripheral and resets registers 
void disableTimerA();

#endif