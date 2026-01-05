#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#define ONE_WIRE_BUS 9

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int numReadings = 10;
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  sensors.begin();  // Inicializa o sensor de temperatura
  lcd.begin(16, 2);  // Inicializa o LCD
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
  
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }

  lcd.print("    Rescaat");
}

void loop() {
  total -= readings[readIndex];  // Subtrai a última leitura
  sensors.requestTemperatures();  // Solicita uma nova leitura de temperatura
  readings[readIndex] = sensors.getTempCByIndex(0);  // Armazena a nova leitura
  total += readings[readIndex];  // Adiciona a nova leitura ao total
  
  readIndex = (readIndex + 1) % numReadings;  // Avança para a próxima posição no array

  average = total / numReadings;  // Calcula a média das leituras

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(average, 2);
  lcd.print(" C");

  delay(4000);  // Aguarda 4 segundos antes da próxima leitura
}
