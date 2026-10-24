#define LM35_pin A0

#define DIG_D2 52
#define DIG_D3 51
#define DIG_D4 50

// Numbers from 0 to 9 in cathode commune mode turn on in HIGH which is 1
byte tabDigit[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// list for Digits 7 segement 
const byte pinDigits[3] ={DIG_D2, DIG_D3, DIG_D4 };
volatile byte affichage[3];


// functions declaration
void prepareAffichage(int number);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LM35_pin, INPUT);
  analogReference(INTERNAL1V1);
  analogRead(LM35_pin);                 // reference settling

  // analog read test 
  Serial.print("Sensor LM35 ADC TEST =>  ");
  Serial.print(analogRead(LM35_pin));
  Serial.println(" N value");

  // Afficheur Setup 
  DDRA = 0xFF;  // segments as outputs
  PORTA = 0x00;  // all segments off

  pinMode(DIG_D2, OUTPUT);
  pinMode(DIG_D3, OUTPUT);
  pinMode(DIG_D4, OUTPUT);

  digitalWrite(DIG_D2, HIGH); 
  digitalWrite(DIG_D3, HIGH); 
  digitalWrite(DIG_D4, HIGH); 

  // Test afficheur 7 segments on afficher 88.8 for 3 loops
  prepareAffichage(888);
  for(int j=0; j<3; j++){
    for(int k=0; k<=68; k++){
      for (int i=0; i<=2;i++){
        PORTA = affichage[i];
        digitalWrite(pinDigits[i], LOW);
        delay(5);
        digitalWrite(pinDigits[i], HIGH);
      }
    }
    delay(1000);
  }
  PORTA = 0x00;
  // end setup
}

void loop() {
  // put your main code here, to run repeatedly:
  long N = analogRead(LM35_pin);

  int temp = (int) ((N * 1100L )/ 1024L);
  
  Serial.print("Temp = ");
  Serial.print(temp / 10);
  Serial.print(".");
  Serial.print(temp % 10);
  Serial.println(" C");
  delay(2000);
}


void prepareAffichage(int number){

  byte dizaine = number / 100;
  byte unit = (number / 10) % 10;
  byte dixieme = number % 10;

  affichage[0] = tabDigit[dizaine];
  affichage[1] = tabDigit[unit] | 0x80;
  affichage[2] = tabDigit[dixieme];
}

