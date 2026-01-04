const int sensorPin = 18;  // Pino digital conectado ao fio amarelo do sensor de fluxo
volatile int pulseCount = 0;
unsigned long oldTime = 0;

float calibrationFactor = 4.5;  // Fator de calibração para o sensor YF-S201
float flowRate = 0.0;
float totalLitres = 0.0;

void setup() {
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);

  Serial.begin(9600);
  oldTime = millis();
}

void loop() {
  if ((millis() - oldTime) > 1000) {  // Calcula o fluxo a cada segundo
    detachInterrupt(digitalPinToInterrupt(sensorPin));

    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    totalLitres += (flowRate / 60);

    Serial.print("Fluxo: ");
    Serial.print(flowRate);
    Serial.print(" L/min");
    Serial.print("\tTotal: ");
    Serial.print(totalLitres);
    Serial.println(" L");

    pulseCount = 0;
    oldTime = millis();

    attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  }
}

void pulseCounter() {
  pulseCount++;
}
