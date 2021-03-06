

#include "math.h"


int timer = 10;           // The higher the number, the slower the timing.
int ledPins[] = {
  WKP, RX, TX, D0, D1, D2, D3
};       // an array of pin numbers to which LEDs are attached
int intensity[] = {0, 43, 85, 128, 170, 213, 255};
int pinCount = 7;           // the number of pins (i.e. the length of the array)

const int P_SINE = 0;
const int P_1_FINGER_STROKE = 1;
const int PI = 3.14159265358979323846264338327950288419716939937510582097;
int pattern = P_SINE;


void setup() {

  // No Serial output for Photon // Serial.begin(9600);

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

  float something = millis() / 100.0;

      // from http://forum.arduino.cc/index.php?topic=27475.0
      intensity[i] = 128.0 + 128 * sin(something + (i * 2.0 * PI / pinCount));

  // No Serial in photon, but also just Debug // Serial.println(intensity[i]);

}
