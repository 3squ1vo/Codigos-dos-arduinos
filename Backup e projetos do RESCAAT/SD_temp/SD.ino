#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>

// Pino de dados do sensor DS18B20
#define ONE_WIRE_BUS 9

// Inicializa a comunicação com o sensor DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Configuração do LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Pino do cartão SD
#define CS_PIN 53 // Para o Arduino Mega 2560, geralmente é o pino 53

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
  lcd.print("    Rescaat");

  sensors.begin();

  Serial.print("Inicializando o cartão SD...");
  if (!SD.begin(CS_PIN)) {
    Serial.println("Falha, verifique se o cartão está presente.");
    lcd.print("SD falhou!");
    return;
  } else{
  Serial.println("Cartão inicializado.");
  lcd.print("SD ok.");
  }
}

void loop() {
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);

  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print(" C");
  lcd.setCursor(0, 0);
  lcd.print("    Rescaat");

  File dataFile = SD.open("LOG.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Temperatura: ");
    dataFile.println(temperatura);
    dataFile.close();
    Serial.println("O arquivo foi aberto com sucesso.");
  } else {
    Serial.println("Falha ao abrir o arquivo LOG.txt");
    lcd.setCursor(0, 1);
    lcd.print("Falha arquivo!");
  }

  delay(2000); // Aguarda 2 segundos antes da próxima leitura
}
