# **RGB LED**

```
How to use Struct for RGB LEDs
Written by RHIBA Zakaria
````

*The but of this project is to switch two RGB LEDs color in the same time red to green to blue, to do that we gonna Use a struct to define a RGB LED*

For exemple if we want to turn the RGB LED with the red color we have to send a low value to the green and blue pins bsides red pin.

## **STRUCT**

A structure type is a user-defined composite type. It is composed of fields or members that can have different types. In C++, a structure is the same as a class except that its members are public by default.

It enables the programmer to create a variable that structures a selected set of data.

For instance, it might be useful to have a struct that represents a RGB value. Being a RGB variable always consists of three other variables a struct is the correct datatype.

### **Synatx**

#### Declaration

```C++
    struct RGB {
        int red;
        int green;
        int blue;
  }; 
```

#### Creating 

We're initialize each color with it's pin

```C++
RGB led = {9,10,11};
```

## **Initialize :**

To Switch between the color we gonna write three function each one turn on a color, so in the initialize part we gonna just write this three function : 

- Turn on red color : 

```C++
void red(RGB led){
    digitalWrite(led.red,HIGH);
    digitalWrite(led.green,LOW);
    digitalWrite(led.blue,LOW);
  }
```

- Turn on Green Color : 

```C++
void green(RGB led){
    digitalWrite(led.green,HIGH);
    digitalWrite(led.red,LOW);
    digitalWrite(led.blue,LOW);
  }
```

- Turn on Blue Color : 

```C++
void blue(RGB led){
    digitalWrite(led.red,LOW);
    digitalWrite(led.green,LOW);
    digitalWrite(led.blue,HIGH);
  }
```

## **Setup Function :**

Initialize the LED pins as an Output

In the setup function I use the same technique by written a function do the setup for me just by given it the RGB led object as a parameter

> In this way we optimize the code so much better in case if we have multiple RGB LEDs.

#### Funtion Setup led :
```C++
void SetupLed(RGB led){
    pinMode(led.red,OUTPUT);
    pinMode(led.green,OUTPUT);
    pinMode(led.blue,OUTPUT);
  }
```
#### Setup Funtion : 

```C++
void setup() {
  SetupLed(led);
}
```

## **Loop Function :**

In the loop function we just gonna call each color to turn on for 1 second : 

```C++
void loop() {
  red(led);
  delay(1000);
  green(led);
  delay(1000);
  blue(led);
  delay(1000);
}
```

## **The Complet Code :** 

```C++
struct RGB {
    int red;
    int green;
    int blue;
  }; 

RGB led = {9,10,11};

void SetupLed(RGB led){
    pinMode(led.red,OUTPUT);
    pinMode(led.green,OUTPUT);
    pinMode(led.blue,OUTPUT);
  }

void red(RGB led){
    digitalWrite(led.red,HIGH);
    digitalWrite(led.green,LOW);
    digitalWrite(led.blue,LOW);
  }

void green(RGB led){
    digitalWrite(led.green,HIGH);
    digitalWrite(led.red,LOW);
    digitalWrite(led.blue,LOW);
  }

void blue(RGB led){
    digitalWrite(led.red,LOW);
    digitalWrite(led.green,LOW);
    digitalWrite(led.blue,HIGH);
  }
  

void setup() {
  // put your setup code here, to run once:
  SetupLed(led);
}

void loop() {
  // put your main code here, to run repeatedly:
  red(led);
  delay(1000);
  green(led);
  delay(1000);
  blue(led);
  delay(1000);
}

```

## **The Complet Code for using Two RGB LEDs :**

```C++
struct RGB {
    int red;
    int green;
    int blue;
  }; 

RGB led1 = {9,10,11};
RGB led2 = {5,6,7};

void SetupLed(RGB led){
    pinMode(led.red,OUTPUT);
    pinMode(led.green,OUTPUT);
    pinMode(led.blue,OUTPUT);
  }

void red(RGB led){
    digitalWrite(led.red,HIGH);
    digitalWrite(led.green,LOW);
    digitalWrite(led.blue,LOW);
  }

void green(RGB led){
    digitalWrite(led.green,HIGH);
    digitalWrite(led.red,LOW);
    digitalWrite(led.blue,LOW);
  }

void blue(RGB led){
    digitalWrite(led.red,LOW);
    digitalWrite(led.green,LOW);
    digitalWrite(led.blue,HIGH);
  }
  

void setup() {
  // put your setup code here, to run once:
  SetupLed(led1);
  SetupLed(led2);
}

void loop() {
  // put your main code here, to run repeatedly:
  red(led1);
  red(led2);
  delay(1000);
  green(led1);
  green(led2);
  delay(1000);
  blue(led1);
  blue(led2);
  delay(1000);
}
```
___

If you have any Question or Collaboration feel free to Visit my portfolio and contact me 

> you can visit my protfolio over here :
[Rhiba Zakaria porfolio](https://zak-rhiba.codes)