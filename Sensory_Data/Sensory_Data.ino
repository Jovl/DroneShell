// dewPoint function NOAA
// reference (1) : http://wahiduddin.net/calc/density_algorithms.htm
// reference (2) : http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//
double dewPoint(double celsius, double humidity)
{
  // (1) Saturation Vapor Pressure = ESGG(T)
  double RATIO = 373.15 / (273.15 + celsius);
  double RHS = -7.90298 * (RATIO - 1);
  RHS += 5.02808 * log10(RATIO);
  RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1) ;
  RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
  RHS += log10(1013.246);

        // factor -3 is to adjust units - Vapor Pressure SVP * humidity
  double VP = pow(10, RHS - 3) * humidity;

        // (2) DEWPOINT = F(Vapor Pressure)
  double T = log(VP/0.61078);   // temp var
  return (241.88 * T) / (17.558 - T);
}

//Celsius to Fahrenheit
double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

// For the temperature sensor
#include <dht11.h>
#include <NewPing.h>
dht11 DHT11;

#define DHT11PIN 5
#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN    12  // Arduino pin tied to echo pin on the ultrasonic sensor.

NewPing sonar1(TRIGGER_PIN, ECHO_PIN); // NewPing setup of pins and maximum distance.

// For the Rain sensor
const int read = A0; //Sensor AO pin to Arduino pin A0
int value;          //Variable to store the incomming data

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
}

void loop() {
  Serial.println("\n");

  // may have to adjust the 200 baseline
  // also may need to adjust 3
  if(value >= 200 || sonar1.ping_cm() <= 3){
    // TODO: HOIST THE SAILS, MATEY
    Serial.println("Raining");
  } else {
    // TODO: LOWER THE SAILS, SAVOY?
  }
  
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK: 
    Serial.println("OK"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.println("Checksum error"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.println("Time out error"); 
    break;
    default: 
    Serial.println("Unknown error"); 
    break;
  }

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (°C): ");
  Serial.println((float)DHT11.temperature, 2);

  Serial.print("Temperature (°F): ");
  Serial.println(Fahrenheit(DHT11.temperature), 2);

  Serial.print("Dew Point (°C): ");
  Serial.println(dewPoint(DHT11.temperature, DHT11.humidity));

  delay(2500);
}
