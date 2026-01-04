const int sensorPin = A0; // Pino analógico onde o sensor está conectado
float sensorValue = 0;    // Valor lido do sensor
float voltage = 0;        // Voltagem calculada a partir do valor lido
float pressure = 0;       // Pressão calculada a partir da voltagem

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  sensorValue = analogRead(sensorPin); // Lê o valor do sensor (0-1023)
  voltage = (sensorValue / 1023.0) * 5.0; // Converte o valor lido para voltagem (0-5V)
  
  // Calibração específica para o sensor MPX5100DP
  pressure = ((voltage - 0.2) / 4.5) * 100.0; // Fórmula para converter voltagem em pressão
  
  Serial.print("Voltagem: ");
  Serial.print(voltage);
  Serial.print(" V, Pressão: ");
  Serial.print(pressure);
  Serial.println(" kPa");
  
  delay(1000); // Espera 1 segundo antes de ler novamente
}