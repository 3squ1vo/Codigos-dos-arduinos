#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 4);
int ledPin = 5;
int buzzer = 6;
int trigPin = 7;
int echoPin = 8;
long duration;
int distance;
float totalDistance = 50.0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("cm | ");
  Serial.println(distance * 10);
  Serial.println("mm");

  if (distance < totalDistance) {
    digitalWrite(ledPin, HIGH);
    tone(buzzer, 523);
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzer);
  }
  delay(500);
}