int limiteDisparo = 600;  // Valor limite para ligar/desligar o LED
int led = 9;  // Pino do LED
int sensor = A0;  // Pino do fotoresistor (LDR)

void setup() {
  pinMode(led, OUTPUT);  // Define o LED como saída
  pinMode(sensor, INPUT);  // Define o LDR como entrada
  Serial.begin(9600);  // Inicia a comunicação serial
}

void loop(){
  int sensorValue = analogRead(sensor);  // Lê o valor do LDR
  digitalWrite(led, sensorValue < limiteDisparo ? HIGH : LOW);  // Controla o LED
  Serial.println(sensorValue);  // Imprime a leitura no monitor serial
  delay(130);  // Aguarda um pequeno intervalo
}
