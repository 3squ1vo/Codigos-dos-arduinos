#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#define ONE_WIRE_BUS 8
const int umidadePin = A0;
const int limiarSeco = 50;
const int pinoValvula = 10;
const int tempoRega = 10;
int umidadeSolo = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int numReadings = 10;
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();

  lcd.print("    SmartCrop");
  delay(1000);
  lcd.clear();

  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }

}

void loop() {
  for(int i = 0; i < 5; i++);
  int umidadeValor = analogRead(umidadePin);
  umidadeValor = map(umidadeValor, 1023, 0, 0, 100);
  
  lcd.setCursor(0, 0);
  lcd.print(" Umidade: ");
  lcd.print(umidadeValor);
  lcd.print(" %");
  delay(2000);

  if (umidadeValor < limiarSeco) {
    lcd.setCursor(0, 0);
    lcd.print("    Regando     ");
    delay(tempoRega * 1000);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("   Encharcado   ");
    delay(3000);
  }
  
  total -= readings[readIndex];
  sensors.requestTemperatures();
  readings[readIndex] = sensores.getTempcByIndex(0);
  total += readings[readIndex];

  readIndex = (readIndex + 1) % numReadings;

  average = total / numReadings;

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(average, 2);
  lcd.print(" C");

  delay(4000);
}
