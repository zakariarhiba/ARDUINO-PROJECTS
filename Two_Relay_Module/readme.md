# **Interface Two Channel Relay Module**

*Sometimes you want your Arduino to control AC powered devices like lamps, fans or other household devices. But because the Arduino operates at 5 volts, it cannot directly control these higher voltage devices.*

*That’s where the relay module comes in. You can use a relay module to control the AC mains and Arduino to control the relay.*

See this documentation to understand how the Relay works : [Documentation](https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/).


Here’s the simple code that will control a 220V lamp conected to the relay using a 5V button : 

## **Initialize :**

Controlling a relay module with the Arduino is as simple as controlling an LED. The sketch starts by declaring the pin to which input pin of relay module is connected and also the button

```C++
int in1 = 8;
int button1 = 9;
```

## **Setup Function :**

In the setup function, we define that input pin as being output and the button pin as an input

```C++
void setup() {
  pinMode(in1,OUTPUT);
  pinMode(button1,INPUT);
}
```

## **Loop Function :**

Now in the loop function, we turn the device ON using a condition if the state of the button is HIGH 

we're using a pull up button in this case

```C++
void loop() {
  int button1Value = digitalRead(button1);  
  if(button1Value == 0){
    digitalWrite(in1,LOW);
  }else{
    digitalWrite(in1,HIGH);
    }
}
```

## The Complet Code : 

```C++
int in1 = 8; 
int button1 = 9; 

void setup() {
  pinMode(in1,OUTPUT);
  pinMode(button1,INPUT);
}

void loop() {
  int button1Value = digitalRead(button1);
  if(button1Value == 0){
    digitalWrite(in1,LOW);
  }else{
    digitalWrite(in1,HIGH);
    }
}
```

___

If you have any Question or Collaboration feel free to Visit my portfolio and contact me 

> you can visit my protfolio over here :
[Rhiba Zakaria porfolio](https://zak-rhiba.codes)