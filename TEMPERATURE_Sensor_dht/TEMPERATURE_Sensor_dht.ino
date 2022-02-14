// Example testing dht11 to mesure temperature 
// Written by RHIBA Zakaria

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 5 // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11  // DHT Type 11 || 21 || 21


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin(); 
}

void loop() {
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

   if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C  \n ");


  delay(2000);  
}
