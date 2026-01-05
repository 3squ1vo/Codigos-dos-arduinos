/*#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte Linhas = 4;
const byte Colunas = 3;

char teclas[Linhas][Colunas] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'-', '0', '='}
};

byte pinoLinhas[Linhas] = {8, 7, 6, 5};
byte pinoColunas[Colunas] = {4, 3, 2};

Keypad teclado = Keypad(makeKeymap(teclas), pinoLinhas, pinoColunas, Linhas, Colunas);

Servo calcServo;
int pos = -90;

long a, b, x, y;
long trm1, trm2, resultado;
String respUser;
int operacao;
char simbOp;

int buzina = 10;
int rPin = 13;
int gPin = 12;
int bPin = 11;

void setup() {
  Serial.begin(9600);
  pinMode(buzina, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  calcServo.attach(9);

  lcd.init();
  lcd.backlight();

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

  bool resp = false;
  respUser = "";

  attResp(1);

  while (resp == false) {
    char teclas = teclado.getKey();

    if (teclas) {
      if (teclas >= '0' && teclas <= '9') {
        respUser += teclas;
        attResp(1);
      } else if (teclas == '-') {
        if (respUser.length() == 0) {
          respUser += teclas;
          attResp(1);
        }
      } else if (teclas == '=') {
        if (respUser.length() == 0) {
          attResp(2);
          resp = true;
        }
      }
    }
  }
}

void attResp (int modo) {
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
      gCor();
      lcd.setCursor(4, 0);
      lcd.print("Parabens!!");
      lcd.setCursor(2, 1);
      lcd.print("Acertou :')");

      tone(buzina, 523);
      delay(110);
      tone(buzina, 659);
      delay(110);
      tone(buzina, 784);
      delay(110);
      tone(buzina, 1568);
      delay(110);

      noTone(buzina);
      delay(250);
      offled();

      calcServo.write(360);
      delay(5000);
      calcServo.write(-90);
      
      lcd.clear();
    } else {
      rCor();
      lcd.setCursor(3, 0);
      lcd.print("Errouuu :'(");
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

void rCor() {
  digitalWrite(rPin, 255);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);
}

void gCor() {
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, 238);
  digitalWrite(bPin, LOW);
}

void offled() {
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);
}*/

/*#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial); // Aguarda o monitor serial (necessário para Leonardo/Micro)
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Escaneando...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    // O scanner inicia uma transmissão para o endereço e verifica se recebe resposta
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Dispositivo I2C encontrado no endereco: 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Erro desconhecido no endereco 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("Nenhum dispositivo I2C encontrado\n");
  else
    Serial.println("Escaneamento concluido\n");

  delay(5000); // Espera 5 segundos para o próximo scan
}*/

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo calcServo;

int buzina = 10;
int rPin = 13;
int gPin = 12;
int bPin = 11;

const byte Linhas = 4;
const byte Colunas = 3;

char tecla[Linhas][Colunas] {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'-', '0', '='}
};

byte pinosLinhas[Linhas] = {8, 7, 6, 5};
byte pinosColunas[Colunas] = {4, 3, 2};

Keypad teclado = Keypad(makeKeymap(tecla), pinosLinhas, pinosColunas, Linhas, Colunas);

long a, b, x, y, trm1, trm2, resultado;
char simbOp;
int nivelDif = 1;

void setup() {
  Serial.begin(9600);

  pinMode(buzina, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  calcServo.attach(9);
  calcServo.write(0);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Cofreladora");
  delay(2000);

  randomSeed(analogRead(0));

  
}