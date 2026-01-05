#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5
LiquidCrystal_I2C lcd (0x27, 16, 2);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int tempLimit = 35;
int limiarSeco = 25.5;
int umidPin = A0;
int buzina = 6;

const int numReadings = 10;
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buzina, OUTPUT);
  
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("   SmartCrop");
  lcd.setCursor(0, 1);
  lcd.print("Futuro no Campo");
  delay(3000);
  lcd.clear();

  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  total = total - readings[readIndex];

  sensors.requestTemperatures();
  readings[readIndex] = sensors.getTempCByIndex(0);

  total = total + readings[readIndex];

  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  average = total / numReadings;

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");

  if (average > tempLimit) {
    lcd.setCursor(6, 0);
    lcd.print("Frio D+");
    delay(2000);
    tone(buzina, 523, 110);
    delay(110);
    tone(buzina, 659, 110);
    delay(110);
    tone(buzina, 784, 110);
    delay(110);
  }
  else {
    lcd.setCursor(6, 0);
    lcd.print("Quente D+");
  }

  for(int i = 0; i < 5; i++) {
    int umidValor = analogRead(umidPin);
    umidValor = map(umidValor, 1023, 0, 0, 100);

    lcd.setCursor(0, 1);
    lcd.print("Umid: ");

    if (umidValor < limiarSeco) {
      lcd.setCursor(6, 1);
      lcd.print("Molhado D+");
      delay(2000);
    } 
    else {
      lcd.setCursor(6, 1);
      lcd.print("Seco D+");
      delay(2000);
    }  
  }
}