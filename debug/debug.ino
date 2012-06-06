int xgyro = 6;              //X Gyro is connected to analog pin 6
int ygyro = 7;              //Y Gyro is connected to analog pin 7
int xval = 0;
int yval = 0;
int maxx = 0;
int minx = 999;

float sens = .0083;
float sensq = 0;
float xzero = 0;
float yzero = 0;
float readx = 0;
float ready = 0;
float xrate = 0;
float yrate = 0;
float then = 0;
float now = 0;
float xangle = 0;
float yangle = 0;
int yes =0;
int counter=0;

void setup() 
{ 
  Serial.begin(9600);
  sensq = 2.573;
} 
 
 
void loop() 
{ 
  xval = analogRead(xgyro);
  yval = analogRead(ygyro);
  
  xrate = (xval-xzero)/sensq;
  yrate = (yval-yzero)/sensq;
  
  xangle=xangle + xrate*(millis()-then)/1000.0;
  
  then = millis();
  
  if (counter==0){Serial.println(xval);counter=0;}
  else {counter++;}
  
  delay(5);
}

/*
1- find average, aka null value
2- deviations from that 
