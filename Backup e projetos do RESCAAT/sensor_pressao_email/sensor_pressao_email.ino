#include <OneWire.h>

const int sensorPressaoPin = A0;
const float supplyVoltage = 5.0;

void setup(){
  Serial.begin(9600);
  Serial.print("Sensor de pressão");
}


void loop() {
  float sensorVaule = analogRead(sensorPressaoPin);
  float pressure = map(sensorVaule, 0, 1023, 0, 500);
  Serial.print(pressure);
  Serial.println(" KPa ");
  delay(3000);
}
