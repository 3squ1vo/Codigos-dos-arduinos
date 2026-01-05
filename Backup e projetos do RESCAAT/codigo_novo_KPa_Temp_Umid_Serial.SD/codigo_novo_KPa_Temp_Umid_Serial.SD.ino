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

  // Salvando dados no arquivo SD
  if (dataFile) {
    dataFile.print("Temperatura: ");
    dataFile.print(temperatura);
    dataFile.print(" C, ");

    dataFile.print("Umidade: ");
    dataFile.print(umidadeValor);
    dataFile.print(", ");

    dataFile.print("Vacuômetro: ");
    dataFile.println(vacuometroValor);

    dataFile.flush(); // Garante que os dados sejam escritos no cartão SD
  }

  delay(2000); // Atualiza a cada 2 segundos
}
