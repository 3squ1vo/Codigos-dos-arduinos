#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int trigPin = 9;
int echoPin = 8;
long duration;
int distance;

Servo lockServo;
const int servoPin = 7;
const int servoOpen = 30;
const int servoClose = 90;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("      PAAI");
  lcd.setCursor(0, 1);
  lcd.print("   Dist: ");
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  lockServo.attach(servoPin);
  lockServo.write(servoClose); 
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  lcd.setCursor(9, 1);
  lcd.print(distance);
  lcd.print(" cm ");
  
  if (distance < 15 && distance > 0) {
    lockServo.write(servoOpen);
  } else {
    lockServo.write(servoClose);
  }
  delay(500);
}
