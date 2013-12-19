#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
Adafruit_GPS GPS(&Serial1);

const int buttonPin = A9;

int buttonState = 0;

#define GPSECHO false

boolean usingInterrupt = false;

void setup()  
{
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");

  GPS.begin(9600);
  
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  delay(1000);

  Serial1.println(PMTK_Q_RELEASE);
  
  pinMode(buttonPin, INPUT_PULLUP);
}


uint32_t timer = millis();
void loop()
{
  buttonState = digitalRead(buttonPin);
  
  if(buttonState == LOW)
  {
  
    char c = GPS.read();
  
  if (GPSECHO)
      if (c) Serial.print(c);
  
  if (GPS.newNMEAreceived()) {
   
    Serial.println(GPS.lastNMEA());
  
    if (!GPS.parse(GPS.lastNMEA()))
      return; 
  }
  
  if (timer > millis())  timer = millis();

  if (millis() - timer > 2000) { 
    timer = millis();
    
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality); 
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", "); 
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
  }
  }
}
