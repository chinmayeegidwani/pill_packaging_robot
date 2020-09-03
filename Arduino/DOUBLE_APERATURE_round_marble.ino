#include <Servo.h>
Servo myservo, myservo2, myservo3, myservo4;  // create servo object to control a servo

#define LEDPIN 13
#define SENSORPIN 2

void setup() {
  //myservo.attach(9);
  // attaches the servo on pin 9 to the servo object
  pinMode(LEDPIN, OUTPUT);
  pinMode(SENSORPIN, INPUT);
}

void loop() {
  myservo.attach(8); //top servo open
  delay(15);
  myservo.write(115);
  delay(125);
  myservo.detach(); //servo stop
  delay(700);


  while(digitalRead(SENSORPIN) == HIGH){ //polling for switch
    delay(100); //loop
    digitalWrite(13, LOW);
  }


  
  digitalWrite(13, HIGH);
  myservo.attach(8); 
  delay(15);
  myservo.write(55); //servo close
  delay(300); 
  myservo.detach();
  delay(700); 


  myservo2.attach(9); //bottom servo open
  delay(15);
  myservo2.write(55);  
  delay(175);
  myservo2.detach(); //servo stop
  delay(700);
  myservo2.attach(9);
  delay(15);
  myservo2.write(115); //servo close
  delay(250); 
  myservo2.detach();
  delay(700); 
  
  
  }
