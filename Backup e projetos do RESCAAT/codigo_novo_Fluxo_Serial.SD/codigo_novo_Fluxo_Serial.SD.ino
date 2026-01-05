#include <SD.h>

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

  Serial.begin(9600);

  if (!SD.begin(chipSelect)) {
    Serial.println("Erro SD");
    while (1); // Trava o código em caso de erro
  }

  dataFile = SD.open("dados.txt", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Erro abrir arquivo");
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

    // Enviando dados para o monitor serial
    Serial.print("Fluxo: ");
    Serial.print(flowRate, 1);
    Serial.print(" L/min\t");
    Serial.print("Total: ");
    Serial.println(totalLitres, 2);

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
