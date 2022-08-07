#ifndef I2C_H
#define I2C_H

#include <Arduino.h>

#define SCL_PORT PORTB
#define SCL_bit 0
#define SDA_PORT PORTB
#define SDA_bit 1

#define I2C_BAUD 500

#define I2C_READ 0b00000001
#define I2C_WRITE 0b00000000

#define TWI0_MSTATUS_WIF_nb 6

class i2c
{
private:

    //Tx and Rx buffer attributes
    //TX
    uint8_t *_tx_buffer;
    uint8_t _tx_buffer_rear; //index of the last element in the fifo queue
    uint8_t _tx_buffer_front;//index of the first element in the fifo queue
    uint8_t _tx_buffer_length;
    uint8_t _tx_buffer_empty;
    //RX
    uint8_t *_rx_buffer;
    uint8_t _rx_buffer_index;
    uint8_t _rx_buffer_length;
    uint8_t _rx_buffer_empty;

    //Registers config attributes
    uint8_t _mbaud;
    uint8_t _ctrla;
    uint8_t _mctrla;
    uint8_t mctrlb;
    uint8_t mstatus;

public:
    i2c();
    i2c(const uint8_t tx_buffer_length, const uint8_t rx_buffer_length);

    void setMBAUD(const uint8_t byte);
    void setCTRLA(const uint8_t byte);
    void setMCTRLA(const uint8_t byte);
    void setMCTRLB(const uint8_t byte);
    void setMSTATUS(const uint8_t byte);
    uint8_t getMSTATUS();

    void clearTxBuffer();
    void appendTxBuffer(const uint8_t byte);
    uint8_t getTxBufferSize();
    
    void clearRxBuffer();
    uint8_t getRxBuffer();
    uint8_t getRxBufferSize();

    void beginTransaction(const uint8_t slave_address, const uint8_t read_write);
    uint8_t isReadyToSend();
    void sendByte(const uint8_t byte);
    void sendBuffer(const uint8_t slave_address, const uint8_t read_write); //sends the whole buffer in one transaction
    void sendBuffer(const uint8_t slave_address, const uint8_t read_write, const uint8_t qty_of_bytes_to_send); //send the specified number of bytes contained in the buffer
    void endTransaction();
    void init();

};



#endif