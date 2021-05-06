#define BTNL 2
#define BTNR 8
#define LEDL 7
#define LEDR 13

bool isFirst = true;
bool RightIsUp = false;
bool LeftIsUp = false;

void setup() {
  pinMode(BTNL, INPUT_PULLUP);
  pinMode(BTNR, INPUT_PULLUP);
  pinMode(LEDL, OUTPUT); 
  pinMode(LEDR, OUTPUT);
}

void loop() {
  if (isFirst){
    if (digitalRead(BTNL) == LOW)
    {
      RightIsUp = true;
      digitalWrite(LEDR, HIGH);
      isFirst = false;
    }
    else if (digitalRead(BTNR) == LOW)
    {
      LeftIsUp = true;
      digitalWrite(LEDL, HIGH);
      isFirst = false;
    }
  }
  else
  {
    if (LeftIsUp)
    {
      if (digitalRead(BTNL) == LOW)
      {
        RightIsUp = true;
        digitalWrite(LEDR, HIGH);
        LeftIsUp = false;
        digitalWrite(LEDL, LOW);
      }
    }
    else if(RightIsUp)
    {
      if (digitalRead(BTNR) == LOW)
      {
        LeftIsUp = true;
        digitalWrite(LEDL, HIGH);
        RightIsUp = false;
        digitalWrite(LEDR, LOW);
      }
    }
  }
}
