#include "i2c.h"
#include <Arduino.h>
#include "ssd1306.h"

i2c::i2c(){
    _tx_buffer_length = 10;
    _rx_buffer_length = 10;
    _tx_buffer = new uint8_t[10];
    _rx_buffer = new uint8_t[10];

    _tx_buffer_empty = 1;
    _rx_buffer_empty = 1;
}
i2c::i2c(const uint8_t tx_buffer_length, const uint8_t rx_buffer_length){
    _tx_buffer_length = tx_buffer_length;
    _rx_buffer_length = rx_buffer_length;
    _tx_buffer = new uint8_t[tx_buffer_length];
    _rx_buffer = new uint8_t[rx_buffer_length];

    _tx_buffer_empty = 1;
    _rx_buffer_empty = 1;
}

void i2c::setMBAUD(const uint8_t byte){
    TWI0.MBAUD = byte;
}
void i2c::setCTRLA(const uint8_t byte){
    TWI0.CTRLA = byte;
}
void i2c::setMCTRLA(const uint8_t byte){
    TWI0.MCTRLA = byte;
}
void i2c::setMCTRLB(const uint8_t byte){
    TWI0.MCTRLB = byte;
}
void i2c::setMSTATUS(const uint8_t byte){
    TWI0.MSTATUS = byte;
}
uint8_t i2c::getMSTATUS(){
    return TWI0.MSTATUS;
}

void i2c::clearTxBuffer(){
    _tx_buffer_front = 0;
    _tx_buffer_rear = 0;
    _tx_buffer_empty = 1;
}
void i2c::appendTxBuffer(const uint8_t byte){
    if(_tx_buffer_rear < _tx_buffer_length){
        if(_tx_buffer_empty){
            _tx_buffer[_tx_buffer_rear] = byte;
            _tx_buffer_empty = 0;
        }
        else{
            _tx_buffer_rear++;
            _tx_buffer[_tx_buffer_rear] = byte;
        }
        
    }
}
uint8_t i2c::getTxBufferSize(){
    return _tx_buffer_rear;
}


void i2c::clearRxBuffer(){
    _rx_buffer_length = 0;
}
uint8_t i2c::getRxBuffer(){
    if(_rx_buffer_index > 0){
    _rx_buffer_length--;
    return _rx_buffer[_rx_buffer_index+1];
    }
}
uint8_t i2c::getRxBufferSize(){
    return _rx_buffer_index;
}

void i2c::beginTransaction(const uint8_t slave_address, const uint8_t read_write){
    TWI0.MCTRLB = 0b00001010; //Flush = 1 & MCMD (Master command) Execute Acknowledge succeeded by a byte send operation 
    TWI0.MADDR = slave_address<<1|read_write;
}
uint8_t i2c::isReadyToSend(){
    return (TWI0.MSTATUS & 0b01000000) >> TWI0_MSTATUS_WIF_nb;
}
void i2c::sendByte(const uint8_t byte){
    while(!isReadyToSend());
    TWI0.MDATA = byte;
}
void i2c::sendBuffer(const uint8_t slave_address, const uint8_t read_write){
    beginTransaction(slave_address, read_write);
    while(_tx_buffer_front <= _tx_buffer_rear){
        sendByte(_tx_buffer[_tx_buffer_front]);
        _tx_buffer_front++;
    }
    endTransaction();
    clearTxBuffer();
}
void i2c::sendBuffer(const uint8_t slave_address, const uint8_t read_write, const uint8_t qty_of_bytes_to_send){
    beginTransaction(slave_address, read_write);
    for(int i = 0;i<qty_of_bytes_to_send;i++){
        if(_tx_buffer_front <= _tx_buffer_rear){
            sendByte(_tx_buffer[_tx_buffer_front]);
            _tx_buffer_front++;
        }
        
    }
    endTransaction();    
}
void i2c::endTransaction(){
    //MCMD (Master command) = 0x3 : "Execute Acknowledge Action succeeded by issuing a Stop Condition"
    while(!isReadyToSend());
    TWI0.MCTRLB = 0b00000011;
}

void i2c::init(){
    //TWI0.MBAUD = 0b00010100;
    TWI0.MBAUD = 0b0000000; //F_SCLK = F_CLK_PER / 10
    TWI0.CTRLA = 0b00000100; //SDASETUP= 4CYC ; SDAHOLD = 1
    TWI0.MCTRLA = 0b00000001; //Master ENABLE = 1
    TWI0.MCTRLB = 0b00001010; //FLUSH = 1, Mode envoi
    TWI0.MSTATUS = 0b00000001; //FORCER IDLE
}
