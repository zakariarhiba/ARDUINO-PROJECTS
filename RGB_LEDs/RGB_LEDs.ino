// Example using RGB LED 
// Written by RHIBA Zakaria

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
