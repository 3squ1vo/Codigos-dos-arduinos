/*#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* serverUrl = "http://eyzqa-200-229-209-61.a.free.pinggy.link/arduino_update";

#define temPin = 15
OneWire oneWire(temPin);
DallasTemperature sensors(&oneWire);

#define rPin 2
#define gPin 4
#define bPin 5

void setup() {
  Serial.begin(115200);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  digitalWrite(rPin, LOW);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);

  sensors.begin();

  WiFi.begin(ssid, password);
  /*Serial.println("Hello, ESP32!");*
  Serial.print("Conectando o WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverUrl);

    http.addHeader("Content-Type", "application/json");
    http.addHeader("ngrok-skip-browser-warning", "true");

    String jsonPayload = "{\"temperatura\": 22.5, \"umidade\": 50}";

    Serial.print("Enviando dados...");
    int httpResponseCode = http.POST(jsonPayload);

    Serial.print("\nCódigo HTTP: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Resposta do server em Python: " + response);

      if (response.indexOf("Ligar") > 0) {
        digitalWrite(rPin, LOW);
        digitalWrite(gPin, HIGH);
        digitalWrite(bPin, LOW);
      }
      else if (response.indexOf("Desligar") > 0) {
        digitalWrite(rPin, HIGH);
        digitalWrite(gPin, LOW);
        digitalWrite(bPin, LOW);
      }
    } else {
      Serial.print("Erro no envio: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Erro: Pode ser WiFi Desconectado ou Url errada!!");
  }
  /*delay(10);*
  delay(5000);
}*/

      /* Código modificado com o DS18B20 + DHT 22*/
#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* serverUrl = "http://vabqt-200-229-209-61.a.free.pinggy.link/arduino_update";

#define temPin 15
LiquidCrystal_I2C lcd(0x27, 16, 2);

OneWire oneWire(temPin);
DallasTemperature sensors(&oneWire);

#define dhtPin 14
#define Tipo_DHT DHT22
DHT dht(dhtPin, Tipo_DHT );

const int numReadings = 10;
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

#define rPin  2
#define gPin  4
#define bPin  5

void setup() {
  Serial.begin(115200);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  digitalWrite(rPin, LOW);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);

  sensors.begin();
  dht.begin();

  lcd.init();
  lcd.backlight();
  
  WiFi.begin(ssid, password);
  Serial.print("Conectando WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado!!");

  lcd.setCursor(3, 0);
  lcd.print("Testando o");
  lcd.setCursor(1, 1);
  lcd.print("Banco de Dados");
  delay(1500);
  lcd.clear();

  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    sensors.requestTemperatures();
    float tempReal = sensors.getTempCByIndex(0);

    float umidReal = dht.readHumidity();

    if (tempReal == -127.00) {
      Serial.println("Erro: O sensor está desconectado!!\nVerifique se ele está conectado!!");
      delay(2000);
      return;
    }

    HTTPClient http;

    http.begin(serverUrl);

    http.addHeader("Content-Type", "application/json");
    http.addHeader("ngrok-skip-browser-warning", "true");

    String jsonPayload = "{\"temperatura\": " + String(tempReal) + ", \"umidade\": " + String(umidReal) + "}";

    Serial.print("Enviando \nTemp: ");
    Serial.print(tempReal);
    Serial.println("°C | Umid: ");
    Serial.print(umidReal);
    Serial.println("%");

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(tempReal);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Umid: ");
    lcd.print(umidReal);
    lcd.print(" %");

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Resposta do Server em Python: " + response);

      if (response.indexOf("Ligar") >= 0) {
        digitalWrite(rPin, LOW);
        digitalWrite(gPin, HIGH);
        digitalWrite(bPin, LOW);
      } else if (response.indexOf("Desligar") >= 0){
        digitalWrite(rPin, HIGH);
        digitalWrite(gPin, LOW);
        digitalWrite(bPin, LOW);
      }
    } else {
      Serial.print("Código HTTP: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi caiu...");
  }
  delay(5000);
}