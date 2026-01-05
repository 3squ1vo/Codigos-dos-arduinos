float offset = 0; // Ajuste inicial
const int sensorPin = A0;
float sensorValue = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Calibrando o sensor...");

  // Aguarda 5 segundos para estabilizar o sensor
  delay(5000);
  
  // Define o offset (valor do ADC sem pressão/vácuo)
  offset = analogRead(sensorPin);
  Serial.print("Offset definido como: ");
  Serial.println(offset);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  float adjustedValue = sensorValue - offset;

  Serial.print("ADC: ");
  Serial.print(sensorValue);
  Serial.print(" | Ajustado: ");
  Serial.print(adjustedValue);
  Serial.println();

  delay(1000);
}