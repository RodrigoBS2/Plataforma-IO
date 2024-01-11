// Programa : Teste do giroscópio GY-80
// Adaptacoes : Arduino e Cia
#include "sensorgy80.h"

// Comnunicação Serial com a VScode e computador
//                      RX    TX
HardwareSerial Serial1(PA10, PA9);

GY_80 Snr = GY_80();
double *dados;

void setup()
{
  if(Snr.begin() != true){
    Serial1.println("Sensor GY-80 não inicializado");
  }  
  Serial1.begin(9600);                  
  delay(1000);
  
}
void loop()
{ 
  Snr.update_GY_data();
  Snr.get_GY_data(&dados);

  Serial1.print("X= "); Serial1.print(*dados); dados = dados + 1;
  Serial1.print("       ");
  Serial1.print("Y= "); Serial1.print(*dados); dados = dados + 1;
  Serial1.print("       ");
  Serial1.print("Z= ");Serial1.print(*dados); 
  Serial1.println("  ");
  delay(1000);
}