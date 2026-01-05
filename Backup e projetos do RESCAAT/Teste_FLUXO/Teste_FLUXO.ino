#include <LiquidCrystal.h>

// Define os pinos do LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int sensorPin = 18;  // Pino digital conectado ao fio amarelo do sensor de fluxo
volatile int pulseCount = 0;
unsigned long oldTime = 0;

float calibrationFactor = 4.5;  // Fator de calibração para o sensor YF-S201
float flowRate = 0.0;
float flowMilliLitres = 0;
float totalLitres = 0.0;

void setup() {
  // Configuração do pino do sensor de fluxo
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);

  // Inicia a comunicação serial e o display LCD
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Exibe mensagem inicial no LCD
  lcd.print("Fluxo de Agua");
  delay(2000);
  lcd.clear();
  oldTime = millis();
}

void loop() {
  if ((millis() - oldTime) > 250) {  // Calcula o fluxo a cada segundo
    // Desabilita a interrupção enquanto calcula o fluxo
    detachInterrupt(digitalPinToInterrupt(sensorPin));

    // Calcula a taxa de fluxo em L/min
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;

    // Totaliza o fluxo em mililitros e litros
    flowMilliLitres = (flowRate / 60) * 1000;
    totalLitres += flowMilliLitres / 1000.0;

    // Exibe os resultados no monitor serial
    Serial.print("Fluxo: ");
    Serial.print(flowRate);
    Serial.print(" L/min");
    Serial.print("\tTotal: ");
    Serial.print(totalLitres);
    Serial.println(" L");

    // Exibe os resultados no display LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fluxo: ");
    lcd.print(flowRate);
    lcd.print(" L/min");
    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(totalLitres);
    lcd.print(" L");

    // Reseta a contagem de pulsos e reinicia o temporizador
    pulseCount = 0;
    oldTime = millis();

    // Reabilita a interrupção
    attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  }
}

// Função de interrupção para contar os pulsos do sensor
void pulseCounter() {
  pulseCount++;
}
