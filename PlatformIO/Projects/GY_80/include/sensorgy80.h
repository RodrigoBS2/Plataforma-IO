#ifndef   SENSORGY80_H
    #define SENSORGY80_H 
    #include <Arduino.h>
    #include <Wire.h>
    #include"ParametrosGY80.h"   

    class GY_80{
        public:
        GY_80();
        bool begin();
        double UpdateAxes(int Register_axe_0, int Register_axe_1);
        void get_GY_data(double **data);
        void update_GY_data();
        
        private:
        // Endereco I2C do sensor : 83 em decimal ou 0x53
        int reading = 0;
        int val=0;
        int ADXAddress = 0x53;  // the default 7-bit slave address
        double gy_buffer1[3];
        double gy_buffer2[3];
        double *gy_buffer_pointer;
    };

#endif