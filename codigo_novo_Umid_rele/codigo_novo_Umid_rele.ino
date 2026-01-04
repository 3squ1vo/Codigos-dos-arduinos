#include <LiquidCrystal.h>
#include <OneWire.h>

// Configuração do display LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int umidadePin = A0; // Pino analógico para o sensor de umidade
const int limiarSeco = 50;
const int pinoValvula = 10;
const int tempoRega = 10;
int umidadeSolo = 0;
#define RELAY_PIN 8

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  lcd.begin(16, 2); // Inicializa o display LCD
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
  lcd.print("  Rescaat 2024");
  digitalWrite(pinoValvula, HIGH);
  pinMode(pinoValvula, OUTPUT);
}

void loop() {
for(int i=0; i <5; i++);
  int umidadeValor = analogRead(umidadePin);
  umidadeValor = map(umidadeValor,1023,0,0, 100);

  lcd.setCursor(0, 1);
  lcd.print(" Umidade: ");
  lcd.print(umidadeValor);
  lcd.print(" %");
  delay(2000); // Atualiza a cada 2 segundos

  if(umidadeValor < limiarSeco) {
  // Posiciona o cursor do LCD na coluna 0 linha 1
  // (Obs: linha 1 é a segunda linha, a contagem começa em 0
  lcd.setCursor(0, 1);
  // Exibe a mensagem no Display LCD:
  lcd.print("    Regando     ");
  // Liga a válvula
  digitalWrite(pinoValvula, LOW);
  // Espera o tempo estipulado
  delay(tempoRega*1000);
  digitalWrite(pinoValvula, HIGH);
  digitalWrite(RELAY_PIN, HIGH);
  }
   else {
    lcd.setCursor(0, 1);
    lcd.print("   Encharcado   ");
    digitalWrite(RELAY_PIN, LOW);
    delay(3000);
  }
}
