#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT22

int ledPin = 5;
int ledPin1 = 4;
const int tempLimite = 31.0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Sensor DHT22");
  dht.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
}

void loop() {
  delay(2000);
  
  float umid = dht.readHumidity();
  float tempC = dht.readTemperature();

  if (isnan(umid) || isnan(tempC)) {
    Serial.println("ERROR 404, ERROR 404, ERROR 404, ERROR 404");
    return;
  }

  Serial.print("Umidade: ");
  Serial.print(umid);
  Serial.print("% Temp: ");
  Serial.print(tempC);
  Serial.print(" °C");

  if (tempC > tempLimite) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin1, LOW);
    Serial.println(" Diminua a temperatura, seu lazarento");
  }
  
  if (tempC == tempLimite) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin, LOW);
    Serial.println(" A temperatura tá muito boa, viu");
  }

  if (tempC < tempLimite) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin1, LOW);
    Serial.println(" Aumenta a temperatura, POURA!!");
  }

}
