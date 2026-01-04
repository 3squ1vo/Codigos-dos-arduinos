#include <LiquidCrystal.h>

// Configuração do display LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define RELAY_PIN 9
const int umidadePin = A0; // Pino analógico para o sensor de umidade
const int limiarSeco = 50;
const int pinoValvula = 10;
const int tempoRega = 10;
int umidadeSolo = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  
  lcd.begin(16, 2); // Inicializa o display LCD
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
  lcd.print("  Smart Crop ");
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
  digitalWrite(RELAY_PIN, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("    Regando     ");
  delay(tempoRega*1000);
  }
   else {
    digitalWrite(RELAY_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("   Encharcado   ");
    
    delay(3000);
  }
}
