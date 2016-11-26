#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN  1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN    2  // Arduino pin tied to echo pin on the ultrasonic sensor.

NewPing sonar1(TRIGGER_PIN, ECHO_PIN); // NewPing setup of pins and maximum distance.

Servo serv1;
Servo serv2;

void setup() {
  Serial.begin(9600);
  
  serv1.attach(9); //Lid servos
  serv2.attach(10);

  pinMode(3, OUTPUT); //Flashing LEDS
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  serv1.write(0);
  serv2.write(180);
  delay(3000); //Wait 3 seconds before running loop
}

void loop() {
  Serial.println("\n");

  // may have to adjust the 200 baseline
  // also may need to adjust 3
  if(sonar1.ping_cm() <= 10){ //TODO: ADD RFID CHECKING HERE AND ONLY CLOSE IF THERE IS A DRONE AND IT IS VALID
    
    // TODO: HOIST THE SAILS, MATEY
    Serial.println("Closing up!");
    
    //Wait to finish landing
    delay(2000);

    //Shut the lid at the fastest speed possible
    serv1.write(180);
    serv2.write(0);

    //Turn off the lights
    lightsOff();
    
    //Delay for 20 seconds for demo ONLY, actual product would have a remote release functionality
    delay(20000);
    serv1.write(0);
    serv2.write(180);
  
  } else {
    // TODO: LOWER THE SAILS, SAVOY?

    //Keep the lid up while waiting
    serv1.write(0);
    serv2.write(180);

    //Blink the lights while waiting for landing
    lightsOn();
    delay(1000);
    lightsOff();
  }

  //Check for landing every second and only every second
  delay(1000);
}

void lightsOn(){ //Turns on all LEDS
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
}


void lightsOff(){ //Turns off all LEDs
  digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(6, LOW);   // turn the LED on (HIGH is the voltage level)
}

