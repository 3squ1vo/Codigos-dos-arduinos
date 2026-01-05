#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>

#define ONE_WIRE_BUS 9
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int pinoCS = 53; // Pino CS para o módulo SD
int numeroLeitura = 0;
float leituraTEMP = 0.0;

void setup() {
  Serial.begin(9600);
  sensors.begin();

  if (!SD.begin(pinoCS)) {
    Serial.println("Falha ao inicializar o cartão SD!");
    while (1); // Para o programa se o SD não inicializar
  }

  Serial.println("Cartão SD inicializado com sucesso!");
}

void loop() {
  numeroLeitura++;
  sensors.requestTemperatures(); 
  leituraTEMP = sensors.getTempCByIndex(0); 

  Serial.print("Leitura ");
  Serial.print(numeroLeitura);
  Serial.print(" - Temp: ");
  Serial.print(leituraTEMP);
  Serial.println(" °C");

  File data = SD.open("Arquivo_SensorTEMP.txt", FILE_WRITE);
  if (data) {
    data.print("Leitura ");
    data.print(numeroLeitura);
    data.print(": ");
    data.print(leituraTEMP);
    data.println(" °C");
    data.close();
  }

  delay(5000); 
}
