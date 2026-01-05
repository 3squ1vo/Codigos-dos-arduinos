#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>

#define ONE_WIRE_BUS 9
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int pinoCS = 53; // Pino CS para o módulo SD
int numeroLeitura = 0;
float leituraTEMP = 0.0;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  lcd.begin(16, 2);
  lcd.print("Inicializando...");

  if (!SD.begin(pinoCS)) {
    lcd.setCursor(0, 1);
    lcd.print("SD falhou!");
    while (1);
  }

  lcd.clear();
  lcd.print("SD OK!");
  delay(2000); 
  lcd.clear();
}

void loop() {
  numeroLeitura++;
  sensors.requestTemperatures(); 
  leituraTEMP = sensors.getTempCByIndex(0); 

  Serial.print("Temp: ");
  Serial.print(numeroLeitura);
  Serial.print(" - ");
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

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Leitura ");
  lcd.print(numeroLeitura);
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(leituraTEMP);
  lcd.print(" C");

  delay(5000); 
}
