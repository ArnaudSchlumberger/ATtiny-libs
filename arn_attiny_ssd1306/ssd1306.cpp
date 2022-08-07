#include "ssd1306.h"
#include <Arduino.h>
#include <avr/pgmspace.h>

#include "chars.h"

SSD1306::SSD1306(){
    i2c _screenI2C(100,100);
    _row_index = 0;
    _line_index= 0;
}
SSD1306::SSD1306(i2c &screenI2C, const uint8_t i2c_address){
    _row_index = 0;
    _line_index= 0;
    _screenI2C = screenI2C;
    _i2c_address = i2c_address;
}

SSD1306::~SSD1306()
{
}

void SSD1306::setMuxRatio(const uint8_t value){
    _screenI2C.beginTransaction(_i2c_address,I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(0xA8);
    _screenI2C.sendByte(CONTINUATION_BYTE);
    _screenI2C.sendByte(value);
    _screenI2C.endTransaction();
}

void SSD1306::setDisplayOffset(const uint8_t value){
    _screenI2C.beginTransaction(_i2c_address, I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(0xD3);
    _screenI2C.sendByte(CONTINUATION_BYTE);
    _screenI2C.sendByte(value);
    _screenI2C.endTransaction();
}
void SSD1306::setDisplayStartLine(const uint8_t value){
    _screenI2C.beginTransaction(_i2c_address, I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(0x40);
    _screenI2C.endTransaction();
}
void SSD1306::setSegmentRemap(const uint8_t value){
    _screenI2C.beginTransaction(_i2c_address, I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(value);
    _screenI2C.endTransaction();
}
void SSD1306::setComOutScanDir(const uint8_t value){
    _screenI2C.beginTransaction(_i2c_address, I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(value);
    _screenI2C.endTransaction();
}
void SSD1306::setComPinsConfig(const uint8_t value){
    _screenI2C.beginTransaction(_i2c_address, I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(0xD3);
    _screenI2C.sendByte(CONTINUATION_BYTE);
    _screenI2C.sendByte(value);
    _screenI2C.endTransaction();
}
void SSD1306::setContrastControl(const uint8_t value){
    _screenI2C.beginTransaction(_i2c_address, I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(0x81);
    _screenI2C.sendByte(CONTINUATION_BYTE);
    _screenI2C.sendByte(value);
    _screenI2C.endTransaction();
}
void SSD1306::disableEntireDisplayOn(){
    _screenI2C.beginTransaction(_i2c_address,I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(0xA4);
    _screenI2C.endTransaction();
}
void SSD1306::enableEntireDisplayOn(){
    _screenI2C.beginTransaction(_i2c_address,I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(0xA5);
    _screenI2C.endTransaction();
}
void SSD1306::setNormalDisplay(){
    _screenI2C.beginTransaction(_i2c_address,I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(0xA6);
    _screenI2C.endTransaction();
}
void SSD1306::setOscFreq(const uint8_t value){
    _screenI2C.beginTransaction(_i2c_address,I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(0xD5);
    _screenI2C.sendByte(CONTINUATION_BYTE);
    _screenI2C.sendByte(value);
    _screenI2C.endTransaction();
}
void SSD1306::setChargePumpReg(const uint8_t value){
    _screenI2C.beginTransaction(_i2c_address,I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(0x8D);
    _screenI2C.sendByte(CONTINUATION_BYTE);
    _screenI2C.sendByte(value);
    _screenI2C.endTransaction();
}
void SSD1306::displayOn(){
    _screenI2C.beginTransaction(_i2c_address,I2C_WRITE);
    _screenI2C.sendByte(COMMAND_BYTE);
    _screenI2C.sendByte(0xAF);
    _screenI2C.endTransaction();
}

void SSD1306::setAddressingMode(const uint8_t value){
  _screenI2C.beginTransaction(_i2c_address,I2C_WRITE);
  _screenI2C.sendByte(COMMAND_BYTE);
  _screenI2C.sendByte(0x20);
  _screenI2C.sendByte(CONTINUATION_BYTE);
  _screenI2C.sendByte(value);
  _screenI2C.endTransaction();
}

void SSD1306::clearScreen(){
    _screenI2C.beginTransaction(0x3C,I2C_WRITE);
    for(int i = 0;i<1024;i++){
        _screenI2C.sendByte(GDDRAM_BYTE);
        _screenI2C.sendByte(0x00);
    }
    _screenI2C.endTransaction();
}

void SSD1306::printTestScreen(){
    _screenI2C.beginTransaction(0x3C,I2C_WRITE);
    for(int i = 0;i<1024;i++){
        _screenI2C.sendByte(GDDRAM_BYTE);
        _screenI2C.sendByte(i);
    }
    _screenI2C.endTransaction();
}


void SSD1306::openWrite(){
    _screenI2C.beginTransaction(_i2c_address, I2C_WRITE);
}

void SSD1306::openRead(){
    _screenI2C.beginTransaction(_i2c_address, I2C_READ);
}

void SSD1306::close(){
    _screenI2C.endTransaction();
}

void SSD1306::writeByteGDDRAM(const uint8_t byte){
    _screenI2C.sendByte(GDDRAM_BYTE);
    _screenI2C.sendByte(byte);
    incrementCursor();

}

void SSD1306::incrementCursor(){
    _row_index++;
    if(_row_index>LINELENGTH-1){
        _line_index++;
        _row_index=0;
    }
    if(_line_index>7){
        _line_index=0;
    } 
}

void SSD1306::setCursor(const uint8_t row, const uint8_t line){
    _screenI2C.beginTransaction(_i2c_address,I2C_WRITE);
    while(_line_index != line){
        writeByteGDDRAM(0x00);
    }
    while(_row_index != row){
        writeByteGDDRAM(0x00);
    }
    _screenI2C.endTransaction();
}

void SSD1306::writeChar(const uint8_t *character){
    for(int i = 1;i<pgm_read_byte(character)+1;i++){
        writeByteGDDRAM(pgm_read_byte(character+i));
    }
    writeByteGDDRAM(0x00);
}

void SSD1306::writeString(const uint8_t length, const char* string){
    for(int i = 0;i<length;i++){
        writeChar(letter2char(string[i]));
    }
}

uint8_t SSD1306::getCursorRow(){
    return _row_index;
}
uint8_t SSD1306::getCursorLine(){
    return _line_index;
}

void SSD1306::initDefaultProfile(){
    setMuxRatio(0x3F);            //==Set MUX ratio
    setDisplayOffset(0x00);      //==Set display offset
    setDisplayStartLine(0x00);  //==Set Display start line
    setSegmentRemap(0xA0);     //==Set Segment re-map
    setComOutScanDir(0XC0);   //==Set COM Output Scan Direction
    setContrastControl(0x3F);//==Set Constrast Control
    disableEntireDisplayOn();    //==Disable Entire Display ON
    setNormalDisplay();         //==Set Normal Display
    setOscFreq(0x80);          //==Set Oscillator Frequency
    setChargePumpReg(0x14);   //==Enable charge pump regulator
    displayOn();             //==Display ON
    setAddressingMode(0x00);//==Set addressing mode

    clearScreen();//Clear screen on startup
}

void SSD1306::printText(const char length, const char* string){
    openWrite();
    writeString(length,string);
    close();
}

void SSD1306::writeRawByte(const char byte){
    openWrite();
    for(int i = 0;i<8;i++){
        if( (byte&(1<<7-i))>>(7-i) ){
            writeChar(char_1);
        }
        else{
            writeChar(char_0);
        }
    }
    close();
}

void SSD1306::writeUnsignedLong(const unsigned long data){
    char data0 = (char)data;
    char data1 = (char)(data>>8);
    char data2 = (char)(data>>16);
    char data3 = (char)(data>>24);

    writeRawByte(data3);
    writeRawByte(data2);
    writeRawByte(data1);
    writeRawByte(data0);


}

void SSD1306::writeRaw20Bits(const unsigned long data){
    char data0 = (char)data;
    char data1 = (char)(data>>8);
    char data2 = (char)(data>>16);

    openWrite();
    for(int i = 0;i<4;i++){
        if( (data2&(1<<3-i))>>(3-i) ){
            writeChar(char_1);
        }
        else{
            writeChar(char_0);
        }
    }
    close();
    
    writeRawByte(data1);
    writeRawByte(data0);
}