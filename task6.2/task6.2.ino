//initialize encoder pins
#define PIN_ENCODER_A 2
#define PIN_ENCODER_B 3
//initialize counter 
long long counter = 0;

void setup()
{
  
  //initialize pins mode
  pinMode(PIN_ENCODER_A,INPUT);
  pinMode(PIN_ENCODER_B,INPUT);
  //create interrupt service
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A),ISR_encoder_A,CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B),ISR_encoder_B,CHANGE);
  Serial.begin(9600);
}

void loop()
{
  //print counter
  Serial.println(counter);
}

//updating counter value
void ISR_encoder_A()
{
  if(digitalRead(PIN_ENCODER_A)!=digitalRead(PIN_ENCODER_B))
  {
    counter++;
  }
  else
  {
    counter--;
  }
}


void ISR_encoder_B()
{
  if(digitalRead(PIN_ENCODER_A)==digitalRead(PIN_ENCODER_B))
  {
    counter++;
  }
  else
  {
    counter--;
  }
}
