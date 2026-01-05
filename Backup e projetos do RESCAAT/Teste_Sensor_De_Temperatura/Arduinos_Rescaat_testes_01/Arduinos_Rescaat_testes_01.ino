// Inclui as bibliotecas
#include <LiquidCrystal.h>
#include <OneWire.h>

// Define os pinos de conexão entre o Arduino e o Display LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Variáveis do programa
const int pinoSensorUmidade = A0;
const int pinoValvula = 10;
const int limiarSeco = 40;
const int tempoRega = 10; // Tempo de rega em segundos
int umidadeSolo = 0;

// Constantes do sensor de pressão
const int sensorPressaoPin = A1; // Pino analógico ao qual o sensor está conectado
const float supplyVoltage = 5.0; // Tensão de alimentação do sensor (em volts)

void setup() {
  pinMode(pinoValvula, OUTPUT);
  // Desliga a válvula
  digitalWrite(pinoValvula, HIGH);

  // Define o tamanho do Display LCD
  lcd.begin(16, 2);
  // Exibe a mensagem no Display LCD.
  lcd.print(" Rescaat");

  // Inicializa a comunicação serial
  Serial.begin(9600);

}

void loop() {
  // Mede a umidade a cada segundo. Faz isso durante uma hora (3600 segundos).
  for (int i = 0; i < 5; i++) {
    // Posiciona o cursor do LCD na coluna 0 linha 0
    lcd.setCursor(0, 0);
    // Exibe a mensagem no Display LCD:
    lcd.print("Umidade: ");
    // Faz a leitura do sensor de umidade do solo
    umidadeSolo = analogRead(pinoSensorUmidade);
    // Converte a variação do sensor de 0 a 1023 para 0 a 100
    umidadeSolo = map(umidadeSolo, 1023, 0, 0, 100);
    // Exibe a umidade no Display LCD
    lcd.print(umidadeSolo);
    lcd.print(" %    ");
    // Espera um segundo
    delay(250);
  }

  // Leitura da pressão
  float sensorValue = analogRead(sensorPressaoPin); // Lê o valor do sensor (de 0 a 1023)
  float pressure = map(sensorValue, 0, 1023, 0, 500); // Mapeia o valor do sensor para uma faixa de pressão (em kPa)

  // Exibe a pressão medida no Display LCD
  lcd.setCursor(0, 1);
  lcd.print("Pre ");
  lcd.print(pressure);
  lcd.print(" kPa ");

  // Controle da rega baseado na umidade do solo
  if (umidadeSolo < limiarSeco) {
    // Exibe a mensagem no Display LCD indicando que está regando
    lcd.setCursor(0, 1);
    lcd.print(" ON ");
    // Liga a válvula
    digitalWrite(pinoValvula, LOW);
    // Espera o tempo estipulado
    delay(tempoRega * 1000);
    // Desliga a válvula
    digitalWrite(pinoValvula, HIGH);
  } else {
    // Exibe a mensagem no Display LCD indicando solo úmido
    lcd.setCursor(0, 1);
    lcd.print("OFF");
    // Espera um tempo
    delay(3000);
  }
}