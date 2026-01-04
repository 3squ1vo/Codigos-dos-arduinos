#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

// Pino ao qual o sensor DS18B20 está conectado
#define ONE_WIRE_BUS 7

// Pinos do LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// Configura o objeto OneWire para comunicar com o DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define RELAY_PIN 8
#define TEMPERATURE_LIMIT 35.00

// Inicializa o display LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int numReadings = 10;
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  lcd.begin(16, 2);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();

  // Inicializa o array de leituras
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  // Subtrai a última leitura
  total = total - readings[readIndex];
  // Solicita uma nova leitura
  sensors.requestTemperatures();
  readings[readIndex] = sensors.getTempCByIndex(0);
  // Adiciona a nova leitura ao total
  total = total + readings[readIndex];
  // Avança para a próxima posição no array
  readIndex = readIndex + 1;

  // Se o índice for igual ao número de leituras, volta ao início
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  // Calcula a média
  average = total / numReadings;

  // Exibe a média no LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(average);
  lcd.print(" C");

  sensors.requestTemperatures();

  float temperaureC = sensors.getTempCByIndex(0);

  if (temperaureC >= TEMPERATURE_LIMIT) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }
  // Aguarda 1 segundo antes de realizar nova leitura
  delay(50);

  if (temperaureC >= 32.00) {
    lcd.setCursor(0, 1);
    lcd.print("Temp. media");

  } else {
    lcd.setCursor(0, 1);
    lcd.print("Temp. Baixa");
  }
}
