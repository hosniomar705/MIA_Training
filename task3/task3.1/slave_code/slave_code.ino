//SLAVE CODE
//adding Wire library
#include <Wire.h>
//define buttons pins
#define B1 2
#define B2 3
//create variable for each button to store its status
int B1_status = 0;
int B2_status = 0;
//create fun to send buttons status to the master arduino
void send_state();
//create fun to encode a status of the buttons to send it to the
//master arduino
int encoder(int x,int y);

void setup()
{
  //initialize pin mode of each button
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  //begin I2C communication and initialize an address for this
  //slave arduino
  Wire.begin(10);
  //when the master requests the data the send state fun
  //will be excuted
  Wire.onRequest(send_state);
}

void loop()
{
  //read status of each button and store it
  B1_status = digitalRead(B1);
  B2_status = digitalRead(B2);
  //this delay for removing bouncing effect
  delay(50);
  
}

//this fun send state of the buttons to the master after encoding
void send_state()
{
  
  Wire.write(encoder(B1_status,B2_status));
}

//this is the encoder fun
//when b2(y)=0 and b1(x)=0 will return 0
//when b2(y)=0 and b1(x)=1 will return 2
//when b2(y)=1 and b1(x)=0 will return 3
//when b2(y)=1 and b1(x)=1 will return 4
//why return these number??
//because i need to map 0-4 to 0-255
//and get 50% when b2(y)=0 and b1(x)=1,so max value 4
//(2/4)*255 = 127 == 50%
//(3/4)*255 = 191 == 75%
//(4/4)*255 = 255 == 100%
//(0/4)*255 = 0 == 0%
int encoder(int x,int y)
{
  if(y==0 && x==0)
  {
    return(0);
  }
  else if(y==0 && x==1)
  {
    return(2);
  }
  else if(y==1 && x==0)
  {
    return(3);
  }
  else
  {
    return(4);
  }
}