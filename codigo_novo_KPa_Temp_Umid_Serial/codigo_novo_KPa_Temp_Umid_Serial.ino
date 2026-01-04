#include <OneWire.h>
#include <DallasTemperature.h>

// Configuração dos sensores
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int umidadePin = A0; // Pino analógico para o sensor de umidade
const int vacuometroPin = A1; // Pino analógico para o vacuômetro

void setup() {
  Serial.begin(9600); // Inicializa o monitor serial
  sensors.begin(); // Inicializa o sensor de temperatura
  pinMode(2, OUTPUT); // Pino de saída para controle adicional
}

void loop() {
  // Leitura do sensor de temperatura
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);
  
  // Leitura dos sensores analógicos
  int umidadeValor = analogRead(umidadePin);
  int vacuometroValor = analogRead(vacuometroPin);

  // Enviando dados para o monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");

  Serial.print("Umidade: ");
  Serial.println(umidadeValor);

  Serial.print("Vacuômetro: ");
  Serial.println(vacuometroValor);

  delay(2000); // Atualiza a cada 2 segundos
}
