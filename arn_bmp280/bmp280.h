#ifndef BMP280_H
#define BMP280_H

#include "spi.h"

//Registers addresses
#define REG_TEMP_XLSB 0xFC
#define REG_TEMP_LSB 0xFB
#define REG_TEMP_MSB 0xFA
#define REG_PRESS_XLSB 0xF9
#define REG_PRESS_LSB 0xF8
#define REG_PRESS_MSB 0xF7
#define REG_CONFIG 0xF5
#define REG_CTRL_MEAS 0xF4
#define REG_STATUS 0xF3
#define REG_RESET 0xE0
#define REG_ID 0xD0
#define REG_CALIB_25 0xA1
#define REG_CALIB_00 0x88

//Measuring mode
#define SLEEP_MODE 0b00
#define FORCED_MODE 0b01
#define NORMAL_MODE 0b11

//Temperature and pressure oversampling values
#define OVERSAMPLING_SKIPPED 0b000
#define OVERSAMPLINGx1 0b001
#define OVERSAMPLINGx2 0b010
#define OVERSAMPLINGx4 0b011
#define OVERSAMPLINGx8 0b100
#define OVERSAMPLINGx16 0b111

//Constant values
#define RESET_VALUE 0xB6

typedef long long signed int BMP280_S32_t;

class bmp280
{
private:
    //Associated SPI peripheral
    spi _spi;
    //Registers memory bytes
    char ctrl_meas_mem;
    char config_mem;
    char status;

    //Measurements
    unsigned long adc_temp;
    unsigned long adc_press;

    

    BMP280_S32_t T;
    
    
public:
    bmp280(spi &spi0);
    ~bmp280();

    //debug
    char *debug_list;
    int list_length;

    //--Compensation words
    //Temperature
    unsigned short dig_T1;
    signed short dig_T2;
    signed short dig_T3;
    //Pressure
    unsigned short dig_P1;
    signed short dig_P2;
    signed short dig_P3;
    signed short dig_P4;
    signed short dig_P5;
    signed short dig_P6;
    signed short dig_P7;
    signed short dig_P8;
    signed short dig_P9;

    //reads and returns chip ID. Should return 0x58
    char readID(); //checked
    //writes 0xB6 to chip's reset register 
    void resetChip(); //checked
    //reads and returns chip's status : 0b1000 : measuring, 0b0001 : updating image registers
    char readStatus();

    //--CTRL_MEAS Register associated functions
    
    //sets measure mode (this acts on ctrl_meas_mem). Use update_ctrl_meas() to update the chip's register.
    void setMeasMode(const char mode); //checked
    //sets temperature oversampling value
    void set_osrs_temp(const char osrs); //checked
    //set pressure oversampling value
    void set_osrs_press(const char osrs); //checked
    //updates chip's ctrl_meas register with ctrl_meas_mem. 
    void update_ctrl_meas(); //checked
    //returns recorded ctrl_meas byte
    char get_ctrl_meas(); //checked
    //reads and returns ctrl_meas register value for debugging purposes
    char read_reg_ctrl_meas(); //checked
    //--END

    //--CONFIG Register associated functions
    
    //sets inactive duration in normal mode (t_standby)
    void setTSB(const char value); //checked
    //sets time constant of IIR filter
    void setFilter(const char value); //checked
    //enables/disables SPI 3-wire mode (value : 0 = disabled, value : 1 = enabled)
    void setSPImode(const char value);
    //updates chip's config register with ctrl_meas_mem. 
    void update_config(); //checked
    //returns recorded config byte
    char get_config(); //checked
    //reads and returns config register value for debugging purposes
    char read_reg_config(); //checked

    //--END

    //--Measurement registers reading functions
    
    //Burst read of pressure and temperature registers
    void burstReadMeasures();
    //Reads pressure registers -- DISCONTINUED
    //void readPress();
    //Reads temperature registers -- DISCONTINUED
    //void readTemperature();
    //--END

    //--Compensation values
    
    //reads all calibration registers and records the compensation values into the microcontroller accordingly
    void readCompensationValues();
    //--END

    unsigned long get_adc_temp();
    unsigned long get_adc_press();

    void computeTemp();
    BMP280_S32_t getTemp();
    
};

unsigned long int concat20bits(char msb, char lsb, char xlsb);
unsigned long int concat24bits(char msb, char lsb, char xlsb);

#endif