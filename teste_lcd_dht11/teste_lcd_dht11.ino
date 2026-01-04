#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int h;
int t;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd (rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(1000);

  Serial.begin(9600);

  Serial.println("Temperature and Humidity Sensor Test");
  
  dht.begin();

}

void loop() {
  h = dht.readHumidity();

  t = dht.readTemperature();
  
  Serial.print("Humidity: ");

  Serial.print(h);

  Serial.print(" %, Temp: ");

  Serial.print(t);

  Serial.println(" ° Celsius");

  lcd.setCursor(0, 0);

  lcd.println(" Simple Circuits");

  lcd.setCursor(0, 1);

  lcd.print(" T:");

  lcd.print(t);

  lcd.print("C");

  lcd.setCursor(11, 1);

  lcd.print("H:");

  lcd.print(h);

  lcd.print("%");

  delay(1000); 
}
