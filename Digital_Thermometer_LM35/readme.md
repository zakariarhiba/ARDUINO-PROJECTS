# **Digital Thermometer with Adjustable Alarm (LM35 + 7 Segment Display)**

```
Digital thermometer with an adjustable alarm on Arduino Mega 2560
Written by RHIBA Zakaria
```

*In this project we build a digital thermometer with an Arduino Mega. The LM35 sensor measures the temperature, and we show it on a 7 segment display with a 0.1 °C precision (for example 24.8). A potentiometer sets an alarm temperature between 0 and 40 °C, and when the temperature goes above it, an LED starts blinking.*

*The project is a good way to practice the ADC, the multiplexing of a 7 segment display, the microcontroller registers, the timers and the interrupts.*

The full project sheet (in French) is here : [Fiche projet](docs/Fiche_projet.pdf)

## **Components :**

___

- Arduino Mega 2560
- LM35 temperature sensor
- 4 digit 7 segment display (12 pins, common cathode like 5641AS)
- 1 kΩ potentiometer + 3.3 kΩ resistor
- 1 LED + 220 Ω resistor
- 8 resistors of 1 kΩ (one for each segment)

## **Wiring :**

___

| Component | Arduino pin |
|---|---|
| LM35 Vout | A0 |
| Potentiometer (wiper) | A1 |
| Segments A, B, C, D, E, F, G, DP | 22 to 29 (PORTA) |
| Digits : tens, units, tenths | 52, 51, 50 |
| Alarm LED | 32 |

> Pins 22 to 29 are the PORTA of the ATmega2560, so we can write the 8 segments of a digit in one line : `PORTA = 0x5B;` shows a 2.

## **Measure the temperature :**

___

The LM35 gives 10 mV for each °C. We use the internal 1.1 V reference of the ADC, so one step is 1.1 V / 1024 = 1.07 mV, which is about 0.1 °C :

```C++
analogReference(INTERNAL1V1);
```

The result of `N * 1100 / 1024` is in mV, and since 1 mV = 0.1 °C, it's directly the temperature in tenths of a degree (248 = 24.8 °C). We use a `long` because 1023 * 1100 is bigger than an `int` :

```C++
int mesureTemp() {
  long N = analogRead(LM35_pin);
  return (int)((N * 1100L) / 1024L);
}
```

## **Show it on the 7 segment display :**

___

Each segment is one bit (bit 0 = A ... bit 7 = DP), and we add the decimal point with `| 0x80` :

```C++
byte tabDigit[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
```

The segments are shared between the digits, so we light one digit at a time, 5 ms each (multiplexing). Timer 1 does that in an interrupt every 5 ms (prescaler 64, `OCR1A = 1249`) :

```C++
ISR(TIMER1_COMPA_vect) {
  digitalWrite(DIG_D2, HIGH);              // turn off all digits
  digitalWrite(DIG_D3, HIGH);
  digitalWrite(DIG_D4, HIGH);
  PORTA = affichage[digitCourant];         // segments of the current digit
  digitalWrite(pinDigits[digitCourant], LOW);   // turn it on
  digitCourant++;
  if (digitCourant >= 3) digitCourant = 0;
}
```

## **The alarm :**

___

The potentiometer is converted to a threshold between 0 and 40.0 °C :

```C++
int mesureTrigger() {
  return map(analogRead(POT), 0, 1023, 0, 400);
}
```

Timer 3 makes the LED blink every 0.5 s (prescaler 256, `OCR3A = 31249`) when the temperature is above the threshold. The `loop()` only measures and decides :

```C++
alarme = (temp > temp_trigger);
```

## **Project files :**

___

| File | Content |
|---|---|
| [Digital_Thermometer_LM35.ino](Digital_Thermometer_LM35.ino) | the complete code |
| [steps/](steps) | the code of each step of the project |
| [wokwi/](wokwi) | the circuit and the code to test it on [Wokwi](https://wokwi.com) without hardware |
| [docs/Fiche_projet.pdf](docs/Fiche_projet.pdf) | the project sheet |
| [docs/Support_de_cours.pdf](docs/Support_de_cours.pdf) | the full course with all the explanations and exercises |

The steps (same numbers as the project sheet) :

- `Etape1_Lire_Temperature` : read the LM35 and test the display with 88.8
- `Etape2_Affichage_Timer1` : show the temperature on the display with Timer 1
- Step 3 of the project sheet is the wiring on the real board, it uses the same code as step 2
- `Etape4_Alarme_Potentiometre` : set the alarm with the potentiometer, the LED turns on
- `Etape5_Alarme_Clignotante_Timer3` : the LED blinks with Timer 3

## **Test it on Wokwi :**

___

Create a new Arduino Mega project on [wokwi.com](https://wokwi.com), paste `wokwi/sketch.ino` in the code tab and `wokwi/diagram.json` in the diagram tab, then press play. Wokwi doesn't have an LM35, so a potentiometer on A0 simulates the temperature.

> On the real board, if your display is common anode (like 5641BS), invert the segments (`PORTA = ~affichage[...]`) and the digits (`HIGH` to select, `LOW` to turn off).

___

If you have any Question or Collaboration feel free to Visit my portfolio and contact me 

> you can visit my protfolio over here :
[Rhiba Zakaria porfolio](https://zak-rhiba.codes)
