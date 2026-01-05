#include <LiquidCrystal.h>
#include <OneWire.h>

// Inicializa o display LCD com os pinos RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int amostras = 1000; // Número de amostras coletadas para a média
const int pin = A0; // Pino de leitura

const float fator_atm = 0.0098692327; // Fator de conversão para atmosferas
const float fator_bar = 0.01; // Fator de conversão para bar
const float fator_kgf_cm2 = 0.0101971621; // Fator de conversão kgf/cm2

void setup() {
  pinMode(pin, INPUT); // Pino de leitura analógica
  Serial.begin(115200); // Iniciando a serial

  // Inicializa o display LCD
  lcd.begin(16, 2);
  lcd.clear();

  // Exibe mensagem inicial no LCD
  lcd.setCursor(0, 0);
  lcd.print("Sensor Pressao");
  lcd.setCursor(0, 1);
  lcd.print("Diferencial");
  delay(1000); // Aguarda 1 segundos
  lcd.clear();
}

void loop() {
  float medidas = 0.0; // Variável para manipular as medidas
  float pressao = 0.0; // Variável para armazenar o valor da pressão

  // Inicia a coleta de amostras do ADC
  for (int i = 0; i < amostras; i++) {
    medidas += analogRead(pin);
    delayMicroseconds(10); // Pequeno atraso para evitar sobrecarga
  }

  medidas = (medidas / float(amostras)); // Tira a média das amostras

  pressao = calculaPressao(medidas); // Calcula a pressão em kPa

  // Limpa o display LCD
  lcd.clear();

  // Exibe a pressão em kPa
  lcd.setCursor(0, 0);
  lcd.print("kPa: ");
  lcd.print(pressao, 2);

  // Exibe a pressão em atm e kgf/cm2 alternadamente
  if (millis() % 2000 < 1000) {
    lcd.setCursor(0, 1);
    lcd.print("atm: ");
    lcd.print(pressao * fator_atm, 4);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("kgf/cm2: ");
    lcd.print(pressao * fator_kgf_cm2, 4);
  }

  // Exibe o valor do ADC no serial monitor
  Serial.print("ADC: ");
  Serial.println(int(medidas));

  delay(1000); // Pequeno atraso para evitar sobrecarga
}

float calculaPressao(float medida) {
  // Calcula a pressão com o valor do AD corrigido pela função corrigeMedida()
  // Esta função foi escrita de acordo com dados do fabricante
  // e NÃO LEVA EM CONSIDERAÇÃO OS POSSÍVEIS DESVIOS DO COMPONENTE (erro)
  return ((corrigeMedida(medida) / 3.3) - 0.04) / 0.0012858;
}

float corrigeMedida(float x) {
  /*
    Esta função foi obtida através da relação entre a tensão aplicada no AD
    e valor lido
  */
  return 4.821224180510e-02
         + 1.180826610901e-03 * x
         - 6.640183463236e-07 * x * x
         + 5.235532597676e-10 * x * x * x
         - 2.020362975028e-13 * x * x * x * x
         + 3.809807883001e-17 * x * x * x * x * x
         - 2.896158699016e-21 * x * x * x * x * x * x;
}