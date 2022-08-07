#include "timer.h"
#include "clock_management.h"

void waitTimerA_micros(const uint16_t microseconds){
    //TimerA basic initialization
    //==Write TOP value to TCA0.PER reg
    TCA0.SINGLE.PER = 0xFFFF;
    TCA0.SINGLE.INTFLAGS = 0b00000001;
    //==Set prescaler value & Enable peripheral (CTRLA reg) [0x7 : prescaler = 1024]
    TCA0.SINGLE.CTRLA = (0x07<<1)|0b00000001;  
    //Enable Overflow / Underflow (OVF) Interrupt
    TCA0.SINGLE.INTCTRL = 0b00000001; 
    uint16_t interrupt_counter = 0;

    /*
    uint16_t interrupt_interval = 1024 / (F_CPU/1000000); //Equals 204 for 5MegHz clock frequency, microsecondes
    
    while(interrupt_counter < microseconds / interrupt_interval){
        //Check whether Overflow / underflow interrupt bit is raised
        if(TCA0.SINGLE.INTFLAGS & 0b00000001){
            TCA0.SINGLE.INTFLAGS = 0b00000001; // resets OVF interrupt flag
            interrupt_counter++;
        }
    }
    */

    //while( (TCA0.SINGLE.INTFLAGS & 0b00000001) != 0b00000001); //test debug

    while(interrupt_counter < 1){
        if((TCA0.SINGLE.INTFLAGS & 0b00000001) == 1){
            TCA0.SINGLE.INTFLAGS = 0b00000001; // resets OVF interrupt flag
            interrupt_counter++;
        }
    }

}


void waitTimerA_milli(const uint16_t milliseconds){
    uint16_t counter = 0;

}
 
void disableTimerA();