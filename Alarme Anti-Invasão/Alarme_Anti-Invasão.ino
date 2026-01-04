#include <pitches.h>

int sensorPin = 8;
int buzina = 9;
int butao = 10;
int laststatusbutao = HIGH;
bool alarmsilencebutao = false;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(buzina, OUTPUT);
  pinMode(butao, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int moviment = digitalRead(sensorPin);
  int actualstatusbutao = digitalRead(butao);

  if (laststatusbutao == HIGH && actualstatusbutao == LOW) {
    Serial.println("Botão Apertado");
    
    alarmsilencebutao = !alarmsilencebutao;

  if (alarmsilencebutao) {
    Serial.println("Alarme SILENCIADO!!");
    noTone(buzina);
  } else {
    Serial.println("Alarme ACIONADO!!");
  }
  }
  laststatusbutao = actualstatusbutao;
  if (alarmsilencebutao) {
    Serial.println("Alarme silenciado, para ativar aperte o botão!!");
  } else {
    if (moviment == HIGH) {
      Serial.println("Alarme ACIONADO e INTRUSO detectado!!");
      tone(buzina, 523);
    } else {
      Serial.println("Alarme ACIONADO e SEM movimento!!");
    }
  }
  delay(500);
}