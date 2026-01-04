int trigPin = 7;
int echoPin = 8;
int relay = 6;
const int limiteDistancia = 100;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relay, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH);
  float distancia = duracion * 0.034 / 2;
  
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.print(" Cm");

  if (distancia < limiteDistancia) {
    digitalWrite(relay, LOW);
    Serial.println(" Torneira Aberta");
  } else {
    digitalWrite(relay, HIGH);
    Serial.println(" Torneira Fechada");
  }
  delay(100);
}