#include "sensores_manager.h"

sensores_manager::sensores_manager(){
}

bool sensores_manager::begin(){
    Wire.setSDA(SENSORS_SDA); 
    Wire.setSCL(SENSORS_SCL); 
    Wire.begin();

    
    if(!bno.begin()){
        #ifdef DEBUGON    // Lá no arquivo debugging.h
          Serial1.println("Erro ao inicializar o BNO");
        #endif
        return false;
    }

    delay(1000);
    bno.setExtCrystalUse(true);

    bno_buffer_pointer = bno_buffer1;

    update_BNO055_data();
 
    #ifdef DEBUGON
      Serial1.println("Sensores inicializados com sucesso");
    #endif
    

    return true;

}

void sensores_manager::get_BNO055_data(float **data){
    *data = bno_buffer_pointer;
}

void sensores_manager::update_BNO055_data(){
    float bno_buffer_pointer_aux[10];

    vec = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    bno_buffer_pointer_aux[0] = (float)vec.x();
    bno_buffer_pointer_aux[1] = (float)vec.y();
    bno_buffer_pointer_aux[2] = (float)vec.z();

    vec = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    bno_buffer_pointer_aux[3] = (float)vec.x()*SENSORS_DPS_TO_RADS;
    bno_buffer_pointer_aux[4] = (float)vec.y()*SENSORS_DPS_TO_RADS;
    bno_buffer_pointer_aux[5] = (float)vec.z()*SENSORS_DPS_TO_RADS;

    vec = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    bno_buffer_pointer_aux[6] = (float)vec.x();
    bno_buffer_pointer_aux[7] = (float)vec.y();
    bno_buffer_pointer_aux[8] = (float)vec.z();

    bno_buffer_pointer_aux[9] = bno.getTemp();    
    
    if(bno_buffer_pointer == bno_buffer1){
        memcpy(bno_buffer2, bno_buffer_pointer_aux, sizeof(float)*10);
        bno_buffer_pointer = bno_buffer2;
    }
    else{
        memcpy(bno_buffer1, bno_buffer_pointer_aux, sizeof(float)*10);
        bno_buffer_pointer = bno_buffer1;
    }
}




