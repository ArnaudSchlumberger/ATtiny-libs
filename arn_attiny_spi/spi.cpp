#include "spi.h"
#include <avr/io.h>
#include <avr/pgmspace.h>


spi::spi(){

}
spi::spi(const char master, const char doubling, const char prescaler, const char spimode, const char byteOrder, const char buffEN, const char buffWR, const char mastermode){
    //configuraton of register CTRLA according to function args
    SPI0_CTRLA = (byteOrder<<SPI0_CTRLA_DORD_BP)|(master<<SPI0_CTRLA_MASTER_BP)|(doubling<<SPI0_CTRLA_CLK2X_BP)|(prescaler<<SPI0_CTRLA_PRESC_BP);
    //configuraton of register CTRLB according to function args
    SPI0_CTRLB = (buffEN<<SPI0_CTRLB_BUFEN_BP)|(buffWR<<SPI0_CTRLB_BUFWR_BP)|(mastermode<<SPI0_CTRLB_SSD_BP)|(spimode<<SPI0_CTRLB_MODE_BP);
    //enabling SPI peripheral
    _enabled = 1;
    SPI0_CTRLA |= (1<<SPI0_CTRLA_ENABLE_BP);
}

spi::~spi(){
}

//char spi::readReceiveByte();
//void spi::sendByte(const char byte);

void spi::setSending(){
    if((_transmission_status_byte & 0b00000010)>>1){
        //then transmission is in progress
        _transmission_status_byte = STATUS_BYTE_SENDING_TRANSMITTING;
    }
    else{
        //no transmision in progress
        _transmission_status_byte = STATUS_BYTE_SENDING_NOT_TRANSMITTING;
    }
}
void spi::setReceiving(){
    if((_transmission_status_byte & 0b00000010)>>1){
        //then transmission is in progress
        _transmission_status_byte = STATUS_BYTE_RECEIVING_TRANSMITTING;
    }
    else{
        //no transmision in progress
        _transmission_status_byte = STATUS_BYTE_RECEIVING_NOT_TRANSMITTING;
    }
}

void spi::setAsMaster(){
    SPI0_CTRLA |= (1<<SPI0_CTRLA_MASTER_BP);
}

void spi::setAsSlave(){
    SPI0_CTRLA &= ~(1<<SPI0_CTRLA_MASTER_BP);
}


void spi::enable(){
    SPI0_CTRLA |= (1<<SPI0_CTRLA_ENABLE_BP);
    _enabled = 1;
}
void spi::disable(){
    SPI0_CTRLA &= ~(1<<SPI0_CTRLA_ENABLE_BP);
    _enabled = 0;
}

void spi::setMultiMasterMode(const char mode){
    if(mode == SPIMULTIMASTER){
        SPI0_CTRLB &= ~(1<<SPI0_CTRLB_SSD_BP);
    }
    else{
        SPI0_CTRLB |= (1<<SPI0_CTRLB_SSD_BP);
    }
}  

void spi::setClockDoubling(const char value){
    if(value){
        SPI0_CTRLA |= (1<<SPI0_CTRLA_CLK2X_BP);
    }
    else{
        SPI0_CTRLA &= ~(1<<SPI0_CTRLA_CLK2X_BP);
    }
}

void spi::setPrescaler(const char value){
    SPI0_CTRLA &= ~(0b11<<SPI0_CTRLA_PRESC_BP); //reinit PRESC1 and PRESC0 bits
    SPI0_CTRLA |= (value<<SPI0_CTRLA_PRESC_BP);
}
       
void spi::setMode(const char value){
    SPI0_CTRLB &= ~(0b11<<SPI0_CTRLB_MODE_BP); //reinit PRESC1 and PRESC0 bits
    SPI0_CTRLB |= (value<<SPI0_CTRLB_MODE_BP);
}

void spi::setDataTransferOrder(const char value){
    if(value){
        SPI0_CTRLA |= (1<<SPI0_CTRLA_DORD_BP);
    }
    else{
        SPI0_CTRLA &= ~(1<<SPI0_CTRLA_DORD_BP);
    }
}

void spi::enableBufferMode(){
    SPI0_CTRLB |= (1<<SPI0_CTRLB_BUFEN_BP);
}

void spi::disableBufferMode(){
    SPI0_CTRLB &= ~(1<<SPI0_CTRLB_BUFEN_BP);
}

void spi::setDummyByte(const char value){
    if(value){
        SPI0_CTRLB |= (1<<SPI0_CTRLB_BUFWR_BP);
    }
    else{
        SPI0_CTRLB &= ~(1<<SPI0_CTRLB_BUFWR_BP);
    }
}

void spi::enableNonBufferInterrupt(){
    SPI0_INTCTRL |= (1<<SPI0_INTCTRL_IE_BP);
}

void spi::disableNonBufferInterrupt(){
    SPI0_INTCTRL &= ~(1<<SPI0_INTCTRL_IE_BP);
}

void spi::setCS(){
    PORTA.OUT &= ~(1<<SS_PIN);
}

void spi::clrCS(){
    PORTA.OUT |= (1<<SS_PIN);
}

void spi::writeByte(const char byte){
    SPI0.DATA = byte;
    while(SPI0.INTFLAGS != 0b10000000){
        
    }
}

void spi::sendByte(const char byte){
    setCS();
    writeByte(byte);
    clrCS();
}

char spi::receiveByte(){

}

char* spi::readRegister(const char reg, const char NumberOfBytes){
    if(NumberOfBytes == 0){
        return 0xFF;
    }
    char * array = new char[NumberOfBytes];

    setCS();
    SPI0.DATA = reg;
    while(SPI0.INTFLAGS != 0b10000000){

    }
    for(int i = 0;i<NumberOfBytes;i++){

        SPI0.DATA = 0x00;
        while(SPI0.INTFLAGS != 0b10000000){

        }
        array[i] = SPI0.DATA;

    }
    clrCS();
    return array;
}

void initSPIpins(){
    PORTA.DIR |= (1<<MOSI_PIN) | (1<<SCK_PIN) | (1<<SS_PIN); //OUTPUTS DIRECTION SETUP
    PORTA.DIR &= ~(1<<MISO_PIN);                             //INPUTS DIRECTION SETUP
    PORTA.OUT |= (1<<MOSI_PIN) | (1<<SCK_PIN) | (1<<SS_PIN); //OUTPUTS DIRECTION SETUP
}

