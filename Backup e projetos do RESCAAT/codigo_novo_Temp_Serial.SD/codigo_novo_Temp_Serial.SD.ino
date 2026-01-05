#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>

#define ONE_WIRE_BUS 9

const int chipSelect = 4; // Pino CS para o módulo SD

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int numReadings = 10;
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

File dataFile;

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  sensors.begin();  // Inicializa o sensor de temperatura

  // Inicializa o módulo SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Erro SD");
    while (1); // Trava o código em caso de erro
  }

  dataFile = SD.open("dados.txt", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Erro abrir arquivo");
    while (1); // Trava o código em caso de erro
  }
}

void loop() {
  total -= readings[readIndex];  // Subtrai a última leitura
  sensors.requestTemperatures();  // Solicita uma nova leitura de temperatura
  readings[readIndex] = sensors.getTempCByIndex(0);  // Armazena a nova leitura
  total += readings[readIndex];  // Adiciona a nova leitura ao total
  
  readIndex = (readIndex + 1) % numReadings;  // Avança para a próxima posição no array

  average = total / numReadings;  // Calcula a média das leituras

  Serial.print("Temp C: ");
  Serial.println(average, 2);

  // Salvando dados no arquivo SD
  if (dataFile) {
    dataFile.print("Temp C: ");
    dataFile.println(average, 2);
    dataFile.flush(); // Garante que os dados sejam escritos no cartão SD
  }

  delay(4000);  // Aguarda 4 segundos antes da próxima leitura
}
