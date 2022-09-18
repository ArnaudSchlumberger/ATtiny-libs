#ifndef SPI_H
#define SPI_H

//SPI PERIPHERAL ASSOCIATED PINS BIT POSITION
#define SS_PIN 4
#define MISO_PIN 2
#define MOSI_PIN 1
#define SCK_PIN 3

//CTRLA REGISTER BIT POSITIONS
#define SPI0_CTRLA_ENABLE_BP 0
#define SPI0_CTRLA_PRESC_BP 1
#define SPI0_CTRLA_CLK2X_BP 4
#define SPI0_CTRLA_MASTER_BP 5
#define SPI0_CTRLA_DORD_BP 6
//CTRLB REGISTER BIT POSITIONS
#define SPI0_CTRLB_MODE_BP 0   
#define SPI0_CTRLB_SSD_BP 2
#define SPI0_CTRLB_BUFWR_BP 6
#define SPI0_CTRLB_BUFEN_BP 7
//SPI0 INTCTRL REGISTER BIT POSITIONS
#define SPI0_INTCTRL_IE_BP 0
#define SPI0_INTCTRL_SSIE_BP 4
#define SPI0_INTCTRL_DREIE_BP 5
#define SPI0_INTCTRL_TXCIE_BP 6
#define SPI0_INTCTRL_RXCIE_BP 7
//SPI0 INTFLAGS REGISTER BIT POSITIONS
#define SPI0_INTFLAGS_BUFOVF_BP 0
#define SPI0_INTFLAGS_SSIF_BP 4
#define SPI0_INTFLAGS_DREIF_BP 5
#define SPI0_INTFLAGS_TXCIF_BP 6 //In buffer mode
#define SPI0_INTFLAGS_WRCOL_BP 6 //In non-buffer mode
#define SPI0_INTFLAGS_RXCIF_BP 7 //In buffer mode
#define SPI0_INTFLAGS_IF_BP 7 //In non-buffer mode

#define SPI_MSB_FIRST 0
#define SPI_LSB_FIRST 1

#define SPIMODE0 0b00
#define SPIMODE1 0b01
#define SPIMODE2 0b10
#define SPIMODE3 0b11

#define SPIMULTIMASTER 0
#define SPIMONOMASTER 1

#define DIV4 0b00
#define DIV16 0b01
#define DIV64 0b10
#define DIV128 0b11


#define STATUS_BYTE_SENDING_NOT_TRANSMITTING 0
#define STATUS_BYTE_SENDING_TRANSMITTING 2
#define STATUS_BYTE_RECEIVING_NOT_TRANSMITTING 1
#define STATUS_BYTE_RECEIVING_TRANSMITTING 3


//NOTE : ONLY SUPPORTS NON-BUFFER MODE
class spi
{
private:
    char _enabled; //0 : peripheral disabled, 1 : peripheral enabled
    char _transmission_status_byte; //0 : sending, no transmission, 1 : receiving, no transmission, 2 : sending, transmission in progress, 3 : receiving, transmission in progress
    char interruptRaised; // 1 if SPI interrupt was raised
public:
    spi();
    spi(const char master, const char doubling, const char prescaler, const char spimode, const char byteOrder, const char buffEN, const char buffWR, const char mastermode);
    ~spi();

    //char readByte();
    //sends byte, no CS handling
    void writeByte(const char byte);
    //sends one byte, handles CS pin
    void sendByte(const char byte);

    void setInterruptFlag();
    void clrInterruptFlag();

    void enableInterrupts();
    void disableInterrupts();
    //updates statuts byte to "sending", whether transmission is in progress or not
    void setSending();
    //updates statuts byte to "receiving", whether transmission is in progress or not
    void setReceiving();
    //sets SPI peripheral as Master
    void setAsMaster();
    //sets SPI peripheral as Slave
    void setAsSlave();

    //enables SPI0 peripheral
    void enable();
    //disables SPI0 peripheral
    void disable();
    //sets whether master mode is interrupted if SS pin is triggered. Allowed values : 0 or 1.
    void setMultiMasterMode(const char mode);    
    //enables or disables clock frequency doubling. Allowed values : 0 or 1.
    void setClockDoubling(const char value);     
    //sets prescaler (frequency divider value). Allowed values : DIV4 (0), DIV16 (1) ,DIV64 (2) or DIV128 (3).
    void setPrescaler(const char value); 
    //sets SPI data transfer mode. Allowed values : SPIMODE0, SPIMODE1, SPIMODE2, SPIMODE3        
    void setMode(const char value);
    //sets whether LSB or MSB is transfered first. Allowed value : SPI_MSB_FIRST or SPI_LSB_FIRST
    void setDataTransferOrder(const char value);

    //In buffer mode : 2 buffers in receive direction, 1 buffer in transmit direction + interrupt flags available
    void enableBufferMode();
    //In buffer mode : 2 buffers in receive direction, 1 buffer in transmit direction + interrupt flags available
    void disableBufferMode();
    //if value : 0 : first data transfered is a dummy sample. Allowed value : 0 or 1 
    void setDummyByte(const char value); 

    void enableNonBufferInterrupt();
    void disableNonBufferInterrupt();

    void setCS();
    void clrCS();

    char receiveByte();
    char *readRegister(const char reg, const char NumberOfBytes);
    void readRegister(const char reg, const char NumberOfBytes, char* outputBuffer);
};

void initSPIpins();

#endif