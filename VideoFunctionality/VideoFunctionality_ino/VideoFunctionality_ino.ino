#include <Servo.h>
#include <NewPing.h>
#include <RFID.h>
#include <SPI.h>

#define TRIGGER_PIN  1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN    2  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define SS_PIN 10  
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);

int led = 7;
int led2 = 8;
// int power = 8; 
int serNum[5];

// the accepted UID
int cards[][5] = {
  {43,248,26,219,18}
};

// changes depending on UID status
bool access = false;

NewPing sonar1(TRIGGER_PIN, ECHO_PIN); // NewPing setup of pins and maximum distance.

Servo serv1;
Servo serv2;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  
  serv1.attach(9); //Lid servos
  serv2.attach(10);

  pinMode(3, OUTPUT); //Flashing LEDS
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(led2, LOW);
  
  serv1.write(0);
  serv2.write(180);
  delay(3000); //Wait 3 seconds before running loop
}

void loop() {
  Serial.println("\n");

  if(rfid.isCard()){

    if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
            
            for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }
           
        }
        
    // may have to adjust the 200 baseline
    // also may need to adjust 3
    if(sonar1.ping_cm() <= 10 && access){ 

       Serial.println("Welcome!");
       digitalWrite(led2, HIGH);
       delay(500);
       digitalWrite(led2, LOW); 
       delay(500);
       digitalWrite(led2, HIGH);
       delay(500);
       digitalWrite(led2, LOW);
      
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

       Serial.println("Not allowed!"); 
       digitalWrite(led, HIGH);
       delay(500);
       digitalWrite(led, LOW); 
       delay(500);
       digitalWrite(led, HIGH);
       delay(500);
       digitalWrite(led, LOW);
      
      //Keep the lid up while waiting
      serv1.write(0);
      serv2.write(180);
  
      //Blink the lights while waiting for landing
      lightsOn();
      delay(1000);
      lightsOff();
    }
  }

  //Check for landing every second and only every second
  delay(1000);
  rfid.halt();
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

