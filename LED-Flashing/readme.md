# **Flashing LED**

*This is a simple Project to turn on a Led which is connected to any digital pin that we want, for our code we're using pin 8.*

## **To Change the led pin :**

___

They are two ways to initialize an Input / Output : 

* First using it as a intger variable, we can name it any name but always name it on what is it (led,motor,temperature sensor... ) :

```C
int led = 8;
```

* We can use also use a ticket, tickets a better way to minimize the memory complexity of the code, because they are translate in the compiling process instead of using a variable he takes an memory based on its type :

```C
#define LED 8
```

## **Setup Function :**

___

We initialize the led as an Output, you chosse between an Output or Input based on if the arduino is gonna send a signal or read a signal : 

```C
void setup() {
  pinMode(led,OUTPUT); //Set led as an Output
}
```

## **Loop Function**

___

to flash a red we have only to turn the led on for a while and then turn it off due to we gonna write that inside the loop function led's gonna keep flashing : 

```C
void loop() {
  digitalWrite(led,HIGH); // Turn led On 
  delay(1000);   // Set a timer for 1000ms
  digitalWrite(led,LOW); // Turn led Off
  delay(1000);   // Set a timer for 1000ms
}
```

## **The Complet Code :**

```C
// initialize Input/Output
int led = 8;
// Setup function
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT); //Set led as an Output
}
// loop function
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led,HIGH); // Turn led On 
  delay(1000);   // Set a timer for 1000ms
  digitalWrite(led,LOW); // Turn led Off
  delay(1000);   // Set a timer for 1000ms
}
```

___

If you have any Question or Collaboration feel free to Visit my portfolio and contact me 

> you can visit my protfolio over here :
[Rhiba Zakaria porfolio](https://zak-rhiba.codes)