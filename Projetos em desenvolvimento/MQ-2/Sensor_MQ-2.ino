int gasPin = A0;
int ledPin = 7;
int buzina = 6;
int gasLimit = 300;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzina, OUTPUT);
  Serial.println("MQ-2 Ligando...");
  delay(500);
  Serial.println("MQ-2 Ligado e Operante");
  delay(500);
}

void loop() {
  int valordoGas = analogRead(gasPin);
  
  Serial.print("Leitura MQ-2: ");
  Serial.print(valordoGas);
  
  if (valordoGas > gasLimit) {
    digitalWrite(ledPin, HIGH);
    tone(buzina, 523);
    Serial.println(" OLHA O GAS/FUMAÇA, ACIONE A VENTILAÇÃO!!");
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzina);
    Serial.println(" Ar limpo!!");
  }
  delay(1000);
}
