#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int sensorPin = A0; // Pino conectado ao Vout do sensor
float sensorValue = 0;    // Valor lido do ADC
float pressure = 0;       // Pressão calculada em kPa

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  Serial.println("MPX5100DP - Medidor de Pressão");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
  lcd.print("    Rescaat");
}

void loop() {
  // Lê o valor do sensor (0-1023)
  sensorValue = analogRead(sensorPin);

  // Calcula a pressão diretamente usando o valor do ADC
  // Fórmula: Pressão (kPa) = ((ADC - Offset) / Sensibilidade) * Faixa
  // Offset = 41 (aproximadamente 0.2V em 5V), Faixa ADC = 1023
  // Sensibilidade = (1023 * 4.5V / 100kPa) / 5V = 9.2 (aproximado)
  pressure = ((sensorValue - 189) / 9.2); // Calcula a pressão em kPa

  // Exibe os valores no Monitor Serial
  Serial.print("ADC: ");
  Serial.print(sensorValue);
  Serial.print(" | Pressão (kPa): ");
  Serial.println(pressure, 2);
  
  lcd.setCursor(0, 1);
  lcd.print(pressure, 2);
  lcd.print(" kPa");
  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}
