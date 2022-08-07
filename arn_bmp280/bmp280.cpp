#include "bmp280.h"
#include "spi.h"



char bmp280::readID(){
    return *_spi.readRegister(REG_ID,1);
}
void bmp280::resetChip(){
    _spi.setCS();
    _spi.writeByte(REG_RESET);
    _spi.writeByte(RESET_VALUE);
    _spi.clrCS();
}
char bmp280::readStatus(){
    return *_spi.readRegister(REG_STATUS,1);
}

//--CTRL_MEAS Register associated functions
void bmp280::setMeasMode(const char mode){
    ctrl_meas_mem = (ctrl_meas_mem & 0b11111100) | mode;
}
void bmp280::set_osrs_temp(const char osrs){
    ctrl_meas_mem = (ctrl_meas_mem & 0b00011111) | (osrs<<5);
}
void bmp280::set_osrs_press(const char osrs){
    ctrl_meas_mem = (ctrl_meas_mem & 0b11100011) | (osrs<<2);

}
void bmp280::update_ctrl_meas(){
    _spi.setCS();
    _spi.writeByte(REG_CTRL_MEAS & 0b01111111); //bit 7 = 0 in write mode
    _spi.writeByte(ctrl_meas_mem);
    _spi.clrCS();
}
char bmp280::get_ctrl_meas(){
    return ctrl_meas_mem;
}
char bmp280::read_reg_ctrl_meas(){
    return *_spi.readRegister(REG_CTRL_MEAS | (1<<6),1);
}

//--CONFIG Register associated functions

void bmp280::setTSB(const char value){
    config_mem = (config_mem & 0b00011111) | (value << 5);
}
void bmp280::setFilter(const char value){
    config_mem = (config_mem & 0b11100011) | (value << 2);
}
void bmp280::setSPImode(const char value){
    config_mem = (config_mem & 0b11111110) | value;
}
void bmp280::update_config(){
    _spi.setCS();
    _spi.writeByte(REG_CONFIG & 0b01111111); //bit 7 = 0 in write mode
    _spi.writeByte(config_mem);
    _spi.clrCS();
}
char bmp280::get_config(){
    return config_mem;
}
char bmp280::read_reg_config(){
    return *_spi.readRegister(REG_CONFIG | (1<<7) ,1);
}


//--Measurement registers reading functions

void bmp280::burstReadMeasures(){
    char *list = new char[6];
    list = _spi.readRegister(REG_PRESS_MSB | (1<<7) , 6);
    
    adc_press = ((unsigned long)list[0]<<12) | ((unsigned long)list[1]<<4) | ((unsigned long)(list[2]>>4));
    adc_temp = ((unsigned long)list[3]<<12) | ((unsigned long)list[4]<<4) | ((unsigned long)(list[5]>>4));

    delete [] list; 
    

    //debug_list = _spi.readRegister(REG_PRESS_MSB | (1<<7) , 6);
}

//--Compensation values

void bmp280::readCompensationValues(){
    char *list = new char[24];
    list = _spi.readRegister(REG_CALIB_00,24);

    delete [] list;
}

unsigned long bmp280::get_adc_temp(){
    return adc_temp;
}

unsigned long bmp280::get_adc_press(){
    return adc_press;
}

bmp280::bmp280(spi &spi0){
    _spi = spi0;

    list_length = 6;
    debug_list = new char[list_length]; 
    

    ctrl_meas_mem = 0;
    config_mem = 0;
    status = 0;

}
bmp280::~bmp280(){
    delete [] debug_list;
}

unsigned long concat20bits(char msb, char lsb, char xlsb){
    // MSB[7-0]|LSB[7-0]|XLSB[7-4]
    return (((unsigned long)msb)<<12) | (((unsigned long)lsb)<<4) | (((unsigned long)xlsb)>>4);
}
