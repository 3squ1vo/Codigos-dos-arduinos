#include <Wire.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Configuração do display LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Configuração dos sensores
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int umidadePin = A0; // Pino analógico para o sensor de umidade
const int vacuometroPin = A1; // Pino analógico para o vacuômetro

void setup() {
  lcd.begin(16, 2); // Inicializa o display LCD
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

  // Exibindo no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Umid: ");
  lcd.print(umidadeValor);
  lcd.print(" V");

  lcd.setCursor(0, 1);
  lcd.print("Vacu: ");
  lcd.print(vacuometroValor);
  lcd.print(" V");
  
  delay(2000); // Atualiza a cada 2 segundos
}
