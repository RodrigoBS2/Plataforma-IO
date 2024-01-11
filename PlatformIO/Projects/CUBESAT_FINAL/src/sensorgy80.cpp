#include "sensorgy80.h"

GY_80::GY_80(){
}

bool GY_80::begin(){
  Wire.setSDA(SENSORS_SDA); 
  Wire.setSCL(SENSORS_SCL);   
  Wire.begin();                    
  delay(1000);
  // enable to measute g data
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_2D);
  Wire.write(8);                //measuring enable
  Wire.endTransmission();     // stop transmitting
  
  gy_buffer_pointer = &gy_buffer1;
  update_GY_data();
  return true;
}

double GY_80::UpdateAxes(int Register_axe_0, int Register_axe_1){
  int axe_0,axe_1,axe_out;
  double axe_g;
  Wire.beginTransmission(ADXAddress); // transmit to device
  Wire.write(Register_axe_0);
  Wire.write(Register_axe_1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2); 
  if(Wire.available()<=2)   
  {
    axe_0 = Wire.read();
    axe_1 = Wire.read(); 
    axe_1 = axe_1<<8;
    axe_out = axe_0 + axe_1;       
  }
  axe_g = axe_out/256.0;
  return axe_g;
}

void GY_80::update_GY_data(){
  double gy_buffer_pointer_aux;
  
  // Eixo Z
  gy_buffer_pointer_aux = UpdateAxes(Register_X0, Register_X1);

  if(gy_buffer_pointer == &gy_buffer1){
        gy_buffer2 = gy_buffer_pointer_aux;
        gy_buffer_pointer = &gy_buffer2;
    }
    else{
        gy_buffer1 = gy_buffer_pointer_aux;
        gy_buffer_pointer = &gy_buffer1;
    }
}

void GY_80::get_GY_data(double **data){
  *data = gy_buffer_pointer;
}
