#include <Arduino.h>

uint8_t count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Aprendendo no VScode");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(count);
  count++;
  if(count == 100){
    count = 0;
  }
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}

