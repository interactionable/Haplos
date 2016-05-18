/*
  I need to start sketching out functions, like

  traceGroove(direction, speed, startingVertebra, endingVertebra)
  linger(Vertebra)
  if muscleTonusIsHeld(Vertebra), linger(Vertebra), linger(previous(Vertebra)), linger(next(Vertebra))
  touch(Vertebra, pseudoweight, speed) // It's pseudoweigh because it's not actually

  if MuscleTonusIsHeld(side, VertebralSection), awaken(side, VertebralSection)


*/



int timer = 10;           // The higher the number, the slower the timing.
int ledPins[] = {
  3, 5, 6, 9, 10, 11
};       // an array of pin numbers to which LEDs are attached
int intensity[] = {0, 51, 102, 154, 205, 255};
int fade[] = {1, 1, 1, 1, 1, 1};
int pinCount = 6;           // the number of pins (i.e. the length of the array)

const int P_SINE = 0;
const int P_1_FINGER_STROKE = 1;
int pattern = P_SINE;


void setup() {
  Serial.begin(9600);

  // declare pins to be an output:
  for (int i = 0; i < pinCount; i++)
    pinMode(ledPins[i], OUTPUT);

}


// the loop routine runs over and over again forever:
void loop() {
  for (int i = 0; i < pinCount; i++)
  {
    //Write all the pins
    analogWrite(ledPins[i], intensity[i] );
    updateValue(i);
  }


  //  delay(timer);

  /*  // wait for 30 milliseconds to see the dimming effect

    for (int i = 0; i < pinCount; i++)
      analogWrite(ledPins[i], 0);
    delay(timer);
  */
}

void updateValue(int i) {

  /*
      intensity[i] += fade[i];
      if (intensity[i] <= 0 || intensity[i] >= (255 - fade[i] + 1))
        fade[i] = -fade[i];
  */
  float something = millis() / 100.0;

  switch (pattern)
  {
    case P_SINE:
      // from http://forum.arduino.cc/index.php?topic=27475.0
      intensity[i] = 128.0 + 128 * sin(something + (i * 2.0 * PI / pinCount));
      break;
    case P_1_FINGER_STROKE:
      break;
    default:
      break;
  }
  // Serial.println(intensity[i]);


}
