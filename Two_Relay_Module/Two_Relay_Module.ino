// How to use Two Relay Module
// Written by RHIBA Zakaria

// initialize the input pins
int in1 = 8; // the input that Send to the Relay

int button1 = 9; // the button that Control the in1 state



void setup() {
  // put your setup code here, to run once:
  pinMode(in1,OUTPUT);
  pinMode(button1,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int button1Value = digitalRead(button1);  // Reading the button State 
  if(button1Value == 0){
    digitalWrite(in1,LOW);
  }else{
    digitalWrite(in1,HIGH);
    }
}
