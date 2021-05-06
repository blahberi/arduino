#include <IRremote.h>
 
const int switchPin1 = 4;
const int switchpin2 = 5;
int buttonState1 = 0;
int buttonState2 = 0;

 
IRsend irsend;
 
void setup()
{
  
  Serial.begin(9600);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

}
 
void loop() {
  
  buttonState1 = digitalRead(4);
  buttonState2 = digitalRead(5);
  Serial.print("POWER: ");
  Serial.println(digitalRead(4));
  Serial.print("FREEZE: ");
  Serial.println(digitalRead(4));

   if (buttonState1 == LOW) {
    irsend.sendNEC(0xC1AA09F6, 32); 
    Serial.println("power signal sent");
  }
  
  if (buttonState2 == LOW) {
    irsend.sendNEC(0xC1AA49B6, 32); 
    Serial.println("freeze signal sent");
  }
      
    
    delay(200);
}
