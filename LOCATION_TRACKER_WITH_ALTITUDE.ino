#include <TinyGPS++.h>    //--------------------------------------------------------------------------------------------------for extracting GPS DATA
#include <HardwareSerial.h>   //--------------------------------------------------------------------------FOR COMMUNICATING WITH SERIALPORTS OF ESP32

static const int GPSBaud = 9600;

TinyGPSPlus gps;//----------------------------------------------------------------------------------FROM TINYGPS++ library for preparing data from GPS
HardwareSerial SerialGPS(1); //-------------------------------------------------------------------------- Uses Serial1 (TX: GPIO2, RX: GPIO4) on ESP32

void setup() {  //----------------------------------------------------Initializes Serial1 for communication with the GPS module (RX: GPIO4, TX: GPIO2).
  Serial.begin(9600);
  SerialGPS.begin(GPSBaud, SERIAL_8N1, 4, 2); //--------------------------------------------------------------------------------- RX: GPIO4, TX: GPIO2

  while (!Serial) {
    ; //-------------------------------------------------------------------------------------------------------------- Wait for serial port to connect
  }
  
  //------------------------------------------------------------------------------------------------------------- Initialize SIM800L module (if needed)
  Serial.println("Initializing SIM800L...");
  Serial2.begin(9600, SERIAL_8N1, 27, 26); // --------------------------------------------------------------Replace with your SIM800L's RX and TX pins
}

void loop() {//-------------------------------------------------------------------------------------------checks and waits for data from the GPS module
  while (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read())) {
      displayInfo();
    }

    if (millis() > 5000 && gps.charsProcessed() < 10) {   // ------------------------------------------------------if not received for more than 5 sec
      Serial.println(F("No GPS detected: check wiring."));
      while (true);
    }
  }

 
}

void displayInfo() {//--------------------------------------------------------------------------------------------displays the data if in valid format
  Serial.print(F("Location: "));
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date "));
  if (gps.date.isValid()) {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Time "));
  if (gps.time.isValid()) {
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    Serial.print(gps.time.centisecond());
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Altitude "));
  if (gps.altitude.isValid()) {
    Serial.print(gps.altitude.meters());
    Serial.print(F(" meters"));
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
