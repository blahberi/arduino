//www.elegoo.com
//2016.12.9

#include "IRremote.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(6, 7, 8, 9, 11, 12);

int receiver = 2; // Signal Pin of IR receiver to Arduino Digital Pin 11

void Clear(int line = 0)
{
  lcd.setCursor(0, line);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}


/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{
  Clear();
  lcd.setCursor(0, 0);
  lcd.print(results.value, HEX);
  lcd.setCursor(0, 1);
  switch (results.decode_type){
    case NEC: 
      lcd.print("NEC"); 
      break;
    case SONY: 
      lcd.print("SONY"); 
      break;
    case RC5: 
      lcd.print("RC5"); 
      break;
    case RC6: 
      lcd.print("RC6"); 
      break;
    case DISH: 
      lcd.print("DISH"); 
      break;
    case SHARP: 
      lcd.print("SHARP"); 
      break;
    case JVC: 
      lcd.print("JVC"); 
      break;
    case SANYO: 
      lcd.print("SANYO"); 
      break;
    case MITSUBISHI: 
      lcd.print("MITSUBISHI"); 
      break;
    case SAMSUNG: 
      lcd.print("SAMSUNG"); 
      break;
    case LG: 
      lcd.print("LG"); 
      break;
    case WHYNTER:
      lcd.print("WHYNTER"); 
      break;
    case AIWA_RC_T501: 
      lcd.print("AIWA_RC_T501"); 
      break;
    case PANASONIC: 
      lcd.print("PANASONIC"); 
      break;
    case DENON: 
      lcd.print("DENON"); 
      break;
  default:
    case UNKNOWN: 
      lcd.print("UNKNOWN"); 
      break;
  }
  delay(1000); // Do not get immediate repeat

  
} //END translateIR
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  lcd.begin(16, 2);
  irrecv.enableIRIn(); // Start the receiver

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */
