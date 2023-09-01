//MASTER CODE
//start with the slave code to understand this code 
//adding Wire library
#include <Wire.h>
//define led pin
#define led 3
//create variable to store led brightness
int led_brightness;
//create variable to store button_status that is been transfered
//from slave arduino
int button_status = 0;
//this variable is for holding prev state of the button
int button_previous_status = 0;

void setup()
{
  //begin I2C communication
  Wire.begin();
  //begin Serial communication
  Serial.begin(9600);
  //initialize led pin mode 
  pinMode(led,OUTPUT);
}

void loop()
{
  //request data (2bytes)from slave which address is (10)
  Wire.requestFrom(10,2);
  //to check if slave send the data
  if(Wire.available())
  {
    //store data send by the slave
    button_status = Wire.read();
  }
  //map button_status 0-255 and store it in led_brightness
  //so i can used for analogWrite fun
  led_brightness = map(button_status,0,4,0,255);
  
  //control led brightness
  analogWrite(led,led_brightness);
  //this if statement prevent printing the massage again and again
  //if there is no change in the button status
  if(button_status != button_previous_status)
  {
    //print led_brightness to check if it is correct
    //you can comment it (just for testing)
    //Serial.println(led_brightness);
    
    //print massage for each button_status
    if(button_status==0)
    {
      Serial.println();
    }

    else if(button_status==2)
    {
      Serial.println("Vector focused");
    }

    else if(button_status==3)
    {
      Serial.println("Vector distracted");
    }

    else
    {
      Serial.println("Glitch");
    }
    //updating the prev state of the button
    button_previous_status = button_status;
  }
  
  
}