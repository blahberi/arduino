#include <LiquidCrystal.h>
#include <Keypad.h>

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   5     // Configurable, see typical pin layout above
#define SS_PIN    53   // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

const long myUID = 0x2232FCBC;

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

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
String passcode = "1234";
String eneteredCode = "";
String hiddenCode = "";

#define GREEN 2
#define RED 3
#define BUZZER 34

void setup() 
{
  Serial.begin(9600);
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  lcd.begin(16, 2);
  lcd.print("Enter passcode");

  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  TrippleBeep(100, 50);
}

void HandleKeyCode(char key)
{
    eneteredCode = eneteredCode + String(key);
    hiddenCode = hiddenCode + "*";
    lcd.print(hiddenCode);
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
}

void VerifyPassword()
{
    if (eneteredCode == passcode) 
    {
      AccessGranted();
    }
    else 
    {
      AccessDenied();
    }
}

void HandleKey()
{
  // Get current keypad press
  char key = customKeypad.getKey();
  if (key) 
  {
    Serial.println("Size of *: " + String(sizeof(int*)));
    Serial.println("Size of int: " + String(sizeof(int)));
    Serial.println("Size of short: " + String(sizeof(short)));
    Serial.println("Size of long: " + String(sizeof(long)));
    lcd.setCursor(0, 1);

    switch (key)
    {
      case '#':
        VerifyPassword();
        Clear();
        break;
      case '*':
        Clear();
        break;
      default:
        HandleKeyCode(key);
        break;
    }
  }

}

void VerifyRFID()
{
  // Compare current UID to myUID
  long *uidByte = &mfrc522.uid.uidByte[0];
  if (memcmp(mfrc522.uid.uidByte, myUID, sizeof(myUID)) == 0)
  {
    AccessGranted();
  }
  else
  {
    AccessDenied();
  }
}

void HandleRFID()
{
  // Look for new cards, and select one if present
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) 
  {
    delay(50);
    return;
  }

  // Check that current UID == sizeof(myUID)
  if (sizeof(myUID) != mfrc522.uid.size) 
  {
    return;
  }

  VerifyRFID();
}

void loop() 
{
  HandleKey();
  HandleRFID();
}

void TrippleBeep(int delayON, int delayOFF)
{
  digitalWrite(BUZZER, HIGH);
  delay(delayON);
  digitalWrite(BUZZER, LOW);
  delay(delayOFF);
  digitalWrite(BUZZER, HIGH);
  delay(delayON);
  digitalWrite(BUZZER, LOW);
  delay(delayOFF);
  digitalWrite(BUZZER, HIGH);
  delay(delayON);
  digitalWrite(BUZZER, LOW);
}

void AccessGranted()
{
  lcd.setCursor(0, 1);
  lcd.print("access granted");
  digitalWrite(GREEN, HIGH);
  TrippleBeep(100, 50);
  delay(600);
  digitalWrite(GREEN, LOW);
  lcd.setCursor(0, 1);
  lcd.setCursor(0, 1);
  Clear();
}

void AccessDenied()
{
  lcd.setCursor(0, 1);
  lcd.print("access denied");
  digitalWrite(RED, HIGH);
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(RED, LOW);
  digitalWrite(BUZZER, LOW);
  lcd.setCursor(0, 1);
  lcd.setCursor(0, 1);
  Clear();
}

void Clear()
{
  lcd.setCursor(0, 1);
  lcd.print("                ");
  eneteredCode = "";
  hiddenCode = "";
}
