#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 11, 12, 13, 14, 15); 

const byte rows = 4;
const byte columns = 4;

const int ledGreen = 2;
const int ledRed = 3;
const int ledBlue = 1;
const int relay = 32;
const int buzzer = 7;

const String password = "1234";
String wordDigitalUser = ""; // sla, eu fumei nesse nome, mas se refere a entrada do user

char keys[rows][columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinosRows[rows] = {22, 23, 24, 25};
byte pinosColumns[columns] = {26, 27, 28, 29};
Keypad teclado = Keypad(makeKeymap(keys), pinosRows, pinosColumns, rows, columns);

void setup() {
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(relay, OUTPUT);

  digitalWrite(relay, LOW);

  lcd.begin(16,2);
  lcd.print("Digite a senha: ");
}

void loop() {
  char key = teclado.getKey();

 if (key) {
  Serial.println(key);

    if (key == '*') {
      wordDigitalUser = "";
      lcd.clear();
      lcd.print("Digite a senha: ");
    } else if (key == '#') {
        if (wordDigitalUser.length() == 4) {
          checkPassword();
        } else {
            lcd.clear();
            lcd.print("Senha incompleta");

            for (int i = 0; i < 4; i++){
              digitalWrite(ledRed, HIGH);
              digitalWrite(ledGreen, HIGH);
              digitalWrite(relay, HIGH);
              delay(200);

              digitalWrite(ledGreen, LOW);
              digitalWrite(ledRed, LOW);
              digitalWrite(relay, LOW);
              delay(200);
            }

            delay(2000);
            lcd.clear();
            lcd.print("Digite a senha: ");
            wordDigitalUser = "";
          }
      } else {
          lcd.setCursor(0, 1);
          wordDigitalUser += key;
          lcd.setCursor(wordDigitalUser.length() - 1, 1);
          lcd.print("*");
        }
  }
}

void checkPassword () {
  if (wordDigitalUser == password) {
    lcd.clear();
    lcd.print("Acesso Liberado");
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(relay, HIGH);
    tone(buzzer, 523, 500);
    noTone(buzzer);
    delay(3000);
    digitalWrite(ledGreen, LOW);
    digitalWrite(relay, LOW);
  } else {
    lcd.clear();
    lcd.print("Senha incorreta");
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(relay, HIGH);
    tone(buzzer, 523);
    delay(3000);
    digitalWrite(ledRed, LOW);
    digitalWrite(relay, LOW);
  }
}