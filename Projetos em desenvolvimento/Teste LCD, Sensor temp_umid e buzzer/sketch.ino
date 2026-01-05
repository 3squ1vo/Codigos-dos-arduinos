#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 10

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

OneWire onseWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define TEMPERATURE_LIMIT = 

int umidSens = A0;
int limitSolo = 50;
int umidSolo = 0;
int rPin = 9;
int gPin = 8;
int bPin = 7;
int buzina = 13;

const int numReadings = 10;
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); //Caso o display LCD se for maior ou menor recomendo alterar para não dar erro!!
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(buzina, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(1000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("SmartCrop");
  lcd.setCursor(0, 1);
  lcd.print("Inovação no Agro");
  lcd.clear();

  for (int i = 0; i < numReadings; i++){
    readings[i] = 0;
  }
}

void loop() {
  for (int i = 0; i < 5; i++) {
    lcd.setCursor(0, 1);
    lcd.print()
    umidSolo = analogRead(umidSens);
    umidSolo = map(umidSolo, 1023, 0, 0,100);
  }

  if (umidSolo <= limitSolo) {
    lcd.setcursor(0, 1);
    lcd.print("    Regando    ");
    
  }
}
