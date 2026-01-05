#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

Servo calcServo;

int pos = 0;

const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte Linhas = 4;
const byte Colunas = 3;

char teclas[Linhas][Colunas] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'-', '0', '='}
};

byte pinosLinhas[Linhas] = {14, 15, 16, 17};
byte pinosColunas[Colunas] = {18, 19, 20};

Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, Linhas, Colunas);

long a, b, x, y, trm1, trm2, resultado;
String respUser;
int operacao;
int nivelDifi;
char simbOp;

int buzina = 7;
int rPin = 8;
int gPin = 9;
int bPin = 10;

void setup() {
  Serial.begin(9600);
  
  pinMode(buzina, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  calcServo.attach(6);
  calcServo.write(0);
  delay(500);
  calcServo.detach();

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("  Cofreladora");
  delay(2000);
  lcd.clear();

  randomSeed(analogRead(0));
}

void loop() {

  // --- Parte da dificuldade ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1-Fac 2-Med");
  lcd.setCursor(0, 1);
  lcd.print("3-Dif Escolha:");

  // Parte da escolha do nível de dificuldade (O número para aperta no teclado)!!
  char key = 0;
  while (key != '1' && key != '2' && key != '3') {
    key = teclado.getKey();
  }

  /* Níveis de dificuldade no caso, pega o de cima e meio que transforma em um número
    para meio que o arduino entender que quer tal dificuldade, saca!!  */
  switch (key) {
    case '1':
      nivelDifi = 1;
      break;
    case '2':
      nivelDifi = 2;
      break;
    case '3':
      nivelDifi = 3;
      break;
  }

  lcd.clear();
  lcd.print("Nivel: ");
  lcd.print(nivelDifi);
  delay(1500);

  // --- Parte das contas de cada nível ---

  bool contaValid = false;
  int opRandom;

  while (!contaValid) {
    if (nivelDifi == 1) {
      x = random(1, 10);
      y = random(1, 10);
      a = random(-9, 10);
      b = random(-9, 10);
      opRandom = random(0, 2);
    } else if (nivelDifi == 2) {
      x = random(1, 10);
      y = random(1, 10);
      a = random(-9, 10);
      b = random(-9, 10);
      opRandom = random(0, 3);
    } else {
      x = random(1, 10);
      y = random(1, 10);
      a = random(-9, 10);
      b = random(-9, 10);

      if (a == 0) {
        a = 1;
      }

      if (b == 0) {
        b = 1;
      }

      opRandom = random(0, 4);
    }

    trm1 = a * x;
    trm2 = b * y;

    if (opRandom == 3) {
      if (trm2 != 0 && trm1 % trm2 == 0) {
        contaValid = true;
      } else {
        contaValid = false;
      }
    } else {
      contaValid = true;
    }

    switch (opRandom) {
      case 0:
        simbOp = '+';
        resultado = trm1 + trm2;
        break;
      case 1:
        simbOp = '-';
        resultado = trm1 - trm2;
        break;
      case 2:
        simbOp = '*';
        resultado = trm1 * trm2;
        break;
      case 3:
        simbOp = '/';
        resultado = trm1 / trm2;
        break;
    }

    // --- Parte de exibir no Display ---

    lcd.clear();
    lcd.setCursor(0, 0);

    lcd.print("(");
    if (trm1 >= 0 && nivelDifi == 3){
      lcd.print("+");
    }
    lcd.print(trm1);
    lcd.print(") ");

    lcd.print(simbOp);

    lcd.print(" (");
    if (trm2 >= 0 && nivelDifi == 3) {
      lcd.print("+");
    }
    lcd.print(trm2);
    lcd.print(")");

    // --- Parte da pessoa responder ---

    respUser = "";
    bool resposta = false;

    lcd.setCursor(0, 1);
    lcd.print("Resp:");

    while (!resposta) {
      char key = teclado.getKey();

      if (key) {
        if (key >= '0' && key <= '9') {
          respUser += key;
          lcd.setCursor(6, 1);
          lcd.print(respUser);
        } 
        else if (key == '-') {
          if (respUser.length() == 0) {
            respUser += key;
            lcd.setCursor(6, 1);
            lcd.print(respUser);
          }
        }
        else if (key == '=') {
          if (respUser.length() > 0) {
            attResp(respUser.toInt());
            resposta = true;
          }
        }
      }
    }
  }
}

void attResp(long valorUsuario) {
  lcd.clear();

  if (valorUsuario == resultado) {
    corGreen();

    lcd.setCursor(3, 0);
    lcd.print("Parabens!!");
    lcd.setCursor(2, 1);
    lcd.print("Acertou :)");
    
    somAcerto();
    noTone(buzina);
    delay(250);

    calcServo.attach(6);
    calcServo.write(90);
    delay(2500);
    calcServo.write(0);
    delay(2500);
    calcServo.detach();

  } else {
    corRed();

    lcd.setCursor(4, 0);
    lcd.print("Errouuu :'(");
    lcd.setCursor(0, 1);
    lcd.print("Resp: ");
    lcd.print(resultado);

    somErro();
  }
  noTone(buzina);
  delay(250);
  offLed();
  lcd.clear();
}

void offLed() {
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);
}

void corGreen() {
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, 238);
  digitalWrite(bPin, LOW);
}

void corRed() {
  digitalWrite(rPin, 255);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);
}

void somAcerto() {
  tone(buzina, 523);
  delay(110);
  tone(buzina, 659);
  delay(110);
  tone(buzina, 784);
  delay(110);
  tone(buzina, 1568);
  delay(110);
}

void somErro() {
  tone(buzina, 622);
  delay(300);
  tone(buzina, 587);
  delay(300);
  tone(buzina, 554);
  delay(300);

  for (byte i = 0; i < 10; i++) {
    for (int pitch = -10; pitch <= 10; pitch++) {
      tone(buzina, 532 + pitch);
      delay(5);
    }
  }
}