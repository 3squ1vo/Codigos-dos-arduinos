#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define ONE_WIRE_BUS 7
#define RELAY_PIN 8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  sensors.begin();  // Inicializa os sensores
  pinMode(RELAY_PIN, OUTPUT);  // Configura o pino do relé como saída
  
  lcd.begin(16, 2);  // Inicializa o LCD
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  sensors.requestTemperatures();  // Solicita a leitura da temperatura
  float temperatureC = sensors.getTempCByIndex(0);  // Lê a temperatura em Celsius

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print(" C");

  float threshold = 25.0;

  if (temperatureC >= threshold) {
    digitalWrite(RELAY_PIN, HIGH);  // Liga o relé se a temperatura for >= 25°C
    lcd.setCursor(0, 1);
    lcd.print("Relé: Ligado  ");
  } else {
    digitalWrite(RELAY_PIN, LOW);  // Desliga o relé se a temperatura for < 25°C
    lcd.setCursor(0, 1);
    lcd.print("Relé: Desligado");
  }

  delay(1000);  // Espera 1 segundo antes da próxima leitura
}
