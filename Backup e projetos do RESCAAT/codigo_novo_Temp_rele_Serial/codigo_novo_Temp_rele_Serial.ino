#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7
#define RELAY_PIN 8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  sensors.begin();  // Inicializa os sensores
  pinMode(RELAY_PIN, OUTPUT);  // Configura o pino do relé como saída
}

void loop() {
  sensors.requestTemperatures();  // Solicita a leitura da temperatura
  float temperatureC = sensors.getTempCByIndex(0);  // Lê a temperatura em Celsius

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  float threshold = 25.0;

  if (temperatureC >= threshold) {
    digitalWrite(RELAY_PIN, HIGH);  // Liga o relé se a temperatura for >= 25°C
    Serial.println("Relé: Ligado");
  } else {
    digitalWrite(RELAY_PIN, LOW);  // Desliga o relé se a temperatura for < 25°C
    Serial.println("Relé: Desligado");
  }

  delay(1000);  // Espera 1 segundo antes da próxima leitura
}
