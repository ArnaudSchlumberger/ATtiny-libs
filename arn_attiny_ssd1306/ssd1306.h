#ifndef SSD1306_H
#define SSD1306_H

#include <Arduino.h>
#include "i2c.h"

//0b[Co][D/C]0..0
#define COMMAND_BYTE 0b10000000
#define CONTINUATION_BYTE 0b00000000
#define GDDRAM_BYTE 0b11000000


#define LINELENGTH 128
class SSD1306
{
private:
    /* data */
    uint8_t _i2c_address;
    i2c _screenI2C;

    uint8_t _row_index;
    uint8_t _line_index;

public:
    SSD1306();
    SSD1306(i2c &screenI2C, const uint8_t i2c_address);
    ~SSD1306();

    void setMuxRatio(const uint8_t value);
    void setDisplayOffset(const uint8_t value);
    void setDisplayStartLine(const uint8_t value);
    void setSegmentRemap(const uint8_t value);
    void setComOutScanDir(const uint8_t value);
    void setComPinsConfig(const uint8_t value);
    void setContrastControl(const uint8_t value);
    void disableEntireDisplayOn();
    void enableEntireDisplayOn();
    void setNormalDisplay();
    void setOscFreq(const uint8_t value);
    void setChargePumpReg(const uint8_t value);
    void displayOn();
    void setAddressingMode(const uint8_t value);
    void clearScreen();
    void printTestScreen();

    //opens i2c master-write transaction between the screen and the microcontroller
    void openWrite();
    //opens i2c master-read transaction between the screen and the microcontroller
    void openRead();
    //closes i2c transmission between the screen and the microcontroller
    void close();
    //writes data to the GDDRAM by first sending the GDDRAM-specific byte and calling incrementCursor() function
    void writeByteGDDRAM(const uint8_t byte);
    //increments both row and line values depending on current position
    void incrementCursor();
    //writes 0x00 to GDDRAM until cursor is at the designated position. DOES NOT require to begin and end I2C transmission
    void setCursor(const uint8_t row, const uint8_t line);
    //writes data to GDDRAM from microcontroller flash memory (PROGMEM)
    void writeChar(const uint8_t *character);
    //writes characters array to GDDRAM
    void writeString(const uint8_t length, const char* string);
    //returns current row value
    uint8_t getCursorRow();
    //returns current line value
    uint8_t getCursorLine();

    void initDefaultProfile();

    //prints text without requiring the use of openWrite() and close() functions
    void printText(const char length, const char* string);

    //prints 8 bits without requiring the use of openWrite() and close() functions
    void writeRawByte(const char byte);
    //prints 32 bits without requiring the use of openWrite() and close() functions
    void writeUnsignedLong(const unsigned long data);
    //prints 20 bits without requiring the use of openWrite() and close() functions
    void writeRaw20Bits(const unsigned long data);
    //prints 16 bits without requiring the use of openWrite() and close() functions
    void writeRaw16Bits(const unsigned int data);
    //prints 24 bits without requiring the use of openWrite() and close() functions
    void writeRaw24Bits(const unsigned long data);

    //prints integer. Max value : 65535. Requires openWrite() and close();
    void writeInteger(const char length, const unsigned int value);
    //prints integer without requiring the use of openWrite() and close() functions
    void printInteger(const char length, const unsigned int value);


};

long int powerof(const int x, const int y);
#endif