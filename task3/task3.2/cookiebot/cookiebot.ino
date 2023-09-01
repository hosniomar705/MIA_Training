//room dimensions in cm
int room_length = 500;
int room_width = 600;

//Right ultrasonic sensor
const int Right_pingPin = 3; // Trigger Pin of Ultrasonic Sensor
const int Right_echoPin = 2; // Echo Pin of Ultrasonic Sensor
//Left ultrasonic sensor
const int Left_pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int Left_echoPin = 4; // Echo Pin of Ultrasonic Sensor
//Up ultrasonic sensor
const int Up_pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int Up_echoPin = 6; // Echo Pin of Ultrasonic Sensor
//Down ultrasonic sensor
const int Down_pingPin = 9; // Trigger Pin of Ultrasonic Sensor
const int Down_echoPin = 8; // Echo Pin of Ultrasonic Sensor

//this fun to calculate_distance from ultra sonic sensor
//takes pingPin number and echoPin number
//returns distance in cm
long calculate_distance(int pingPin,int echoPin);

void setup()
{
  Serial.begin(9600); // Starting Serial Terminal
  //initialize pin mode for each ultrasonic sensor
  pinMode(Right_pingPin, OUTPUT);
  pinMode(Right_echoPin, INPUT);
  
  pinMode(Left_pingPin, OUTPUT);
  pinMode(Left_echoPin, INPUT);
  
  pinMode(Up_pingPin, OUTPUT);
  pinMode(Up_echoPin, INPUT);
  
  pinMode(Down_pingPin, OUTPUT);
  pinMode(Down_echoPin, INPUT);
}

void loop()
{
  //create variables to store distance and position
  long Right_dis,left_dis,Up_dis,Down_dis,x_pos,y_pos;
  
  //calculating distance from each sensor
  Right_dis = calculate_distance(Right_pingPin,Right_echoPin);
  left_dis = calculate_distance(Left_pingPin,Left_echoPin);
  Up_dis = calculate_distance(Up_pingPin,Up_echoPin);
  Down_dis = calculate_distance(Down_pingPin,Down_echoPin);
  //calculating the position of the bot
  //because the bot has a dimensions i dont konw 
  //so i used this equ to calcutale its position taking 
  //the center of the bot as a reference
  x_pos = left_dis + ((room_length-(left_dis+Right_dis))/2);
  y_pos = Down_dis + ((room_width-(Down_dis+Up_dis))/2);
  
  Serial.print(x_pos);
  Serial.print(',');
  Serial.println(y_pos);
}

long calculate_distance(int pingPin,int echoPin)
{
  long distance,duration;
  // Clears the pingPin
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  // Sets the pingPin on HIGH state for 10 micro seconds
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; 
  return(distance);
}