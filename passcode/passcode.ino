#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {23, 22, 24, 25};
byte colPins[COLS] = {28, 29, 30, 31};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
String passcode = "1234";
String eneteredCode = "";
String hiddenCode = "";

void Clear(){
  lcd.print("                ");
  eneteredCode = "";
  hiddenCode = "";
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Enter passcode");

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(34, OUTPUT);
}

void loop() {
  char key = customKeypad.getKey();
  if (key) {
    lcd.setCursor(0, 1);
    if (String(key) == "#") {
      if (eneteredCode == passcode) {
        lcd.print("access granted");
        digitalWrite(2, HIGH);
        TrippleBeep();
        delay(600);
        digitalWrite(2, LOW);
        lcd.setCursor(0, 1);
        lcd.print("                ");
      }
      else {
        lcd.print("access denied");
        digitalWrite(3, HIGH);
        digitalWrite(34, HIGH);
        delay(1000);
        digitalWrite(3, LOW);
        digitalWrite(34, LOW);
        lcd.setCursor(0, 1);
        lcd.print("                ");
      }
      Clear();
    }
    else if (String(key) == "*") {
      Clear();
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }
    else {
      eneteredCode = eneteredCode + String(key);
      hiddenCode = hiddenCode + "*";
      Serial.println(eneteredCode);
      lcd.print(hiddenCode);
      digitalWrite(34, HIGH);
      delay(100);
      digitalWrite(34, LOW);
    }
  }
}

void TrippleBeep(){
        digitalWrite(34, HIGH);
        delay(100);
        digitalWrite(34, LOW);
        delay(50);
        digitalWrite(34, HIGH);
        delay(100);
        digitalWrite(34, LOW);
        delay(50);
        digitalWrite(34, HIGH);
        delay(100);
        digitalWrite(34, LOW);
}
