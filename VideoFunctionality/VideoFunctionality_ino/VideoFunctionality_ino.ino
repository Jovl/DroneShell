#include <Servo.h>

#include <NewPing.h>


#define TRIGGER_PIN  1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN    2  // Arduino pin tied to echo pin on the ultrasonic sensor.

NewPing sonar1(TRIGGER_PIN, ECHO_PIN); // NewPing setup of pins and maximum distance.

Servo serv1;
Servo serv2;


void setup() {
  Serial.begin(9600);
  
  serv1.attach(9);
  serv2.attach(10);

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  serv1.write(0);
  serv2.write(180);
  delay(3000);
}

void loop() {
  Serial.println("\n");

  // may have to adjust the 200 baseline
  // also may need to adjust 3
  if(sonar1.ping_cm() <= 10){
    
    
    // TODO: HOIST THE SAILS, MATEY
    Serial.println("closing up");
    
    //wait to finish landing
    delay(2000);
    
    serv1.write(180);
    serv2.write(0);
    lightsOff();
    delay(20000);

     serv1.write(0);
     serv2.write(180);

    
    
  } else {
    // TODO: LOWER THE SAILS, SAVOY?
    serv1.write(0);
    serv2.write(180);
    lightsOn();
    delay(1000);
    lightsOff();
  }
  delay(1000);
}

void lightsOn(){
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
}


void lightsOff(){
  digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(6, LOW);   // turn the LED on (HIGH is the voltage level)
}

