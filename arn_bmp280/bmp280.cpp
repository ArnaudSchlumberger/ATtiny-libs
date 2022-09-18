#include "bmp280.h"
#include "spi.h"



char bmp280::readID(){
    _spi.readRegister(REG_ID,1, buffer);
    return buffer[0];
}
void bmp280::resetChip(){
    _spi.setCS();
    _spi.writeByte(REG_RESET);
    _spi.writeByte(RESET_VALUE);
    _spi.clrCS();
}
char bmp280::readStatus(){
    _spi.readRegister(REG_STATUS,1,buffer);
    return buffer[0];
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
    _spi.readRegister(REG_CTRL_MEAS | (1<<6), 1, buffer);
    return buffer[0];
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
    _spi.readRegister(REG_CONFIG | (1<<7), 1, buffer);
    return buffer[0];
}


//--Measurement registers reading functions

void bmp280::burstReadMeasures(){
    _spi.readRegister(REG_PRESS_MSB | (1<<7) , 6, buffer);
    
    adc_press = concat20bits(buffer[0], buffer[1], buffer[2]);
    adc_temp = concat20bits(buffer[3], buffer[4], buffer[5]);
}

//--Compensation values

void bmp280::readCompensationValues(){
    _spi.readRegister(REG_CALIB_00 | (1<<7), 24, buffer);

    dig_T1 = (((unsigned short int)buffer[1] & 0xff)<<8) | ((unsigned short int)buffer[0] & 0xff);
    dig_T2 = (((signed short int)buffer[3] & 0xff)<<8) | ((signed short int)buffer[2] & 0xff);
    dig_T3 = (((signed short int)buffer[5] & 0xff)<<8) | ((signed short int)buffer[4] & 0xff);

    dig_P1 = (((unsigned short int)buffer[7] & 0xff)<<8) | ((unsigned short int)buffer[6] & 0xff);
    dig_P2 = (((signed short int)buffer[9] & 0xff)<<8) | ((signed short int)buffer[8] & 0xff);
    dig_P3 = (((signed short int)buffer[11] & 0xff)<<8) | ((signed short int)buffer[10] & 0xff);
    dig_P4 = (((signed short int)buffer[13] & 0xff)<<8) | ((signed short int)buffer[12] & 0xff);
    dig_P5 = (((signed short int)buffer[15] & 0xff)<<8) | ((signed short int)buffer[14] & 0xff);
    dig_P6 = (((signed short int)buffer[17] & 0xff)<<8) | ((signed short int)buffer[16] & 0xff);
    dig_P7 = (((signed short int)buffer[19] & 0xff)<<8) | ((signed short int)buffer[18] & 0xff);
    dig_P8 = (((signed short int)buffer[21] & 0xff)<<8) | ((signed short int)buffer[20] & 0xff);
    dig_P9 = (((signed short int)buffer[23] & 0xff)<<8) | ((signed short int)buffer[22] & 0xff);

}

unsigned long bmp280::get_adc_temp(){
    return adc_temp;
}

unsigned long bmp280::get_adc_press(){
    return adc_press;
}

bmp280::bmp280(spi &spi0){
    _spi = spi0;

    buffer_length = 24;
    buffer = new char[buffer_length];    

    ctrl_meas_mem = 0;
    config_mem = 0;
    status = 0;

}
bmp280::~bmp280(){
    delete [] buffer;
}

signed long int concat24bits(char msb, char lsb, char xlsb){
    return ( ((unsigned long int)msb & 0xff)<<16) | (((unsigned long int)lsb & 0xff) << 8) | ((unsigned long int)xlsb & 0xff);
}

signed long int concat20bits(char msb, char lsb, char xlsb){
    return ( ((unsigned long int)msb & 0xff)<<12) | (((unsigned long int)lsb & 0xff) << 4) | ((unsigned long int)xlsb & 0xff) >> 4;
}

void bmp280::computeTemp(){
    BMP280_S32_t var1, var2;

    var1 = (((adc_temp >> 3) - ((BMP280_S32_t)dig_T1<<1)) * ((BMP280_S32_t)dig_T2)) >> 11;
    var2 = (((((adc_temp >> 4) - ((BMP280_S32_t)dig_T1)) * ((adc_temp >> 4) - ((BMP280_S32_t)dig_T1))) >> 12) * ((BMP280_S32_t)dig_T3)) >> 14;
    t_fine = var1 + var2;

    T = (t_fine * 5 + 128) >> 8;

}

char bmp280::computePress(){
    BMP280_S64_t var1, var2, p_temp;

    var1 = t_fine - 128000;
    var2 = var1 * var1 * (BMP280_S64_t)dig_P6;
    var2 = var2 + ((var1 * (BMP280_S64_t)dig_P5)<<17);
    var2 = var2 + ((BMP280_S64_t)dig_P4<<35);
    var1 = ((var1 * var1 * (BMP280_S64_t)dig_P3)>>8) + ((var1 * (BMP280_S64_t)dig_P2)<<12);
    var1 = (((((BMP280_S64_t)1)<<47)+var1))*((BMP280_S64_t)dig_P1)>>33;


    if(var1 == 0){
        return 0; //avoid exception caused by division by zero
    }

    p_temp = 1048576 - adc_press;
    p_temp = (((p_temp<<31)-var2)*3125)/var1;

    var1 = (((BMP280_S64_t)dig_P9) * (p_temp>>13) * (p_temp>>13)) >> 25;
    var2 = (((BMP280_S64_t)dig_P8) * p_temp) >> 19;
    p_temp = ((p_temp + var1 + var2) >> 8) + (((BMP280_S64_t)dig_P7)<<4);
    P = (BMP280_U32_t)p_temp;
    return 1; 

}

BMP280_S32_t bmp280::getTemp(){
    return T;
}

BMP280_S32_t bmp280::getPress(){
    return P;
}