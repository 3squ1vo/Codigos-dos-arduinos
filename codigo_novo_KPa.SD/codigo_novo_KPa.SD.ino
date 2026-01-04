#include <LiquidCrystal.h>
#include <SD.h>

// Inicializa o display LCD com os pinos RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int pin = A0; // Pino de leitura
const int chipSelect = 4; // Pino CS para o módulo SD

const float fator_atm = 0.0098692327;
const float fator_kgf_cm2 = 0.0101971621;

File dataFile;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Sensor Pressao");
  delay(1000);
  lcd.clear();

  Serial.begin(115200); // Inicializa a serial

  // Inicializa o módulo SD
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
}

void loop() {
  float medidas = analogRead(pin); // Lê o valor do ADC
  float pressao = calculaPressao(medidas); // Calcula a pressão

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("kPa: ");
  lcd.print(pressao, 2);

  lcd.setCursor(0, 1);
  if (millis() % 2000 < 1000) {
    lcd.print("atm: ");
    lcd.print(pressao * fator_atm, 4);
  } else {
    lcd.print("kgf/cm2: ");
    lcd.print(pressao * fator_kgf_cm2, 4);
  }

  Serial.print("ADC: ");
  Serial.println(medidas);
  Serial.print("Pressao kPa: ");
  Serial.println(pressao, 2);

  // Salvando dados no arquivo SD
  if (dataFile) {
    dataFile.print("ADC: ");
    dataFile.print(medidas);
    dataFile.print(", Pressao kPa: ");
    dataFile.println(pressao, 2);
    dataFile.flush(); // Garante que os dados sejam escritos no cartão SD
  }

  delay(1000);
}

float calculaPressao(float medida) {
  return ((corrigeMedida(medida) / 3.3) - 0.04) / 0.0012858;
}

float corrigeMedida(float x) {
  return 4.821e-02 + 1.181e-03 * x - 6.64e-07 * x * x + 5.236e-10 * x * x * x
         - 2.02e-13 * x * x * x * x + 3.81e-17 * x * x * x * x * x
         - 2.896e-21 * x * x * x * x * x * x;
}
