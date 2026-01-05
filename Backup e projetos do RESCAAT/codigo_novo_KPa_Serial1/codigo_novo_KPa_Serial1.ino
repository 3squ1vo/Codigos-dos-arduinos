const int sensorPressaoPin = A0;

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  float sensorValue = analogRead(sensorPressaoPin); // Lê o valor do sensor (de 0 a 1023)
  float pressure = map(sensorValue, 0, 1023, 0, 500); // Mapeia o valor do sensor para uma faixa de pressão (em kPa)

  Serial.print("Pressao: ");
  Serial.print(pressure);
  Serial.println(" kPa");
  
  delay(3000);
}
