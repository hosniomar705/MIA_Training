#include <Wire.h>

//define addresses
#define IMU_ADDRESS 0x68
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define PWR_MGMT_1 0x6B

#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

//number of samples for 
# define N_SAMPLES 3000

//initialize variables to store acc and gyro date and normalized data
int16_t acc_x = 0;
int16_t acc_y = 0;
int16_t acc_z = 0;

float N_acc_x = 0;
float N_acc_y = 0;
float N_acc_z = 0;

int16_t gyro_x = 0;
int16_t gyro_y = 0;
int16_t gyro_z = 0;

float N_gyro_x = 0;
float N_gyro_y = 0;
float N_gyro_z = 0;

//initialize variables to store acc and gyro offset
int16_t gyro_offset_x = 0;
int16_t gyro_offset_y = 0;
int16_t gyro_offset_z = 0;

int16_t acc_offset_x = 0;
int16_t acc_offset_y = 0;
int16_t acc_offset_z = 0;
//initialize variables to store angles
float pitch = 0;
float roll = 0;
float yaw = 0;

//initialize variables to store time_step and old_time
float time_step = .001;
unsigned long old_time = millis();


void setup()
{
  //initialize MPU
  MPU_init();
  //initialize GYRO
  MPU_GyroConfig();
  //initialize ACC
  MPU_AccelConfig();
  //calibrating the sensor
  MPU_Calibration();
  
  Serial.begin(115200);
}

void loop()
{
  //calculating the angles every time step(i coukd use time interrupt "Timer.h" but it didn't work idk why)
  if(millis()-old_time>= time_step*1000)
  {
    //update time
    old_time = millis();
    
    //read acc values
    MPU_readAcc_XYZ();
    //read gyro values
    MPU_readGyro_XYZ();
    
    //Normalize values according to max range we have selected in AccelConfig and GyroConfig
    Acc_Normalization(2);//fun takes make range i have selected 2 g
    Gyro_Normalization(250);//fun takes make range i have selected 250 degree/s
    
    //calculate angles using euler's angles method(i should have calculated the angles using acc reading the applying a filter such as[kalman or complementary] but the time of the task is very limited :( ) 
    get_angles();

    //print angles
    Serial.print(" Pitch = ");
    Serial.print(pitch);
    Serial.print(" Roll = ");
    Serial.print(roll);  
    Serial.print(" Yaw = ");
    Serial.println(yaw);
  }

 
}







//initialize MPU
void MPU_init()
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(PWR_MGMT_1);
  Wire.write(0x00);
  Wire.endTransmission();
}
//initialize GYRO sensor
void MPU_GyroConfig()
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(GYRO_CONFIG);
  Wire.write(0x00);
  Wire.endTransmission();
}
//initialize ACC sensor
void MPU_AccelConfig()
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(ACCEL_CONFIG);
  Wire.write(0x00);
  Wire.endTransmission();
} 




//read Gyro senor readings from the registers 
void MPU_readGyro_XYZ()
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(GYRO_XOUT_H);
  Wire.endTransmission();

  Wire.requestFrom(IMU_ADDRESS,6);

  while(Wire.available()<6);

  gyro_x = Wire.read()<<8 | Wire.read();
  gyro_y = Wire.read()<<8 | Wire.read();
  gyro_z = Wire.read()<<8 | Wire.read();

  gyro_x -= gyro_offset_x;
  gyro_y -= gyro_offset_y;
  gyro_z -= gyro_offset_z;
  
}
//read Acc senor readings from the registers
void MPU_readAcc_XYZ()
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission();

  Wire.requestFrom(IMU_ADDRESS,6);

  while(Wire.available()<6);

  acc_x = Wire.read()<<8 | Wire.read();
  acc_y = Wire.read()<<8 | Wire.read();
  acc_z = Wire.read()<<8 | Wire.read();

  acc_x -= acc_offset_x;
  acc_y -= acc_offset_y;
  acc_z -= acc_offset_z;
}


// calibrate Gyro and Acc sensor before taking readings from them
void MPU_Calibration()
{
 for(int i = 0; i < N_SAMPLES; i++)
 {
  MPU_readGyro_XYZ();
  MPU_readAcc_XYZ();
  
  gyro_offset_x += gyro_x;
  gyro_offset_y += gyro_y;
  gyro_offset_z += gyro_z;

  acc_offset_x += acc_x;
  acc_offset_y += acc_y;
  acc_offset_z += acc_z;
 }
 
 gyro_offset_x /= N_SAMPLES;
 gyro_offset_y /= N_SAMPLES;
 gyro_offset_z /= N_SAMPLES;

 acc_offset_x /= N_SAMPLES;
 acc_offset_y /= N_SAMPLES;
 acc_offset_z /= N_SAMPLES;
}


//Normalize values to the selected range
void Acc_Normalization(int s)
{
  N_acc_x = 1.0*acc_x * s /32786;
  N_acc_y = 1.0*acc_y * s /32786;
  N_acc_z = 1.0*acc_z * s /32786;
}
//Normalize values to the selected range
void Gyro_Normalization(int s)
{
  N_gyro_x = 1.0*gyro_x * s /32786;
  N_gyro_y = 1.0*gyro_y * s /32786;
  N_gyro_z = 1.0*gyro_z * s /32786;
}



//convert normalized Gyro reading to eular rate then updating the angles
void get_angles()
{
  float phi_dot = N_gyro_x + (N_gyro_y * sin(roll) * tan(pitch)) + (N_gyro_z * cos(roll) * tan(pitch));;
  float theta_dot = N_gyro_y * cos(roll) - N_gyro_z * sin(roll);
  float psi_dot = (N_gyro_y * sin(roll)) / cos(pitch) + (N_gyro_z * cos(roll)) / cos(pitch);

  roll = roll + phi_dot * time_step;
  pitch = pitch + theta_dot * time_step;
  yaw = yaw +psi_dot  * time_step;
}
