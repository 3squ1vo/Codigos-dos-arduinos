#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo calcServo;

int buzina = 2;
int rPin = 6;
int gPin = 5;
int bPin = 4;
int pos = -90;

const byte Linhas = 4;
const byte Colunas = 3;

char teclas[Linhas][Colunas] {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'-', '0', '='}
};

byte pinoLinhas[Linhas] = {13, 12, 11, 10};
byte pinoColunas[Colunas] = {9, 8, 7};

Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, Linhas, Colunas);

long a, b, x, y, trm1, trm2, resultado;
String respUser;
int operacao;
char simbOp;
int nivelDifi = 1;

void setup() {
  Serial.begin(9600);
  pinMode(buzina, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  calcServo.attach(3);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(3, 0);
  lcd.print("Cofreladora");
  delay(2000);
  lcd.clear();

  randomSeed(analogRead(0));
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1-Facil 2-Medio");
  lcd.setCursor(0, 1);
  lcd.print("3-Dif Escolha:");

  char key = 0;
  while(key != '1' && key != '2' && key! = '3') {
    key = teclado.getKey();
  }

  nivelDifi = key - '0';

  lcd.clear();
  lcd.print("Nivel: ");
  lcd.print(nivelDifi);
  delay(1500);

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

      if (a == 0) a = 1;
      if (b == 0) b = 1;
      opRandom = random(0, 4);
    }

    trm1 = a * x;
    trm2 = b * y;

    if (opRandom == 3) {
      if (trm2 != 0 && trm1 % trm2 == 0) contaValid = true;
    } else {
      contaValid = true;
    }
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

  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("(");
  if (trm1 > 0 && nivelDif == 3) lcd.print("+");
  lcd.print(trm1);
  lcd.print(")");

  lcd.print(simbOp);

  lcd.print("(");
  if (trm2 > 0 && nivelDifi == 3); lcd.print("+");
  lcd.print(trm2);
  lcd.print(")");

  bool resp = false;
  respUser = "";

  attResp(1);

  while (resp = false) {
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
        if (respUser.length() > 0){
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
        lcd.print("Parabens");
        lcd.setCursor(2, 1);
        lcd.print()
      }
  }
}

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