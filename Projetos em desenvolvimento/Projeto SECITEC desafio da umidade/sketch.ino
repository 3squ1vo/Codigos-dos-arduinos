const int rPin = 2;
const int gPin = 3;
const int bPin = 4;
int buzina = 9;
int sensPin = A0;

const int limitMin = 45;
const int limitMax = 55;
const int sensMin = 0;
const int sensMax = 1023;
const int sensAr = 800;


void setup() {
  Serial.begin(9600);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(buzina, OUTPUT);
}

void loop() {
  Serial.println("\nAguardando sensor no solo...");
  corBlue();
  
  while (analogRead(sensPin) == sensAr){
    tone(buzina, 392, 70);
    delay(750);
    tone(buzina, 415, 70);
    delay(750);
  }

  noTone(buzina);
  Serial.println("Fazendo leitura...");
  delay(1000);

  int valorSens = analogRead(sensPin);
  int umidSolo = map (valorSens, sensMax, sensMin, 0, 100);
  
  Serial.print("Umidade: ");
  Serial.print(umidSolo);
  Serial.println(" %");

  if (umidSolo > limitMax || umidSolo < limitMin) {
    Serial.println("Resultado: Você... Errou que peninha!!");
    corRed();
    tone(buzina, 622);
    delay(300);
    tone(buzina, 587);
    delay(300);
    tone(buzina, 554);
    delay(300);
    for (byte i = 0; i < 10; i++) {
      for (int pitch = -10; pitch <= 10; pitch++) {
        tone(buzina, 523 + pitch);
        delay(5);
      }
    }
    noTone(buzina);
    delay(500);
  } else {
    Serial.println("Resultado: Você... Acertou, parabens!!");
    tone(buzina, 523, 110);
    delay(110);
    tone(buzina, 659, 110);
    delay(110);
    tone(buzina, 784, 110);
    delay(110);
    tone(buzina, 1568, 165);
    delay(165);
  }
  delay(2500);
  noTone(buzina);
  offLed();
  delay(1000);
}


void corRed() {
  digitalWrite(rPin, 255);
  digitalWrite(gPin, 0);
  digitalWrite(bPin, 0);
}

void corGreen() {
  digitalWrite(rPin, 0);
  digitalWrite(gPin, 238);
  digitalWrite(bPin, 0);
}

void corBlue() {
  digitalWrite(rPin, 0);
  digitalWrite(gPin, 191);
  digitalWrite(bPin, 255);
}

void offLed() {
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);
}