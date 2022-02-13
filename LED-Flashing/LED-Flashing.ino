// initialize Input/Output
int led = 8;

#define 

void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT); //Set led as an Output
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led,HIGH); // Turn led On 
  delay(1000);   // Set a timer for 1000ms
  digitalWrite(led,LOW); // Turn led Off
  delay(1000);   // Set a timer for 1000ms
}
