#include <Wire.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>

// Configuração do display LCD
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// Configuração dos sensores
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int umidadePin = A0; // Pino analógico para o sensor de umidade
const int vacuometroPin = A1; // Pino analógico para o vacuômetro
const int chipSelect = 4; // Pino CS para o módulo SD

File dataFile;

void setup() {
  lcd.begin(16, 2); // Inicializa o display LCD
  sensors.begin(); // Inicializa o sensor de temperatura
  
  // Inicializa o módulo SD
  if (!SD.begin(chipSelect)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro SD");
    while (1);
  }

  dataFile = SD.open("dados.txt", FILE_WRITE);
  if (!dataFile) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro abrir arquivo");
    while (1);
  }
  
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

  lcd.setCursor(8, 1);
  lcd.print("Vacu: ");
  lcd.print(vacuometroValor);
  lcd.print(" V");

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
