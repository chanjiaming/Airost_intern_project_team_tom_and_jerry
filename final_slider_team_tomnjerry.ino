
#include <SoftwareSerial.h> 
#include <Servo.h> 
Servo MYSERVO2, MYSERVO3, MYSERVO4; 

int bluetoothTx = 10; // bluetooth tx to 10 pin
int bluetoothRx = 11; // bluetooth rx to 11 pin


SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  MYSERVO2.attach(6);
  MYSERVO3.attach(7);
  MYSERVO4.attach(9);

  Serial.begin(9600);

  bluetooth.begin(9600);
}

void loop()
{
  //Because we need to control 3 servos in the another app, the signal with 1-byte size is not enough to transmit the data, so 2 bytes is used.
  if(bluetooth.available()>= 2 )
  {
    unsigned int servopos = bluetooth.read();
    Serial.println("servopos is");
    Serial.println(servopos);
    unsigned int servopos1 = bluetooth.read();
    Serial.println("servopos1 is");
    Serial.println(servopos1);
    unsigned int realservo = (servopos1 *256) + servopos;
    Serial.println(realservo);

      if (realservo >= 3000 && realservo <=3090) {
        int servo2 = realservo;
        servo2 = map(servo2, 3000, 3090, 0, 90);
        MYSERVO2.write(servo2);
        Serial.println("Servo 2 ON");
        Serial.println(servo2);


      }
      if (realservo >= 5090 && realservo <=5180) {
        int servo3 = realservo;
        servo3 = map(servo3, 5090, 5180, 90, 180);
        MYSERVO3.write(servo3);
        Serial.println("Servo 3 ON");
        Serial.println(servo3);


      }
      if (realservo >= 7000 && realservo <=7045) {
        int servo4 = realservo;
        servo4 = map(servo4, 7000, 7045, 0, 45);
        MYSERVO4.write(servo4);
        Serial.println("Servo 4 ON");
        Serial.println(servo4);

      }
  }
}
