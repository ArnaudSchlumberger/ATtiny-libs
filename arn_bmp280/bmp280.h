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

typedef long signed int BMP280_S32_t;
typedef long unsigned int BMP280_U32_t;
typedef long long signed int BMP280_S64_t;

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
    char* buffer; //24 bytes buffer for both compensation words and adc readings
    char buffer_length;
    signed long adc_temp; //last read Temperature ADC value
    signed long adc_press; //last read Pressure ADC value

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

    BMP280_S32_t T; //0.01°C step : 5984 reads 59.84°C
    BMP280_S32_t P; 

    BMP280_S32_t t_fine;
    
public:
    bmp280(spi &spi0);
    ~bmp280();

    //debug
    char *debug_list;
    int list_length;

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
    //--END

    //--Compensation values
    
    //reads all calibration registers and records the compensation values into the microcontroller accordingly
    void readCompensationValues();
    //--END

    //returns last stored Temperature ADC value
    unsigned long get_adc_temp();
    //returns last stored Pressure ADC value
    unsigned long get_adc_press();

    //calculates temperature using adc_temp and compensations values. Result is stored as T.
    void computeTemp();
    //calculates pressure using adc_temp and compensations values. Result is stored as P.
    char computePress();

    //returns stored temperature value
    BMP280_S32_t getTemp();
    //returns stored pressure value
    BMP280_S32_t getPress();
    
};

//returns a 32bits word built by concanating 3 bytes. Word structure : 0x000|MSB|LSB|XLSB[7-4]|
signed long int concat20bits(char msb, char lsb, char xlsb);
//returns a 24bits word built by concanating 3 bytes. Word structure : 0x00|MSB|LSB|XLSB|
signed long int concat24bits(char msb, char lsb, char xlsb);

#endif