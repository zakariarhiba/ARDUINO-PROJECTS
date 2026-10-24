/***************************************************************************
 * Thermomètre numérique avec alarme - VERSION POUR WOKWI (simulateur en ligne)
 *
 * Différences avec la version carte réelle (2 seulement, marquées [WOKWI]) :
 *   1) Pas de LM35 dans Wokwi -> un potentiomètre sur A0 simule la
 *      température (tourner = changer la température, de 0.0 à 50.0 °C)
 *   2) Référence ADC = 5 V (DEFAULT) au lieu de 1,1 V
 * Afficheur réglé en "cathode commune" dans Wokwi (segment 1 = allumé,
 * digit 0 = sélectionné). Le reste du code est identique.
 ***************************************************************************/
#define LM35_pin A0
#define DIG_D2 52
#define DIG_D3 51
#define DIG_D4 50
#define LED 32
#define POT A1

// Numbers from 0 to 9, 1 = segment ON (seen from the Arduino)
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

// global variables
int temp;
int temp_trigger;
volatile bool alarme = false;

void setup() {
  Serial.begin(9600);

  pinMode(DIG_D2, OUTPUT);
  pinMode(DIG_D3, OUTPUT);
  pinMode(DIG_D4, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(DIG_D2, HIGH);
  digitalWrite(DIG_D3, HIGH);
  digitalWrite(DIG_D4, HIGH);
  digitalWrite(LED, LOW);

  analogReference(DEFAULT);          // [WOKWI] 5 V  (carte réelle : INTERNAL1V1)
  analogRead(LM35_pin);

  Serial.print("Test Sensor Temp = ");
  temp = mesureTemp();
  Serial.print(temp / 10);
  Serial.print(".");
  Serial.print(temp % 10);
  Serial.println(" C");

  // afficheur Setup
  DDRA = 0xFF;
  PORTA = 0x00;

  initTimer1();
  initTimer3();

  // test AFFICHAGE
  prepareAffichage(888);
  delay(3000);
}

void loop() {
  temp = mesureTemp();
  temp_trigger = mesureTrigger();

  alarme = temp > temp_trigger;

  prepareAffichage(temp);
  Serial.print("Temp = ");
  Serial.print(temp / 10);
  Serial.print(".");
  Serial.print(temp % 10);
  Serial.print(" C  |  Trigger = ");
  Serial.print(temp_trigger / 10);
  Serial.print(".");
  Serial.print(temp_trigger % 10);
  Serial.println(alarme ? " C  -> ALARME, LED blinking" : " C");

  delay(500);
}

// return temperature in tenths
int mesureTemp() {
  // [WOKWI] potentiometer on A0 simulates 0.0 .. 50.0 °C
  return map(analogRead(LM35_pin), 0, 1023, 0, 500);
  // Version carte réelle :
  // long N = analogRead(LM35_pin);
  // return (int)((N * 1100L) / 1024L);
}

// return the trigger TEMP in tenths (0..400 = 0.0..40.0 °C)
int mesureTrigger() {
  return map(analogRead(POT), 0, 1023, 0, 400);
}

void prepareAffichage(int number) {
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
  OCR1A = 1249;                           // 5 ms
  TCCR1B |= (1 << WGM12);                 // CTC
  TCCR1B |= (1 << CS11) | (1 << CS10);    // prescaler 64
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void initTimer3() {
  noInterrupts();
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3  = 0;
  OCR3A = 31249;                          // 0.5 s
  TCCR3B |= (1 << WGM32);                 // CTC
  TCCR3B |= (1 << CS32);                  // prescaler 256
  TIMSK3 |= (1 << OCIE3A);
  interrupts();
}

// Multiplexing: every 5 ms
ISR(TIMER1_COMPA_vect) {
  digitalWrite(DIG_D2, HIGH);
  digitalWrite(DIG_D3, HIGH);
  digitalWrite(DIG_D4, HIGH);

  PORTA = affichage[digitCourant];
  digitalWrite(pinDigits[digitCourant], LOW);

  digitCourant++;
  if (digitCourant >= 3) digitCourant = 0;
}

// Blinking: every 0.5 s
ISR(TIMER3_COMPA_vect) {
  if (alarme) digitalWrite(LED, !digitalRead(LED));
  else digitalWrite(LED, LOW);
}
