#include "clock_management.h"

void setClk32k()
{
    CCP = 0xD8;
    CLKCTRL_MCLKLOCK = 0b00000000;
    CCP = 0xD8;
    CLKCTRL_MCLKCTRLA= 0b00000001;
    CCP = 0xD8;
    CLKCTRL_MCLKCTRLB= 0b00000000;
}

void setClk20M()
{
    CCP = 0xD8;
    CLKCTRL_MCLKLOCK = 0b00000000;
    CCP = 0xD8;
    CLKCTRL_MCLKCTRLA= 0b00000000;
    CCP = 0xD8;
    CLKCTRL_MCLKCTRLB= 0b00000000;
}

void setClk5M(){
    setClk20M(); //Réglage fréquence d'horloge : 20MegHertz
    CCP = 0xD8; //Desactivation protection registres
    CLKCTRL_MCLKCTRLB = 0b00000011; //Division par 4 : F_CLK = 5MHz
}

void setClk2M(){
    CCP = 0xD8;
    CLKCTRL_MCLKLOCK = 0b00000000;
    CCP = 0xD8;
    CLKCTRL_MCLKCTRLA= 0b00000000; //selects 16/20MegHz internal oscillator
    CCP = 0xD8;
    CLKCTRL_MCLKCTRLB= 0b00010011; //disables prescaler
}

uint8_t ClkStable(){
    return (CLKCTRL_MCLKSTATUS & 0b00010000) >> 4;
}