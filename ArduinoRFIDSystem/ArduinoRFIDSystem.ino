#include <RFID.h>

/*
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS/SDA: Pin 10
* RST: Pin 9
*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);


int led = 7;
int led2 = 6;
// int power = 8; 
int serNum[5];

// the accepted UID
int cards[][5] = {
  {43,248,26,219,18}
};

// changes depending on UID status
bool access = false;

void setup(){

    Serial.begin(9600);
    SPI.begin();
    rfid.init();

    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
   
}

void loop(){

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
       // It worked! :)
       if(access){
        // add in the code to unlock the charging station
           Serial.println("Welcome!");
           digitalWrite(led2, HIGH);
           delay(500);
           digitalWrite(led2, LOW); 
           delay(500);
           digitalWrite(led2, HIGH);
           delay(500);
           
           digitalWrite(led2, LOW);
        // It didn't work :(   
      } else {
           Serial.println("Not allowed!"); 
           digitalWrite(led, HIGH);
           delay(500);
           digitalWrite(led, LOW); 
           delay(500);
           digitalWrite(led, HIGH);
           delay(500);
           digitalWrite(led, LOW);         
       }        
    }
    
    
    
    rfid.halt();

}


