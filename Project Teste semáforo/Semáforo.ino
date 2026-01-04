#define trigPin 11
#define echoPin 10
long duracion;
int distancia;

int ledPinr = 8;
int ledPina = 7;
int ledPinv = 6;
int distanciaTotal = 199;
int buzina = 12;
int buzina1 = 13;

unsigned long tiempoAnterior = 0;
const long intervalo = 500;

void setup() {
 Serial.begin(9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(buzina, OUTPUT);
 pinMode(buzina1, OUTPUT);
 noTone(buzina);
 noTone(buzina1);
}

void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duracion = pulseIn(echoPin, HIGH);

    distancia = duracion * 0.034 / 2;

    Serial.print("Distância: ");
    Serial.print(distancia);
    Serial.println(" cm");
  
  if (distancia < distanciaTotal) {
    Serial.println("Atenção!!");
    digitalWrite(ledPina, HIGH);
    digitalWrite(ledPinr, LOW);
    tone(buzina, 262, 125);
    delay(1000);

    digitalWrite(ledPina, LOW);
    digitalWrite(ledPinr, HIGH);
    tone(buzina, 131, 125);
    delay(3000);
  }
 }