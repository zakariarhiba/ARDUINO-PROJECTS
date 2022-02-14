# **Mesure Temperature using DHT11 Sensor**

```
Example testing mesure temperature using DHT11 sensor
Written by RHIBA Zakaria
````

To use DHT11 Sensor is requires the following Arduino libraries:
- DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
- Adafruit Unified Sensors Lib : https://github.com/adafruit/Adafruit_Sensor


*In the following programs, the temperature and humidity values on the serial port will be displayed every 2 seconds. It is therefore necessary to open the serial terminal on the Arduino interface after having "uploaded" the program.*

## **Intialize Sensor :**

___

DHT11 has 3 pins, one for Vcc, second for GND, and the last one is a digital pin for data transfer we chosse pin 5 : 

```C
#include "DHT.h"

#define DHTPIN 5 // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11  // DHT Type 11 || 21 || 21
```

Initialize DHT sensor with the data pin and its type : 

```C
DHT dht(DHTPIN, DHTTYPE);
```

## **Setup Function :**

___

> To understand there a complet road to understand it in the reporistry feel free to read it.

```C
void setup() {
  Serial.begin(9600); // Initialize Serial Communication
  dht.begin();  // Run DHT11 mesurement
}
```

# **Loop Function :**

___

Read temperature as Celsius (the default) :

```C
float t = dht.readTemperature();
```

Check if dht success to mesure, if not we print in serial that it failed :

```C
if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
```

Print in Serial the mesure value : 

```C
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C  \n ");
```

## **The Complet Code :**

```C
// Example testing dht11 to mesure temperature 
// Written by RHIBA Zakaria
#include "DHT.h"

#define DHTPIN 5 
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin(); 
}

void loop() {

  float t = dht.readTemperature();

   if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C  \n ");

  delay(2000);   // Mesure each 2 second
}
```
___

If you have any Question or Collaboration feel free to Visit my portfolio and contact me 

> you can visit my protfolio over here :
[Rhiba Zakaria porfolio](https://zak-rhiba.codes)