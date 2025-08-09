#include <LiquidCrystal.h>

// LCD pin connections: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int flexPins[5] = {A0, A1, A2, A3, A4}; // thumb..pinky
int threshold = 600; // Bend threshold (tune for your sensors)

// Read flex sensor state (true = bent, false = straight)
bool isBent(int pin) {
  int value = analogRead(pin);
  return (value > threshold); // adjust for your sensor range
}

void setup() {
  lcd.begin(16, 2);           // initialize LCD
  lcd.print("Smart Gloves");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  bool bent[5];
  for (int i = 0; i < 5; i++) {
    bent[i] = isBent(flexPins[i]);
  }

  lcd.clear();
  lcd.setCursor(0, 0);

  // Simple gesture detection
  if (bent[0] && bent[1] && bent[2] && bent[3] && bent[4]) {
    lcd.print("EMERGENCY");
  }
  else if (!bent[0] && bent[1] && bent[2] && bent[3] && bent[4]) {
    lcd.print("HELP");
  }
  else if (!bent[1] && bent[0] && bent[2] && bent[3] && bent[4]) {
    lcd.print("YES");
  }
  else if (!bent[1] && !bent[2] && bent[0] && bent[3] && bent[4]) {
    lcd.print("NO");
  }
  else {
    lcd.print("No Gesture");
  }

  delay(1000);
}
