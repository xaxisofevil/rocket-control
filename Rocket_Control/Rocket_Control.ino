#include <Servo.h> 
//servo setup 
Servo xservo;  // create servo object to control X axis
Servo yservo;  // create servo object to control Y axis

int xservoRange = 180;  //check the spec sheet for this value
int yservoRange = 180;  //check the spec sheet for this value
int xservoNull = xservoRange / 2; //find the null angle
int yservoNull = yservoRange / 2; //find the null angle

//gyro setup
int xgyroPin = 6;              //X Gyro is connected to analog pin 6
int ygyroPin = 7;              //Y Gyro is connected to analog pin 7

float gyroVoltage = 3.3;         //Gyro is running off the 3.3V pin
float gyroZeroVoltage = 1.23;   //Gyro is zeroed at 1.23V
float gyroSensitivity = .0083;  //Check spec sheet for this value
float rotationThreshold = 1;   //Minimum deg/sec to keep track of to help fight gyro drifting

float xcurrentAngle = 0;        //Keep track of the current x angle
float ycurrentAngle = 0;        //Keep track of the current y angle

//debug variables go below here
long interval=1000;
long current=0;
long previous=0;


void setup() 
{ 
  Serial.begin(9600);
  //xservo.attach(9);  // attaches the servo on pin 9 to the X servo object
  //yservo.attach(10);  // attaches the servo on pin 10 to the Y servo object
  //pinMode(13,OUTPUT);
} 
 
 
void loop() 
{ 
  //This line converts the 0-1023 signal to 0-5V for both gyros
  float xgyroRate = (analogRead(xgyroPin) * gyroVoltage) / 1023;
  float ygyroRate = (analogRead(ygyroPin) * gyroVoltage) / 1023;
  
  //following computation: (find the voltage offset from the null position) / gyro's sensitivity  
  xgyroRate = (xgyroRate - gyroZeroVoltage) / gyroSensitivity;
  ygyroRate = (ygyroRate - gyroZeroVoltage) / gyroSensitivity;
  
  //Ignore the gyro if our angular velocity does not meet our threshold
  if (xgyroRate >= rotationThreshold || xgyroRate <= -rotationThreshold) {
    //Divide the value by 100 since we are running in a 10ms loop (1000ms/10ms)
    xgyroRate /= 100;
    xcurrentAngle += xgyroRate;
  }
  
  //do the same thing for y
  if (ygyroRate >= rotationThreshold || ygyroRate <= -rotationThreshold) {
    ygyroRate /= 100;
    ycurrentAngle += ygyroRate;
  }
  if (abs(xcurrentAngle) <= xservoNull){
    //add the x tilt angles to the servo null angle to keep the fins perpendicular to gravity
    xservo.write(xservoNull-xcurrentAngle);
  }
  if ((ycurrentAngle) <= yservoNull){
    //add the y tilt angles to the servo null angle to keep the fins perpendicular to gravity
    yservo.write(yservoNull-ycurrentAngle);  
  }
  unsigned long current=millis();
  if (current - previous >= interval){
    Serial.println("X angle:");
    Serial.println(xgyroRate);
    Serial.println("Y angle:");
    Serial.println(ygyroRate);
    previous = current;
  }
  delay(10);
} 
