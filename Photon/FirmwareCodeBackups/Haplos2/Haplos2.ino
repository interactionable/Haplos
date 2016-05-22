/* VERSION HISTORY

160518-16.43: Can receive an OSC message and respond with a LED blink but unable to differentiate between different OSC messages. About to try a different OSC implementation (sparkcore_osc)

*/

#include "OSCMessage.h"

UDP udp;

IPAddress PHOTON_IP;
const IPAddress OUT_IP(172, 20, 10, 2);
const unsigned int REMOTEPORT = 7475;
const unsigned int LOCALPORT = 7475;
const bool USING_SIMPLE_OSC = false;
const int PIN_COUNT = 7;           // the number of pins (i.e. the length of the array)
int ledPins[] = {WKP, RX, TX, D0, D1, D2, D3};       // an array of pin numbers to which LEDs are attached
bool motorOn = 0;

void setup()
{
    /* Network setup */
    Serial.begin(9600);
    udp.begin(LOCALPORT);

    while (!WiFi.ready())
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    IPAddress PHOTON_IP = WiFi.localIP();

    sendPhotonIDToComputer("/photonip", PHOTON_IP);

    /* Actuator/LED setup */
    for (int i = 0; i < PIN_COUNT; i++)
      pinMode(ledPins[i], OUTPUT);
}

void sendPhotonIDToComputer(String addr, IPAddress photon_ip){
  //Serial.print(F("Photon IP : "));
  //Serial.print(photon_ip);
  Serial.print(F(" : "));
  Serial.print(LOCALPORT);

  OSCMessage PhotonIPMessage(addr);
  PhotonIPMessage.add(photon_ip[0]).add(photon_ip[1]).add(photon_ip[2]).add(photon_ip[3]);
  udp.beginPacket(OUT_IP, REMOTEPORT);
	PhotonIPMessage.send(udp);
	udp.endPacket();
}


void loop()
{
    // Wait for an OSC message
    int size = 0;
    int i = 0;
    OSCMessage inMessage;
    if ( ( size = udp.parsePacket()) > 0)
    {
        while (size--) {inMessage.fill(udp.read());}

        // Interpret the OSC message
        if (inMessage.fullMatch("/button1/press")) i = 0;
        else if (inMessage.fullMatch("/button2/press")) i = 1;
        else if (inMessage.fullMatch("/button3/press")) i = 2;
        else if (inMessage.fullMatch("/button4/press")) i = 3;
        else if (inMessage.fullMatch("/button5/press")) i = 4;
        else if (inMessage.fullMatch("/button6/press")) i = 5;
        else if (inMessage.fullMatch("/button7/press")) i = 6;

        //Figure out where the message is to turn the motor on or off
        if (inMessage.getFloat(0) == 1.0){
          motorOn = true; digitalWrite(ledPins[i], HIGH);
          Serial.print("On: "); Serial.print(i);}
        else if  (inMessage.getFloat(0) == 0.0){
          motorOn = false; digitalWrite(ledPins[i], LOW);
          Serial.print("Off: "); Serial.print(i);}


    }



    //SEND
    /*OSCMessage outMessage("/pong");
    outMessage.addString("test");
    outMessage.addFloat(-3.14);
    outMessage.addInt(-1);
    outMessage.send(udp,OUT_IP,REMOTEPORT);*/
}
