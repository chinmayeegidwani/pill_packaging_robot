#include <Servo.h>       

Servo LeadServo;


void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  LeadServo.attach(3); 
  LeadServo.write(180 );                  // sets the servo position according to the scaled value 
  delay(2000);                           // waits for the servo to get there 
  LeadServo.detach();    
}
