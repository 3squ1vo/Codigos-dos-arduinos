#include <SD.h>

const int sensorPressaoPin = A0; // Pino de leitura do sensor de pressão
const int chipSelect = 4; // Pino CS para o módulo SD

File dataFile;

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial

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
  float sensorValue = analogRead(sensorPressaoPin); // Lê o valor do sensor (de 0 a 1023)
  float pressure = map(sensorValue, 0, 1023, 0, 500); // Mapeia o valor do sensor para uma faixa de pressão (em kPa)

  Serial.print("Pressao kPa: ");
  Serial.println(pressure);

  // Salvando dados no arquivo SD
  if (dataFile) {
    dataFile.print("Pressao kPa: ");
    dataFile.println(pressure);
    dataFile.flush(); // Garante que os dados sejam escritos no cartão SD
  }

  delay(3000);
}
