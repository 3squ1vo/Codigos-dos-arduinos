/*
Tem uma variavel e o pinMode comentado é para, caso queira
testar usando um buzzer que o site tem, caso queira modificar o
código da calculadora, fique a vontade, o projeto não é só meu
só peço para tentar acoplar um sistema de cofre, que abrira somente
se a pessoa acertar o calculo, o resultado pode ser números 
com casas decimais, só se divirta e qualquer duvida e tals, não exite em 
falar comigo!!
*/

#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

const byte pinosLinhas = 4;
const byte pinosColunas = 4;

char keys[pinosLinhas][pinosColunas] {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

byte linhas[pinosLinhas] = {9, 8, 7, 6};
byte colunas[pinosColunas] = {5, 4, 3, 2};

Keypad teclado = Keypad(makeKeymap(keys), linhas, colunas, pinosLinhas, pinosColunas);


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//int buzina = 10;

String numDigit = "";
float num1 = 0;
float num2 = 0;
char operador = ' ';
bool calcFinal = false;

void setup() {
  Serial.begin(9600);
  //pinMode(buzina, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("AFI apresenta:");
  lcd.setCursor(0, 1);
  lcd.print("Cofreladora");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.blink();
}

void loop() {
  char tecla = teclado.getKey();

  if (tecla) {
    if(tecla >= '0' && tecla <= '9') {
      if (calcFinal) {
        lcd.clear();
        lcd.setCursor(0, 0);
        numDigit = "";
        num1 = 0;
        operador = ' ';
        calcFinal = false;
      }

      numDigit += tecla;
      lcd.print(tecla);
    }
    else if (tecla == '+' || tecla == '-' || tecla == '*' || tecla == '/') {
      if (numDigit != "") {
        num1 = numDigit.toFloat();
        operador = tecla;
        numDigit = "";

        lcd.print(tecla);
      }
    }
    else if (tecla == '=') {
      if (operador != ' ' && numDigit != "") {
        num2 = numDigit.toFloat();
        float resultado = 0;
        bool erro = false;

        if (operador == '+') resultado = num1 + num2;
        if (operador == '-') resultado = num1 - num2;
        if (operador == '*') resultado = num1 * num2;
        if (operador == '/') {
          if (num2 == 0) erro = true;
          else resultado = num1 / num2;
        }
        lcd.seCursor(0, 1);
        lcd.print("=");

        if (erro) {
          lcd.print("Erro Div 0");
        }
        else {
          if (resultado == (int)resultado) {
            lcd.print((int)resultado);
          }
          else {
            lcd.print(resultado);
          }
        }
        calcFinal = true;
      }
    }
    else if (tecla == 'C') {
      lcd.clear();

      numDigit = "";
      num1 = 0;
      num2 = 0;
      operador = ' ';
      calcFinal = false;

      lcd.setCursor(0, 0);
    }
  }
}
