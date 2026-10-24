---
title: "ميزان حرارة رقمي مع منبه قابل للضبط"
description: "ميزان حرارة بدقة عُشر درجة باستخدام الحساس LM35 وشاشة عرض ذات سبع قطع، مع منبه قابل للضبط يجعل مصباح LED يومض. نستخدم المحول التناظري الرقمي، والمسح المتعدد، والسجلات، ومؤقتين."
board: "Arduino Mega 2560"
notions: ["المحول التناظري الرقمي والجهد المرجعي 1.1 فولت", "شاشة العرض ذات القطع السبع", "المسح المتعدد", "السجل PORTA", "المؤقتان 1 و 3", "المقاطعات"]
components: ["لوحة Arduino Mega 2560", "حساس الحرارة LM35", "شاشة عرض ذات سبع قطع بأربعة أرقام", "مقاومة متغيرة 1 كيلو أوم", "مصباح LED واحد", "8 مقاومات 1 كيلو أوم", "مقاومة 3.3 كيلو أوم", "مقاومة 220 أوم"]
resources:
  - label: "بطاقة المشروع (PDF، بالفرنسية)"
    url: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/Fiche_projet.pdf"
  - label: "دعامة الدرس كاملة (PDF، بالفرنسية)"
    url: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/Support_de_cours.pdf"
  - label: "الوثيقة التقنية للحساس LM35 (PDF)"
    url: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/datasheet_capteur_LM35.pdf"
  - label: "المحاكاة على Wokwi (الدارة والشيفرة)"
    url: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/Digital_Thermometer_LM35/wokwi"
---

# **ميزان حرارة رقمي مع منبه قابل للضبط**

```
مشروع Arduino رقم 5: LM35 وشاشة عرض ذات سبع قطع
إعداد: RHIBA Zakaria، Zakpy Academy
```

*في هذا المشروع نقيس درجة الحرارة بالحساس LM35، ونعرضها على شاشة عرض ذات سبع قطع بدقة 0.1 درجة مئوية (مثلًا 24.8). تسمح مقاومة متغيرة بضبط درجة حرارة المنبه بين 0 و 40 درجة. عندما تتجاوز الحرارة هذه القيمة، يبدأ مصباح LED في الوميض.*

*يبدو المشروع بسيطًا، لكنه يسمح بالتعرف على مفاهيم مهمة: المحول التناظري الرقمي، والمسح المتعدد للشاشة، وسجلات المتحكم الدقيق، والمؤقتات، والمقاطعات.*

## **وثائق المشروع**

___

| الوثيقة | المحتوى |
|---|---|
| [بطاقة المشروع](https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/Fiche_projet.pdf) | الوصف، ومخطط Proteus، والمراحل، والملاحق (بالفرنسية) |
| [دعامة الدرس](https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/Support_de_cours.pdf) | الشرح الكامل، والأخطاء الشائعة، وتمارين محلولة (بالفرنسية) |
| [الوثيقة التقنية للحساس LM35](https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/datasheet_capteur_LM35.pdf) | توثيق الحساس |

## **ما الذي سنتعلمه**

___

- قراءة جهد كهربائي بالمحول التناظري الرقمي واختيار الجهد المرجعي المناسب (1.1 فولت).
- ترميز أرقام شاشة العرض ذات القطع السبع في بايت واحد.
- كتابة 8 منافذ دفعة واحدة باستخدام السجل `PORTA`.
- عرض عدة أرقام بطريقة المسح المتعدد.
- ضبط مؤقت واستخدام مقاطعة.

## **المكونات**

___

- لوحة Arduino Mega 2560
- حساس الحرارة LM35
- شاشة عرض ذات سبع قطع بأربعة أرقام (12 طرفًا، مثل 5641AS بمهبط مشترك)
- مقاومة متغيرة 1 كيلو أوم ومقاومة 3.3 كيلو أوم
- مصباح LED ومقاومة 220 أوم
- 8 مقاومات 1 كيلو أوم (واحدة لكل قطعة)

## **التوصيل**

___

![مخطط المشروع على Proteus: لوحة Arduino Mega 2560، الحساس LM35، شاشة العرض ذات القطع السبع، المقاومة المتغيرة ومصباح LED (هنا شاشة بمصعد مشترك مع عواكس 4049)](images/schema-proteus.png)

| العنصر | منفذ Arduino |
|---|---|
| الحساس LM35 (المخرج Vout) | A0 |
| المقاومة المتغيرة (الطرف الأوسط) | A1 |
| القطع A و B و C و D و E و F و G و DP | من 22 إلى 29 (PORTA) |
| أرقام العشرات والوحدات والأعشار | 52 و 51 و 50 |
| مصباح المنبه | 32 |

> المنافذ من 22 إلى 29 تشكل السجل PORTA في المتحكم ATmega2560. لذلك يمكننا كتابة القطع الثماني لرقم ما في سطر واحد: `PORTA = 0x5B;` يعرض الرقم 2.

## **قياس درجة الحرارة**

___

يعطي الحساس LM35 جهدًا قدره 10 ملي فولت لكل درجة. نستخدم الجهد المرجعي الداخلي 1.1 فولت للمحول التناظري الرقمي، فتصبح الخطوة 1.1 / 1024 = 1.07 ملي فولت، أي حوالي 0.1 درجة.

```C++
analogReference(INTERNAL1V1);
```

العملية `N × 1100 / 1024` تعطي الجهد بالملي فولت، وبما أن 1 ملي فولت يساوي 0.1 درجة، فالنتيجة هي درجة الحرارة بالأعشار مباشرة (248 تعني 24.8 درجة). نستخدم النوع `long` لأن 1023 × 1100 أكبر من سعة النوع `int`:

```C++
int mesureTemp() {
  long N = analogRead(LM35_pin);
  return (int)((N * 1100L) / 1024L);
}
```

## **العرض على الشاشة ذات القطع السبع**

___

كل قطعة تقابل بِتًّا واحدًا (البت 0 للقطعة A … البت 7 للنقطة DP)، ونضيف النقطة العشرية بالعملية `| 0x80`:

```C++
byte tabDigit[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
```

القطع مشتركة بين الأرقام، لذلك نشغل رقمًا واحدًا في كل مرة، لمدة 5 ملي ثانية لكل رقم: هذا هو المسح المتعدد. يتكفل المؤقت 1 بذلك داخل مقاطعة كل 5 ملي ثانية (مقسم التردد 64، و `OCR1A = 1249`):

```C++
ISR(TIMER1_COMPA_vect) {
  digitalWrite(DIG_D2, HIGH);              // on éteint tout
  digitalWrite(DIG_D3, HIGH);
  digitalWrite(DIG_D4, HIGH);
  PORTA = affichage[digitCourant];         // les segments du chiffre
  digitalWrite(pinDigits[digitCourant], LOW);   // on allume ce chiffre
  digitCourant++;
  if (digitCourant >= 3) digitCourant = 0;
}
```

## **المنبه**

___

تتحول قيمة المقاومة المتغيرة إلى درجة حرارة بين 0 و 40.0 درجة:

```C++
int mesureTrigger() {
  return map(analogRead(POT), 0, 1023, 0, 400);
}
```

يجعل المؤقت 3 المصباح يومض كل 0.5 ثانية (مقسم التردد 256، و `OCR3A = 31249`) عندما تتجاوز الحرارة قيمة المنبه. أما الدالة `loop()` فتكتفي بالقياس واتخاذ القرار:

```C++
alarme = (temp > temp_trigger);
```

## **مراحل المشروع**

___

شيفرة كل مرحلة موجودة في المجلد [steps](https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/Digital_Thermometer_LM35/steps)، بنفس أرقام بطاقة المشروع:

- `Etape1_Lire_Temperature`: قراءة الحساس LM35 واختبار الشاشة بعرض 88.8
- `Etape2_Affichage_Timer1`: عرض درجة الحرارة باستخدام المؤقت 1
- المرحلة 3 هي التوصيل على اللوحة الحقيقية، بنفس شيفرة المرحلة 2
- `Etape4_Alarme_Potentiometre`: ضبط المنبه بالمقاومة المتغيرة، ويشتغل المصباح
- `Etape5_Alarme_Clignotante_Timer3`: وميض المصباح باستخدام المؤقت 3

## **الاختبار دون مكونات على Wokwi**

___

أنشئ مشروع Arduino Mega جديدًا على [wokwi.com](https://wokwi.com)، والصق `wokwi/sketch.ino` في تبويب الشيفرة و `wokwi/diagram.json` في تبويب المخطط، ثم شغّل المحاكاة. لا يوجد الحساس LM35 في Wokwi، لذلك تؤدي مقاومة متغيرة على المنفذ A0 دور الحرارة.

> على اللوحة الحقيقية، إذا كانت شاشتك بمصعد مشترك (مثل 5641BS)، يجب عكس القطع (`PORTA = ~affichage[...]`) وعكس الأرقام (`HIGH` للاختيار و `LOW` للإطفاء).

## **الشيفرة الكاملة**

___

التعليقات والرسائل داخل الشيفرة باللغة الفرنسية، كما في ملف `.ino` الذي يمكنك تحميله.

```C++
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
```

## **للتعمق أكثر**

___

- استبدل المصباح بجرس صوتي للحصول على منبه مسموع.
- أضف هامشًا (تخلفًا) حتى لا يشتغل المنبه وينطفئ باستمرار قرب القيمة المحددة.
- احفظ قيمة المنبه في الذاكرة الدائمة (EEPROM) حتى بعد انقطاع الكهرباء.
- أرسل درجة الحرارة إلى الهاتف، كأول لبنة في مشروع المنزل الذكي King House.
