int ledPin = 12;
int sensorPin = 7;
int leitura = 0;
int relay = 8;
bool estadoSensor = false;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(relay, OUTPUT);
}
void loop() {
  leitura = digitalRead(sensorPin);
  if (leitura == HIGH) {
    digitalWrite(ledPin, HIGH);
    if (estadoSensor == false) {
      digitalWrite(relay, LOW);
      Serial.println("Movimento detectado");
      estadoSensor = true;
    }
    delay(5000);
  } else {
    digitalWrite(ledPin, LOW);
    if (estadoSensor == true) {
      digitalWrite(relay, HIGH);
      Serial.println("Sem movimento");
      estadoSensor = false;
    }
  }
}