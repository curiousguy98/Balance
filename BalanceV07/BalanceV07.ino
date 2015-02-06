
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

int nStepCount = 0;
int iStepDir1 = 0;
int iStepDir2 = 0;

int motorSpeed = 100;

#define JOYSTICK_MAX_THRES  800
#define JOYSTICK_MIN_THRES  200
#define MOVE_DIR_UP  1
#define MOVE_DIR_DOWN  -1
#define MOVE_DIR_STAY  0

MeJoystick joystick1(PORT_8);
MeJoystick joystick2(PORT_7);

MeLimitSwitch limitSwitch1(PORT_4); 
MeLimitSwitch limitSwitch2(PORT_3); 

MeDCMotor motor1(M2); 
MeDCMotor motor2(M1);


int y1 = 0;      // a variable for the Joystick's x value
int y2 = 0;      // a variable for the Joystick's y value

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  ///NO1 Motor control
  y1 = joystick1.readY(); 


  if(y1 < JOYSTICK_MIN_THRES){
    iStepDir1 = MOVE_DIR_UP;
    motorSpeed = (500 - y1) / 2;
  Serial.println("Y1");
  Serial.println(y1);    
  }
  else if(y1 > JOYSTICK_MAX_THRES){
    iStepDir1 = MOVE_DIR_DOWN;
    motorSpeed = (y1 -500) / 2;
  }
  else{
    iStepDir1 = MOVE_DIR_STAY;
    motorSpeed = 0;
  }
  
   if(limitSwitch1.touched() && iStepDir1==-1){
      iStepDir1 = MOVE_DIR_STAY;
      motor1.run(100);
      delay(100);
      motor1.stop();      
   }
   
  if(iStepDir1==MOVE_DIR_UP){
    motor1.run(motorSpeed);
  }
  else if(iStepDir1==MOVE_DIR_DOWN){
    motor1.run(-motorSpeed);
  }
  else{
    motor1.stop();   
  }
  
  ///NO2 Motor control
  y2 = joystick2.readY(); 

  if(y2 < JOYSTICK_MIN_THRES){
    iStepDir2 = MOVE_DIR_UP;
    motorSpeed = (500 - y2) / 2;
  Serial.println("Y2");
  Serial.println(y2);    
  }
  else if(y2 > JOYSTICK_MAX_THRES){
    iStepDir2 = MOVE_DIR_DOWN;
    motorSpeed = (y2 - 500) / 2;
  }
  else{
    iStepDir2 = MOVE_DIR_STAY;
    motorSpeed = 0;
  }
  
  if(limitSwitch2.touched() && iStepDir2==-1){
      iStepDir2 = MOVE_DIR_STAY;
      motor2.run(100);
      delay(100);
      motor2.stop();        
  }
   
  if(iStepDir2==MOVE_DIR_UP){
    motor2.run(motorSpeed);
  }
  else if(iStepDir2==MOVE_DIR_DOWN){
    motor2.run(-motorSpeed);
  }
  else{
    motor2.stop();   
  }
  
}
