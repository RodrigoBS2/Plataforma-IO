
#ifndef PARAMETROSGY80_H
    #define PARAMETROSGY80_H

    //#include <Arduino.h>

    //Pinos da comunicação i2c com os sensores bno055 e ina219
    #define Register_ID 0
    #define Register_2D 0x2D
    #define Register_X0 0x32
    #define Register_X1 0x33
    #define Register_Y0 0x34
    #define Register_Y1 0x35
    #define Register_Z0 0x36
    #define Register_Z1 0x37

    //Endreço do giroscópio
    //#define ADXAddress 0x53

    // Para ao stm32f103c8t6 (bluepill)
    #define   SENSORS_SDA PB9
    #define   SENSORS_SCL PB8
   

#endif
