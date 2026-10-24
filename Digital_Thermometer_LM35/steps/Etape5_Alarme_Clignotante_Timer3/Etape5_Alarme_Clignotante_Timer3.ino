#define LM35_pin A0
#define DIG_D2 52
#define DIG_D3 51
#define DIG_D4 50
#define LED 32
#define POT A1

// Numbers from 0 to 9 in cathode commune mode turn on in HIGH which is 1
byte tabDigit[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
const byte pinDigits[3] = {DIG_D2, DIG_D3, DIG_D4};
volatile byte affichage[3];


// variable for ISR timer
volatile byte digitCourant = 0;


// Function declarations
void prepareAffichage(int number);
int mesureTemp();
int mesureTrigger();
void initTimer1();
void initTimer3(); 


// global variable for TEMP
int temp;
int temp_trigger;
volatile bool alarme = false; 


// Setup Arduino
void setup() {

  Serial.begin(9600);


  pinMode(LM35_pin,INPUT);
  pinMode(DIG_D2,OUTPUT);
  pinMode(DIG_D3,OUTPUT);
  pinMode(DIG_D4,OUTPUT);
  pinMode(POT,INPUT);
  pinMode(LED,OUTPUT);

  digitalWrite(DIG_D2, HIGH);
  digitalWrite(DIG_D3, HIGH);
  digitalWrite(DIG_D4, HIGH);
  digitalWrite(LED, LOW);


  analogReference(INTERNAL1V1);
  analogRead(LM35_pin);

  //test temp 
  Serial.print("Test Sensor Temp = ");
  temp = mesureTemp();
  Serial.print(temp/10);
  Serial.print(".");
  Serial.print(temp%10);
  Serial.println(" C");


  // afficheur Setup
  DDRA = 0xFF; 
  PORTA = 0x00;

  initTimer1();
  initTimer3();

  //test AFFICHAGE 
  prepareAffichage(888);

  
  delay(3000);
}

void loop() {
  temp = mesureTemp();
  temp_trigger = mesureTrigger();

  alarme = temp > temp_trigger; 

  prepareAffichage(temp);
  Serial.println("New Mesure TEMP : ");
  Serial.print("Temp = ");
  Serial.print(temp/10);
  Serial.print(".");
  Serial.print(temp%10);
  Serial.println(" C");

  Serial.print("Trigger = ");
  Serial.print(temp_trigger/10);
  Serial.print(".");
  Serial.print(temp_trigger%10);
  Serial.println(" C");

  if (alarme == true){
    Serial.println("Trigger High, LED blinking");
  } 

  delay(500);
}



// return temperature en dixieme 
int mesureTemp(){
  long N = analogRead(LM35_pin);
  return (int)((N*1100L)/1024L); 
}

// return the trigger TEMP 
int mesureTrigger(){
  return map(analogRead(POT), 0, 1023, 0, 400); 
}

// Preparation d'affichage d'afficheur
void prepareAffichage(int number){
  if (number > 999) number = 999;
  if (number < 0) number = 0;

  int dizaine = number / 100;
  int unite = (number / 10) % 10;
  int dixieme = number % 10;

  if (dizaine == 0) affichage[0] = 0x00;
  else affichage[0] = tabDigit[dizaine];
  
  affichage[1] = tabDigit[unite] | 0x80;
  affichage[2] = tabDigit[dixieme];

 
}


void initTimer1() {
  noInterrupts();                        

  TCCR1A = 0;                             
  TCCR1B = 0;
  TCNT1  = 0;                             

  OCR1A = 1249;   

  TCCR1B |= (1 << WGM12);                 
  TCCR1B |= (1 << CS11) | (1 << CS10);    
  TIMSK1 |= (1 << OCIE1A);                

  interrupts();                           
}

void initTimer3() {
  noInterrupts();                        

  TCCR3A = 0;                             
  TCCR3B = 0;
  TCNT3  = 0;                             

  OCR3A = 31249;              // 31 250 ticks = 0.5 s
  TCCR3B |= (1 << WGM32);     // CTC
  TCCR3B |= (1 << CS32);      // prescaler 256  

  TIMSK3 |= (1 << OCIE3A); 

  interrupts();                           
}


// Multiplexing: called automatically every 5 ms by Timer 1
ISR(TIMER1_COMPA_vect){
   // turn off all digits
  digitalWrite(DIG_D2, HIGH);
  digitalWrite(DIG_D3, HIGH);
  digitalWrite(DIG_D4, HIGH);

  // Affichage current Digit
  PORTA = affichage[digitCourant];
  digitalWrite(pinDigits[digitCourant], LOW);

  // next time: next digit
  digitCourant++;
  if (digitCourant >= 3) digitCourant = 0;

}


ISR(TIMER3_COMPA_vect){
  if (alarme == true) digitalWrite(LED, !digitalRead(LED));
  else digitalWrite(LED, LOW);
}
