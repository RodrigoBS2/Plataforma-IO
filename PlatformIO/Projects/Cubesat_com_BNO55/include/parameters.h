
#ifndef PARAMETERS_H
    #define PARAMETERS_H

    //#include <Arduino.h>

    //Pinos da comunicação i2c com os sensores bno055 e ina219
    #define   SENSORS_SDA PB9
    #define   SENSORS_SCL PB8
    #define   SENSORS_ADC PA5
    
    #define   WAKEUPRASP_PIN PA4

    //------------------------------------------------------------------------------
    //Byte inicial de um pacote recebido
    #define INITIAL_BYTE            0xA5
    //Byte final de um pacote recebido
    #define FINAL_BYTE              0x5A

    //------------------------------------------------------------------------------
    //Tamanho dos pacotes recebidos
    #define RXPACKET_SIZE           9
    //Tamanho dos pacotes de telemetria enviados
    #define TXPACKET_SIZE           63
    //Tamanho dos pacotes de ACK enviados
    #define ACKPACKET_SIZE          8

    #define CRC_SIZE                4

    //------------------------------------------------------------------------------

    #define BAUDRATE                115200
    
    //------------------------------------------------------------------------------

    #define INTERRUPTCALLBACKPERIOD     100
    #define INTERRUPTCALLBACKFREQUENCY  1000/INTERRUPTCALLBACKPERIOD
    #define BNO055_update_data_time     10
    #define INA219_update_data_time     10
    #define DS18B20_update_data_time    10

    #define TELEMETRY_PERIOD            5000
    #define TELEMETRY_SAVING_PERIOD     5000

#endif
