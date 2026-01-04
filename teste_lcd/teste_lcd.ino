#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd (rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Ola");
}

void loop() {

}
