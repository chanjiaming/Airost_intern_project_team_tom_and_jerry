#include <SoftwareSerial.h> 
#include <Servo.h>
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENA 11
#define ENB 5
#define bluetoothTx 2 
#define bluetoothRx 4
Servo servo1;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
 


void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  servo1.attach(3);
  //set up the baud rate for bluetooth communication between handphone and hc-06
  Serial.begin(9600);
  bluetooth.begin(9600);
 
  //Start with motors off
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
  //Set a default speed for both sides of dc motors
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}
 
void loop() { 
  //Because we need to control 3 servos in the another app, the signal with 1-byte size is not enough to transmit the data, so 2 bytes is used.
  //The bluetooth signal emitted by handphone via this app is also 2 bytes for convenience. 
  //Only if the signal received by hc-06 is more than 2 bytes, than the following statements will be executed.
  if(bluetooth.available()>=2 ){ 
    int signal = bluetooth.read();   //input the signal
    if (signal == 0){
    // Set motors STOP
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW); //stop
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, LOW); //stop
    Serial.println("STOP"); //convenient for me to monitor whether the signal transmission is working
    delay (10);
    }  

    if (signal == 1){
    // Set motors forward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH); //LEFT FORWARD
    digitalWrite(IN3, HIGH); 
    digitalWrite(IN4, LOW); //RIGHT FORWARD
    Serial.println("FORWARD");
    delay (10); 
    } 

    if (signal == 2){
    // Set motors reverse
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW); //LEFT BACKWARD
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, HIGH); //RIGHT BACKWARD
    Serial.println("BACKWARD");
    delay (10);
    }


    if (signal == 3){
    //TURN TO LEFT
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH); //RIGHT BACKWARD
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, HIGH); //LEFT FORWARD
    Serial.println("TURN LEFT");
    delay (10);
    }

    if (signal == 4){
    //TURN TO RIGHT
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW); //RIGHT FORWARD
    digitalWrite(IN3, HIGH); 
    digitalWrite(IN4, LOW); //LEFT BACKWARD
    Serial.println("TURN RIGHT");
    delay (10);
    }


    //for adjusting the speed of dc motor
    if (signal ==5){
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
    Serial.println("low speed");
    }


    if (signal ==6){
    analogWrite(ENA, 250);
    analogWrite(ENB, 250);
    Serial.println("high speed");
    }

    if (signal ==7){
    analogWrite(ENA, 200);
    analogWrite(ENB, 200);
    Serial.println("moderate speed");
    }


    //for controlling the servo1. This is because we found that a single arduino couldn't be linked
    //to too many servos. So we moved servo1 (for base axis) to this arduino, while the another arduino 
    //is connected to other 3 servos. This approach could reduce servos jittering problem.
    
    if (signal ==8){
      Serial.println("Servo 1 ON");
      servo1.write(0);
    }

    if (signal ==9){
      Serial.println("Servo 1 ON");
      servo1.write(45);
    }
    if (signal ==10){
      Serial.println("Servo 1 ON");
      servo1.write(90);
    }
    if (signal ==11){
      Serial.println("Servo 1 ON");    //the center position for the robotic arm
      servo1.write(135);
    }
    if (signal ==12){
      Serial.println("Servo 1 ON");
      servo1.write(180);
    }
    if (signal ==13){
      Serial.println("Servo 1 ON");
      servo1.write(100);
    }
    if (signal ==14){
      Serial.println("Servo 1 ON");
      servo1.write(80);
    }
  }
}
