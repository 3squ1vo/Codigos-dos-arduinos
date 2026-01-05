#include <LiquidCrystal.h>

int seconds = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("RESCAAT!!!");
  delay(1000);
}

void loop() {
}