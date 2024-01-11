#ifndef SENSORES_MANAGER_H
    #define SENSORES_MANAGER_H

    #include <Wire.h>
    #include <Adafruit_Sensor.h>
    #include <Adafruit_BNO055.h>
    #include <utility/imumaths.h>

    #include "parameters.h"
    #include "debugging.h"

    class sensores_manager{
        public:
        sensores_manager();
        bool begin();
        
        void get_BNO055_data(float **data);
        void update_BNO055_data();
        
        private:
        Adafruit_BNO055 bno = Adafruit_BNO055(55);
        imu::Vector<3> vec;
        float bno_buffer1[10];
        float bno_buffer2[10];
        float *bno_buffer_pointer;
    };

#endif
