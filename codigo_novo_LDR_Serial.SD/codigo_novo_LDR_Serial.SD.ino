#include <SD.h>
#include <SPI.h>

int limiteDisparo = 600;  // Valor limite para ligar/desligar o LED
int led = 9;  // Pino do LED
int sensor = A0;  // Pino do fotoresistor (LDR)
const int chipSelect = 4;  // Pino CS do módulo SD

void setup() {
  pinMode(led, OUTPUT);  // Define o LED como saída
  pinMode(sensor, INPUT);  // Define o LDR como entrada
  Serial.begin(9600);  // Inicia a comunicação serial

  // Inicializa o módulo SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Falha ao inicializar o cartão SD!");
    while (1);
  }
  Serial.println("Cartão SD inicializado com sucesso!");
}

void loop() {
  int sensorValue = analogRead(sensor);  // Lê o valor do LDR
  digitalWrite(led, sensorValue < limiteDisparo ? HIGH : LOW);  // Controla o LED

  // Exibe a leitura no monitor serial
  Serial.print("Leitura atual do sensor: ");
  Serial.println(sensorValue);

  // Grava a leitura no cartão SD
  File dataFile = SD.open("leituraLDR.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Leitura do LDR: ");
    dataFile.println(sensorValue);
    dataFile.close();
  } else {
    Serial.println("Erro ao abrir o arquivo.");
  }

  delay(130);  // Aguarda um pequeno intervalo
}
