#include <Wire.h>
//#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal_I2C lcd(0x27, 16, 2);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//const int rPin = 22;
//const int gPin = 23;
//const int bPin = 24;

const int limitMax = 45;
const int limitMin = 55;
const int tempMax = 30;
const int tempMin = 19;

int buzina = 9;
int umidPin = A0;

const int numReadings = 10;
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buzina, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  lcd.init();
  lcd.backlight();
  //lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("   SmartCrop");
  lcd.setCursor(0, 1);
  lcd.print("Futuro no Campo");
  Serial.println("Fazendo Leitura...");
  delay(3000);
  lcd.clear();

  for (int i = 0; i< numReadings; i++) {
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

  if (average < tempMin) {
    lcd.setCursor(6, 0);
    lcd.print("Frio D+");
    //digitalWrite(rPin, 255);
    //digitalWrite(gPin, LOW);
    //digitalWrite(bPin, LOW);
    tone(buzina, 554);
  }
  else if (average > tempMax) {
    lcd.setCursor(6, 0);
    lcd.print("Quente D+");
    //digitalWrite(rPin, 255);
    //digitalWrite(gPin, LOW);
    //digitalWrite(bPin, LOW);
    tone(buzina, 554);
  }
  else if (average >= tempMin || average <= tempMax) {
    lcd.setCursor(6, 0);
    lcd.print("Esta ideal!!");
    //digitalWrite(rPin, LOW);
    //digitalWrite(gPin, 238);
    //digitalWrite(bPin, LOW);
  }

  for (int i = 0; i < 5; i++) {
    int umidValor = analogRead(umidPin);
    umidValor = map(umidValor, 1023, 0, 0, 100);

    lcd.setCursor(0, 1);
    lcd.print("Umid: ");

    if (umidValor < limitMin) {
      lcd.setCursor(6, 1);
      lcd.print("Molhado D+");
      //digitalWrite(rPin, 255);
      //digitalWrite(gPin, LOW);
      //digitalWrite(bPin, LOW);
      tone(buzina, 554);
    }
    else if (umidValor > limitMax) {
      lcd.setCursor(6, 1);
      lcd.print("Seco D+");
      //digitalWrite(rPin, 255);
      //digitalWrite(gPin, LOW);
      //digitalWrite(bPin, LOW);
      tone(buzina, 554);
    }
    else if (umidValor >= limitMin || umidValor <= limitMax) {
      lcd.setCursor(6, 1);
      lcd.print("Esta ideal!!");
      //digitalWrite(rPin, LOW);
      //digitalWrite(gPin, 238);
      //digitalWrite(bPin, LOW);
    }
    delay(1500);
  }
}