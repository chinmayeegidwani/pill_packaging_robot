/* Arduino_UART_PIC
 *  
 * Author: Tyler Gamvrelis
 * Date: August 29, 2017 4:51 PM
 * Description: Sample program for arbitrary information exchange between
 *              the main PIC and the Arduino Nano
 * Preconditions:
 *   1.  Main PIC uses hardware UART
 *   2.  Arduino Nano uses software UART
 *   3.  The Co-processor is not driving lines on the UART bus (e.g. the UART jumpers are removed
 *   4.  The character LCD is in an Arduino Nano socket
 *   5.  PIC-Arduino link switches are enabled (ON) for D0 of the Arduino (the RX pin).
 *       However, make sure that neither of D0 and D1 are enabled (ON) while programming the Arduino Nano
 */

#include <SoftwareSerial.h>
#include <Servo.h>          

Servo LeadServo;  //servo for lead screw 
Servo myservo, myservo1, myservo2, myservo3; //servos for apertures 
Servo panel; //servo for turning panel 


static char arr[2]; // To hold received characters
const byte rxPin = 1;
const byte txPin = 0;
const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;



 
#define LEDPIN 13
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin  6: Teensy++ 2.0 has the LED on pin 6
  // Pin 13: Teensy 3.0 has the LED on pin 13
 
#define SENSORPIN 10
 
// variables will change:
int sensorState = 0, lastState=0;         // variable for reading the pushbutton status
 


SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


char curr = ' ';
char prev = ' ';

void setup() {
  /* Configure pin modes for tx and rx. */
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  /* Open software serial port with baud rate = 9600. */
  mySerial.begin(9600);
  
  // initialize the LED pin as an output:
  pinMode(LEDPIN, OUTPUT);      
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN, INPUT);     
  digitalWrite(SENSORPIN, HIGH); // turn on the pullup
  

  
  
  
  
}

void loop() {
  while(mySerial.available() < 1){ 
    
    
    continue; }
  arr[0] = mySerial.read();
  //Serial.print(arr[0]);
  

  
  
  if(arr[0] == 'Z'){ //start program - lead screw
    leadScrew();
    delay(500);
    //get mode from color sensor and send back to PIC 
    //if(colorsensor){
    digitalWrite(0, HIGH); //send a appropriate signal back to pic 
  }

  

  int count = 0;
  

  while(count < 15 && arr[0] != 'Z'){
      if(count%2 == 0){ //turns panel servo for morning/afternoon
        Panel('M');
      } else{
        Panel('A');
      }
    
      
      //dispense appropriate pills - aperture 
      if(arr[0] == 'B'){
        dispenseR(1);
      } else if(arr[0] == 'C'){
        dispenseR(2);
      } else if(arr[0] == 'D'){
        dispenseF(1);
      } else if(arr[0] == 'E'){
        dispenseF(2);
      } else if(arr[0] == 'F'){
        dispenseL(1);
      } else if(arr[0] == 'G'){
        dispenseL(2);
      } else if(arr[0] == 'H'){
        dispenseL(3);
      } 
      delay(1000);
            
      
      count++; 
      
      if(count%2 == 0){ //when morning and afternoon pills done processing, move box
        leadScrew();
      }

      if(arr[0] == 'e'){
        endProgram();
      }

      digitalWrite(0, HIGH); //send signal back to PIC that processing is done
} 
  
}

void endProgram(){
  myservo.write(50);
  delay(500);
  myservo.detach();
  delay(500);

  
  
}


void leadScrew(){
  LeadServo.attach(3); 
  LeadServo.write(180 );                  // sets the servo position according to the scaled value 
  delay(2000);                           // waits for the servo to get there 
  LeadServo.detach();                // sets the servo position according to the scaled value 

  
}

void Panel(char AM){
  int turntime = 1000;
  if(AM == 'A'){
    panel.attach(9);
    panel.write(0);
  
    delay(500);
    panel.detach();
  
  } else if(AM == 'M'){
    delay(500);
    panel.attach(9);
    panel.write(180);

    delay(500);
    panel.detach();
  }
}


void dispenseR(int num){
  int delaytime = 5000;
  for(int i =0; i<num; i++){
        myservo.attach(8); //top servo open
        delay(15);
        myservo.write(115);
        delay(125);
        myservo.detach(); //servo stop
        delay(700);
      
      
        while(digitalRead(SENSORPIN) == LOW){ //polling for switch
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
      
      
        myservo1.attach(9); //bottom servo open
        delay(15);
        myservo1.write(55);  
        delay(175);
        myservo1.detach(); //servo stop
        delay(700);
        myservo1.attach(9);
        delay(15);
        myservo1.write(115); //servo close
        delay(250); 
        myservo1.detach();
        delay(700); 
        }
}

void dispenseF(int num){
  int delaytime = 5000;
  for(int i =0; i<num; i++){
          myservo2.attach(8); //top servo open
          delay(15);
          myservo2.write(115);
          delay(125);
          myservo2.detach(); //servo stop
          delay(700);
        
        
          while(digitalRead(SENSORPIN) == HIGH){ //polling for switch
            delay(100); //loop
            digitalWrite(13, LOW);
          }
        
        
          
          digitalWrite(13, HIGH);
          myservo2.attach(8); 
          delay(15);
          myservo2.write(55); //servo close
          delay(300); 
          myservo2.detach();
          delay(700); 
        
        
          myservo3.attach(9); //bottom servo open
          delay(15);
          myservo3.write(55);  
          delay(175);
          myservo3.detach(); //servo stop
          delay(700);
          myservo3.attach(9);
          delay(15);
          myservo3.write(115); //servo close
          delay(250); 
          myservo3.detach();
          delay(700); 
  }
}

void dispenseL(int num){
  int delaytime = 5000;
  for(int i =0; i<num; i++){
    //solenoid
  }
}





