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
    
    adc_press = concat20bits(list[0], list[1], list[2]);
    adc_temp = concat20bits(list[3], list[4], list[5]);

    delete [] list; 
    

    //debug_list = _spi.readRegister(REG_PRESS_MSB | (1<<7) , 6);
}

//--Compensation values

void bmp280::readCompensationValues(){
    char *list = new char[24];
    list = _spi.readRegister(REG_CALIB_00 | (1<<7) ,24);

    dig_T1 = (((unsigned short int)list[1] & 0xff)<<8) | ((unsigned short int)list[0] & 0xff);
    dig_T2 = (((signed short int)list[3] & 0xff)<<8) | ((signed short int)list[2] & 0xff);
    dig_T3 = (((signed short int)list[5] & 0xff)<<8) | ((signed short int)list[4] & 0xff);

    dig_P1 = (unsigned short int)list[6]<<8 | list[7];
    dig_P2 = (signed short int)list[8]<<8 | list[9];
    dig_P3 = (signed short int)list[10]<<8 | list[11];
    dig_P4 = (signed short int)list[12]<<8 | list[13];
    dig_P5 = (signed short int)list[14]<<8 | list[15];
    dig_P6 = (signed short int)list[16]<<8 | list[17];
    dig_P7 = (signed short int)list[18]<<8 | list[19];
    dig_P8 = (signed short int)list[20]<<8 | list[21];
    dig_P9 = (signed short int)list[22]<<8 | list[23];

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

unsigned long int concat24bits(char msb, char lsb, char xlsb){
    // Data structure : MSB[7-0]|LSB[7-0]|XLSB[7-4]
    /* unsigned long int msb_temp = (((unsigned long int)msb)&0x000000ff) << 16;
    unsigned long int lsb_temp = (((unsigned long int)lsb)&0x000000ff) << 8;
    return msb_temp | lsb_temp | xlsb; */
    return ( ((unsigned long int)msb & 0xff)<<16) | (((unsigned long int)lsb & 0xff) << 8) | ((unsigned long int)xlsb & 0xff);
}

unsigned long int concat20bits(char msb, char lsb, char xlsb){
    return ( ((unsigned long int)msb & 0xff)<<12) | (((unsigned long int)lsb & 0xff) << 4) | ((unsigned long int)xlsb & 0xff) >> 4;
}

void bmp280::computeTemp(){
    BMP280_S32_t var1, var2, t_fine;

    var1 = (((adc_temp >> 3) - ((BMP280_S32_t)dig_T1<<1)) * ((BMP280_S32_t)dig_T2)) >> 11;
    var2 = (((((adc_temp >> 4) - ((BMP280_S32_t)dig_T1)) * ((adc_temp >> 4) - ((BMP280_S32_t)dig_T1))) >> 12) * ((BMP280_S32_t)dig_T3)) >> 14;
    t_fine = var1 + var2;

    T = (t_fine * 5 + 128) >> 8;

    
}

BMP280_S32_t bmp280::getTemp(){
    return T;
}