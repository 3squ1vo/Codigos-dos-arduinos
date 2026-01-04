#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>

#define ONE_WIRE_BUS 7
#define RELAY_PIN 8
const int chipSelect = 4; // Pino CS para o módulo SD

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

File dataFile;

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  sensors.begin();  // Inicializa os sensores
  pinMode(RELAY_PIN, OUTPUT);  // Configura o pino do relé como saída

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
  sensors.requestTemperatures();  // Solicita a leitura da temperatura
  float temperatureC = sensors.getTempCByIndex(0);  // Lê a temperatura em Celsius

  Serial.print("Temp C: ");
  Serial.print(temperatureC);
  Serial.print(", Relé: ");
  
  float threshold = 25.0;

  if (temperatureC >= threshold) {
    digitalWrite(RELAY_PIN, HIGH);  // Liga o relé se a temperatura for >= 25°C
    Serial.println("Ligado");
  } else {
    digitalWrite(RELAY_PIN, LOW);  // Desliga o relé se a temperatura for < 25°C
    Serial.println("Desligado");
  }

  // Salvando dados no arquivo SD
  if (dataFile) {
    dataFile.print("Temp C: ");
    dataFile.print(temperatureC);
    dataFile.print(", Relé: ");
    dataFile.println(temperatureC >= threshold ? "Ligado" : "Desligado");
    dataFile.flush(); // Garante que os dados sejam escritos no cartão SD
  }

  delay(1000);  // Espera 1 segundo antes da próxima leitura
}
