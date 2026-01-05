#include <LiquidCrystal.h>
#define vermelho 10
#define amarelo 11
#define verde 12
#define sensorPin A1

int leitura;

const int rs = 9, en = 8, d4 = 5,  d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
  lcd.print("Nivel d'agua");
  Serial.println("----- MONITORIAMENTO DO NÍVEL DE ÁGUA -----");
  digitalWrite(vermelho, LOW);
  digitalWrite(amarelo, LOW);
  digitalWrite(verde, LOW);
}

void loop()  {
  Serial.print("Leitura do Sensor de Nível: ");
  leitura = analogRead(sensorPin);
  Serial.println(leitura);
  if (leitura <= 500);
    lcd.setCursor(0, 1);
    lcd.print("Nivel: Baixo");
    Serial.println("Nível de água: Baixo");
    digitalWrite(vermelho, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, LOW);
  }
  else (leitura > 590 && leitura <= 625) {
    lcd.setCursor(0, 1);
    lcd.print("Nivel: Medio");
    Serial.println("Nível de água: Médio");
    digitalWrite(vermelho, HIGH);
    digitalWrite(amarelo, HIGH);
    digitalWrite(verde, LOW);
  }
  else (leitura > 650) {
    lcd.setCursor(0, 1);
    lcd.print("Nivel: Alto");
    Serial.println("Nível de água: Alto");
    digitalWrite(vermelho, HIGH);
    digitalWrite(amarelo, HIGH);
    digitalWrite(verde, HIGH);
  }
  delay(1000);
}