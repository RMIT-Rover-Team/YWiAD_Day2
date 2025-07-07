/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Here are a few definitions of functions available on the rover
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/ 
void carStartup();      // Sets up the rover on startup

void carStop();         // Stop the rover moving
void carGoForward();    // Move Forward
void carGoBack();       // Move Backward
void carTurnRight();    // Turn Right
void carTurnLeft();     // Turn Left

float carGetDistance(); // Get distance of ultrasonic sensor, returns floating point value
void carSetServo(float angle); // Set the servo to a specific angle between +-90 degrees
/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/


// This is the setup function of the program, it runs only once
void setup() {
  //Set up the rover
  carStartup(); //Here we call one of the above functions to 

  //Face the servo forward
  carSetServo(0.0);

  // put your setup code here, to run once:
  // If there are any initial actions you want the rover to do, they go here

  //[TODO] - Edit here
}



// This is the main loop of the rover, it runs everything inside forever
void loop() {
  // put your main code here, to run repeatedly:
  // [TODO] - Edit here

  // Here is some example code below
  // Feel free to delete or edit as you see fit
  carGoForward();
  delay(2000); //Milliseconds

  carGoBackward();
  delay(2000); //Milliseconds

  carTurnLeft();
  delay(2000); //Milliseconds

  carTurnRight();
  delay(2000); //Milliseconds

  // Read the ultrasonic distance sensor and print the result
  float mySample = carGetDistance(); //Read the distance and put it in the variable mySample
  
  // Display it
  if (mySample == 0.0){
    Serial.println("No Value");
  }
  else {
    Serial.println("Distance: " + String(mySample));
  }
  
}























/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
This section contains the functions that let the rover move
Please do not edit past here
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/


#include <Servo.h> 

#define speedPin_M1     5     //M1 Speed Control
#define speedPin_M2     6     //M2 Speed Control
#define directionPin_M1 4     //M1 Direction Control
#define directionPin_M2 7     //M1 Direction Control

#define URPWM  3    // PWM Output 0－25000US，Every 50US represent 1cm
#define URTRIG 10   // PWM trigger pin

#define ServoPin 9  // The control pin of the servo

Servo myservo;

void carStartup(){
  Serial.begin(9600);

  //Set up the wheels
  pinMode(speedPin_M1, OUTPUT);
  pinMode(speedPin_M2, OUTPUT);
  pinMode(directionPin_M1, OUTPUT);
  pinMode(directionPin_M2, OUTPUT);

  carStop();

  pinMode(URTRIG,OUTPUT);     // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);  // Set to HIGH 
  pinMode(URPWM, INPUT);      // Sending Enable PWM mode command

  myservo.attach(ServoPin);
}


void carStop(){
  digitalWrite(speedPin_M2,0); 
  digitalWrite(directionPin_M1,LOW);    
  digitalWrite(speedPin_M1,0);   
  digitalWrite(directionPin_M2,LOW);   
}

void carGoForward(){
  analogWrite (speedPin_M2,255);
  digitalWrite(directionPin_M1,LOW);    
  analogWrite (speedPin_M1,255);    
  digitalWrite(directionPin_M2,HIGH);
}

void carGoBackward(){
  analogWrite (speedPin_M2,255);
  digitalWrite(directionPin_M1,HIGH);    
  analogWrite (speedPin_M1,255);    
  digitalWrite(directionPin_M2,LOW);
}

void carTurnRight(){
  analogWrite (speedPin_M2,255);
  digitalWrite(directionPin_M1,HIGH);    
  analogWrite (speedPin_M1,255);    
  digitalWrite(directionPin_M2,HIGH);
}


void carTurnLeft(){
  analogWrite (speedPin_M2,255);
  digitalWrite(directionPin_M1,LOW);    
  analogWrite (speedPin_M1,255);    
  digitalWrite(directionPin_M2,LOW);
}



int MeasureDistance(){  // a low pull on pin COMP/TRIG  triggering a sensor reading
    digitalWrite(URTRIG, LOW);
    digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses    
    unsigned long distance=pulseIn(URPWM,LOW);    
    if(distance==50000){              // the reading is invalid.
      Serial.print("Invalid");    
    }else{
      distance=distance/50;           // every 50us low level stands for 1cm
    }
    return distance;
}

float carGetDistance(){
  return MeasureDistance();
}


void carSetServo(float angle){
  if (angle < -90){
    angle = -90;
  }
  if (angle > 90){
    angle = 90;
  }
  myservo.write((int)(((angle+90)/180)*255));
}

