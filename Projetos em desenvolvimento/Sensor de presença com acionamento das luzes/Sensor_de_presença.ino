int sensorPir = 7;
int ledPin = 6;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPir, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int moviment = digitalRead(sensorPir);

  if (moviment == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Sala com movimento!!");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Sala Vazia!!");
  }
  delay(500);
}
