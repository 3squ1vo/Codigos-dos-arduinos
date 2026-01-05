#define speakerPin 8
const int pirPin = 1;
const int relayPin = 13;
const int ledPin = 6;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int movimento = digitalRead(pirPin);

  if (movimento == HIGH) {
    Serial.println("Movimento Detectado!!");
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, LOW);
    tone(speakerPin, 1000);
    delay(500);
    noTone(speakerPin);
  } else {
    Serial.println("Sem Movimentos");
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, HIGH);
  }
  delay(500);
}
