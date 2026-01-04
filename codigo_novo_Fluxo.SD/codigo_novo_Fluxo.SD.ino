#include <LiquidCrystal.h>
#include <SD.h>

// Define os pinos do LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int sensorPin = 18;  // Pino digital conectado ao sensor de fluxo
const int chipSelect = 4;  // Pino CS para o módulo SD

volatile int pulseCount = 0;
unsigned long oldTime = 0;

float calibrationFactor = 4.5;  // Fator de calibração para o sensor
float flowRate = 0.0;
float flowMilliLitres = 0;
float totalLitres = 0.0;

File dataFile;

void setup() {
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);

  lcd.begin(16, 2);
  lcd.print("Fluxo de Agua");
  delay(2000);
  lcd.clear();

  if (!SD.begin(chipSelect)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro SD");
    while (1); // Trava o código em caso de erro
  }

  dataFile = SD.open("dados.txt", FILE_WRITE);
  if (!dataFile) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro abrir arquivo");
    while (1); // Trava o código em caso de erro
  }

  oldTime = millis();
}

void loop() {
  if ((millis() - oldTime) > 250) {  // Calcula o fluxo a cada 250 ms
    detachInterrupt(digitalPinToInterrupt(sensorPin));

    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    flowMilliLitres = (flowRate / 60) * 1000;
    totalLitres += flowMilliLitres / 1000.0;

    // Exibindo no LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fluxo: ");
    lcd.print(flowRate, 1);
    lcd.print(" L/min");
    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(totalLitres, 2);
    lcd.print(" L");

    // Salvando dados no arquivo SD
    if (dataFile) {
      dataFile.print("Fluxo: ");
      dataFile.print(flowRate, 1);
      dataFile.print(" L/min, ");
      dataFile.print("Total: ");
      dataFile.println(totalLitres, 2);
      dataFile.flush(); // Garante que os dados sejam escritos no cartão SD
    }

    pulseCount = 0;
    oldTime = millis();

    attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  }
}

void pulseCounter() {
  pulseCount++;
}
