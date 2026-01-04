const int pin = A0; // Pino de leitura
const float fator_atm = 0.0098692327;
const float fator_kgf_cm2 = 0.0101971621;

void setup() {
  Serial.begin(115200); // Inicializa a serial
}

void loop() {
  float medidas = analogRead(pin); // Lê o valor do ADC
  float pressao = calculaPressao(medidas); // Calcula a pressão

  Serial.print("kPa: ");
  Serial.print(pressao, 2);
  Serial.print(" atm: ");
  Serial.print(pressao * fator_atm, 4);
  Serial.print(" kgf/cm2: ");
  Serial.println(pressao * fator_kgf_cm2, 4);

  delay(1000);
}

float calculaPressao(float medida) {
  return ((corrigeMedida(medida) / 3.3) - 0.04) / 0.0012858;
}

float corrigeMedida(float x) {
  return 4.821e-02 + 1.181e-03 * x - 6.64e-07 * x * x + 5.236e-10 * x * x * x
         - 2.02e-13 * x * x * x * x + 3.81e-17 * x * x * x * x * x
         - 2.896e-21 * x * x * x * x * x * x;
}
