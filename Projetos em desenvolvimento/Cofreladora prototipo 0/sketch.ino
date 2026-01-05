/*No verifyResp tu pode adicionar a parte do cofre, provavelmente,
  irei usar, um buzzer e/ou um led RGB, para teste mas pode usar isso e o
  else!!*/

#include <LiquidCrystal.h>
/*#include <LiquidCrystal_I2C.h>*/
#include <Keypad.h>
#include <Servo.h>

/*LiquidCrystal_I2C lcd(0x24, 16, 2);*/
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);

const byte Linhas = 4;
const byte Colunas = 4;

char teclas[Linhas][Colunas] = {
  {'1', '2', '3'/*, '+'*/},
  {'4', '5', '6'/*, '-'*/},
  {'7', '8', '9'/*, '*'*/},
  {'-', '0', '='/*, '/'*/}
};

byte pinoLinhas[Linhas] = {22, 23, 24, 25};
byte pinoColunas[Colunas] = {26, 27, 28, 29};

Keypad teclado = Keypad(makeKeymap(teclas), pinoLinhas, pinoColunas, Linhas, Colunas);

Servo cofreServo;
int pos = -90;

long a, b, x, y;
long trm1, trm2, resultado;
String respUser;
int operacao;
char simbOp;

int buzina = 7;
int rPin = 10;
int gPin = 9;
int bPin = 8;

void setup() {
  Serial.begin(9600);
  pinMode(buzina, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  cofreServo.attach(13);

  /*lcd.init();*/
  /*lcd.backlight();*/
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Cofreladora");
  delay(2000);
  lcd.clear();

  randomSeed(analogRead(0));
}

void loop() {
  bool contaValid = false;

  while (!contaValid) {
    x = random(1, 10);
    y = random(1, 10);
    a = random(-9, 10);
    b = random(-9, 10);

    if (a == 0) a = 1;
    if (b == 0) b = 1;

    trm1 = a * x;
    trm2 = b * y;

    operacao = random(0, 4);

    if (operacao == 3) {
      if (trm2 != 0 && trm1 % trm2 == 0) {
        contaValid = true;
      }
    } else {
      contaValid = true;
    }
  }

  switch (operacao) {
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

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("(");
  if (trm1 > 0) lcd.print("+");
  lcd.print(trm1);
  lcd.print(") ");
  lcd.print(simbOp);
  lcd.print(" (");
  if (trm2 > 0) lcd.print("+");
  lcd.print(trm2);
  lcd.print(")");

  bool  resp = false;
  respUser = "";

  attResp(1);

  while (resp == false) {
    char tecla = teclado.getKey();

    if (tecla) {
      if (tecla >= '0' && tecla <= '9') {
        respUser += tecla;
        attResp(1);
      }
      else if (tecla == '-') {
        if (respUser.length() == 0) {
          respUser += tecla;
          attResp(1);
        }
      }
      else if (tecla == '=') {
        if (respUser.length() > 0) {
          attResp(2);
          resp = true;
        }
      }
    }
  }
}

void attResp(int modo) {
  switch (modo) {
    case 1:
      lcd.setCursor(0, 1);
      lcd.print("Resp: ");
      lcd.print(respUser);
      break;

    case 2:
      long userResp = respUser.toInt();
      lcd.clear();

      if (userResp == resultado) {
        corGreen();
        lcd.setCursor(4, 0);
        lcd.print("Parabuains");
        lcd.setCursor(2, 1);
        lcd.print("Acertou :')");
        tone(buzina, 523);
        delay(110);
        tone(buzina, 659);
        delay(110);
        tone(buzina, 784);
        delay(110);
        tone(buzina, 1568);
        delay(150);
        
        noTone(buzina);
        delay(250);
        offled();
        cofreServo.write(360);
        delay(15000);
        cofreServo.write(-90);
        lcd.clear();
      }
      else {
        corRed();
        lcd.setCursor(3, 0);
        lcd.print("Errrouu :'(");
        lcd.setCursor(0, 1);
        lcd.print("Resp: ");
        lcd.print(resultado);
        tone(buzina, 622);
        delay(300);
        tone(buzina, 587);
        delay(300);
        tone(buzina, 554);
        delay(300);
        for (byte i = 0; i < 10; i++) {
          for (int pitch = -10; pitch <= 10; pitch++) {
            tone(buzina, 523 + pitch);
            delay(5);
          }
        }
        noTone(buzina);
        delay(250);
        offled();
        lcd.clear();
        break;
      }
  }
}


void corRed() {
  digitalWrite(rPin, 255);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);
}

void corGreen() {
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, 238);
  digitalWrite(bPin, LOW);
}

void offled() {
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);
}