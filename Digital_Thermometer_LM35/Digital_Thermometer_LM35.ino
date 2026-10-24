/*********************************************************************
 *  Thermomètre numérique avec alarme - Arduino Mega 2560 (16 MHz)
 *  LM35 + afficheur 7 segments (Timer 1) + alarme réglable (Timer 3)
 *  Written by RHIBA Zakaria - Zakpy Academy
 *********************************************************************/
#define LM35_pin A0      // capteur LM35
#define POT      A1      // potentiomètre du seuil
#define LED      32      // LED d'alarme
#define DIG_D2   52      // afficheur des dizaines
#define DIG_D3   51      // afficheur des unités (+ point)
#define DIG_D4   50      // afficheur des dixièmes

// Codes 0..9, 1 = segment allumé (cathode commune, ou anode commune + 4049)
byte tabDigit[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
const byte pinDigits[3] = {DIG_D2, DIG_D3, DIG_D4};

volatile byte affichage[3];          // les 3 codes à afficher
volatile byte digitCourant = 0;      // afficheur allumé en ce moment
volatile bool alarme = false;        // décidée par loop(), lue par Timer 3

int temp;                            // température en dixièmes (248 = 24,8 °C)
int temp_trigger;                    // seuil en dixièmes (0..400)

void prepareAffichage(int number);
int  mesureTemp();
int  mesureTrigger();
void initTimer1();
void initTimer3();

void setup() {
  Serial.begin(9600);

  pinMode(DIG_D2, OUTPUT);  digitalWrite(DIG_D2, HIGH);   // HIGH = éteint
  pinMode(DIG_D3, OUTPUT);  digitalWrite(DIG_D3, HIGH);
  pinMode(DIG_D4, OUTPUT);  digitalWrite(DIG_D4, HIGH);
  pinMode(LED, OUTPUT);     digitalWrite(LED, LOW);

  analogReference(INTERNAL1V1);      // 1 pas = 1,07 mV ≈ 0,1 °C
  analogRead(LM35_pin);              // 1re lecture ignorée

  DDRA  = 0xFF;                      // broches 22..29 en sortie
  PORTA = 0x00;

  initTimer1();                      // multiplexage toutes les 5 ms
  initTimer3();                      // clignotement toutes les 0,5 s

  prepareAffichage(888);             // test des segments : 88.8
  delay(3000);
}

void loop() {
  temp         = mesureTemp();
  temp_trigger = mesureTrigger();
  alarme       = (temp > temp_trigger);   // loop() décide, les timers agissent

  prepareAffichage(temp);

  Serial.print("Temp = ");
  Serial.print(temp / 10);  Serial.print(".");  Serial.print(temp % 10);
  Serial.print(" C  |  Seuil = ");
  Serial.print(temp_trigger / 10);  Serial.print(".");  Serial.print(temp_trigger % 10);
  Serial.println(alarme ? " C  -> ALARME" : " C");

  delay(500);
}

// Température en dixièmes : N x 1100 / 1024 = mV = dixièmes de °C
int mesureTemp() {
  long N = analogRead(LM35_pin);           // long : 1023 x 1100 dépasse un int
  return (int)((N * 1100L) / 1024L);
}

// Seuil en dixièmes : 0..1023 -> 0..400 (0,0 à 40,0 °C)
int mesureTrigger() {
  return map(analogRead(POT), 0, 1023, 0, 400);
}

// Découpe la valeur en 3 chiffres et prépare les codes
void prepareAffichage(int number) {
  if (number > 999) number = 999;          // 3 digits : 99,9 max
  if (number < 0)   number = 0;

  int dizaine = number / 100;
  int unite   = (number / 10) % 10;
  int dixieme = number % 10;

  if (dizaine == 0) affichage[0] = 0x00;   // pas de zéro inutile
  else              affichage[0] = tabDigit[dizaine];
  affichage[1] = tabDigit[unite] | 0x80;   // point décimal (bit 7)
  affichage[2] = tabDigit[dixieme];
}

// Timer 1 : CTC, prescaler 64, 1250 ticks de 4 us = 5 ms
void initTimer1() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A  = 1249;
  TCCR1B |= (1 << WGM12);                  // mode CTC
  TCCR1B |= (1 << CS11) | (1 << CS10);     // prescaler 64
  TIMSK1 |= (1 << OCIE1A);                 // autorise l'interruption
  interrupts();
}

// Timer 3 : CTC, prescaler 256, 31250 ticks de 16 us = 0,5 s
void initTimer3() {
  noInterrupts();
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3  = 0;
  OCR3A  = 31249;
  TCCR3B |= (1 << WGM32);                  // mode CTC
  TCCR3B |= (1 << CS32);                   // prescaler 256
  TIMSK3 |= (1 << OCIE3A);
  interrupts();
}

// Multiplexage : un afficheur à chaque appel (toutes les 5 ms)
ISR(TIMER1_COMPA_vect) {
  digitalWrite(DIG_D2, HIGH);              // 1) tout éteindre
  digitalWrite(DIG_D3, HIGH);
  digitalWrite(DIG_D4, HIGH);

  PORTA = affichage[digitCourant];         // 2) segments du chiffre
  digitalWrite(pinDigits[digitCourant], LOW);   // 3) allumer cet afficheur

  digitCourant++;                          // 4) le suivant au prochain appel
  if (digitCourant >= 3) digitCourant = 0;
}

// Clignotement : bascule la LED toutes les 0,5 s si alarme
ISR(TIMER3_COMPA_vect) {
  if (alarme) digitalWrite(LED, !digitalRead(LED));
  else        digitalWrite(LED, LOW);
}
