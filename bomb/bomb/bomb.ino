#include <LiquidCrystal.h>
#include <Keypad.h>

#define ROWS 4
#define COLS 4
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {22, 25, 26, 29};
byte colPins[COLS] = {30, 33, 34, 37};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

#define GREEN 2
#define RED 3
#define BUZZER 53


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(5, 7, 8, 9, 11, 12);
bool timer = true;
String passcode = "0911";

String enteredCode = "";
int timeInMinutes = 45;
long lastSecond = millis();
int devider = 1000;


void Clear(int line = 0)
{
  lcd.setCursor(0, line);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  enteredCode = "";
}


void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  TrippleBeep(100, 50);
}

void loop() 
{
  HandleTimer();
  HandleKey();
}

void HandleTimer()
{
  lcd.setCursor(5, 0);
  int minutes = timeInMinutes - (millis()/(60*devider));
  int seconds = 59 - (millis() / devider) % 60;
  if (timer){
    if (minutes < 10)
    {
      lcd.print('0');
      lcd.print(minutes);
    }
    else
    {
      lcd.print(minutes); 
    }
    lcd.print(':');
    if (seconds < 10)
    {
      lcd.print(0);
      lcd.print(seconds);
    }
    else
    {
      lcd.print(seconds);
    }
  
    if(minutes <= 0 && seconds < 30)
    {
      if (seconds <= 0 || minutes < 0)
      {
        Clear();
        lcd.setCursor(5, 0);
        lcd.print("00:00");
        lcd.setCursor(3,1);
        lcd.print("GAME OVER");
        timer = false;
        delay(1000);
        Beep(3*1000);
        digitalWrite(BUZZER, LOW);
      }
      if(millis() - lastSecond > seconds*32)
      {
        Beep(100);
        lastSecond = millis();
      }
    }
  }
}

void AccessDenied()
{
  lcd.setCursor(0, 0);
  lcd.print("wrong password");
  Beep(1000);
  devider = devider/2;
  Clear();
}

void AccessGranted()
{
  Clear(1);
  lcd.setCursor(0, 1);
  lcd.print("congradulations");
  digitalWrite(GREEN, HIGH);
  TrippleBeep(100, 50);
  delay(600);
  digitalWrite(GREEN, LOW);
  timer = false;
}

void VerifyPassword()
{
    if (enteredCode == passcode) 
    {
      AccessGranted();
    }
    else 
    {
      AccessDenied();
    }
}

void TrippleBeep(int delayON, int delayOFF)
{
  Beep(delayON);
  delay(delayOFF);
  Beep(delayON);
  delay(delayOFF);
  Beep(delayON);
}


void HandleKey()
{
  // Get current keypad press
  char key = customKeypad.getKey();
  if (key) 
  {
    lcd.setCursor(0, 1);

    switch (key)
    {
      case '#':
        VerifyPassword();
        break;
      case '*':
        Clear(1);
        break;
      default:
        HandleKeyCode(key);
        break;
    }
  }
}

void HandleKeyCode(char key)
{
    enteredCode = enteredCode + String(key);
    lcd.print(enteredCode);
    Beep(100);
}

void Beep(int duration)
{
  digitalWrite(BUZZER, HIGH);
  delay(duration);
  digitalWrite(BUZZER, LOW);
}
