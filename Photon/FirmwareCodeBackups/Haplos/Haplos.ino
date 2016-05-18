/* VERSION HISTORY

160518-16.43: Can receive an OSC message and respond with a LED blink but unable to differentiate between different OSC messages. About to try a different OSC implementation (sparkcore_osc)

*/

#include "OSCMessage.h"
UDP udp;


const IPAddress OUT_IP(172, 20, 10, 2);
IPAddress PHOTON_IP;
const unsigned int REMOTEPORT = 7475;
const unsigned int LOCALPORT = 7475;
const bool USING_SIMPLE_OSC = false;
bool motorOn = 0;

int led1 = D0;


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
    pinMode(led1, OUTPUT);


}

void sendPhotonIDToComputer(String addr, IPAddress photon_ip){
  Serial.print(F("Photon IP : "));
  Serial.print(photon_ip);
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

    //RECEIVE
    int size = 0;
    OSCMessage inMessage;

    if ( ( size = udp.parsePacket()) > 0)
    {
        while (size--)
        {
            inMessage.fill(udp.read());
        }
        //Figure out where the message is to turn the motor on or off
        if (inMessage.getFloat(0) == 1.0){
          motorOn = true; digitalWrite(led1, HIGH);
          Serial.print(F("Button ON!"));
          }
        else if  (inMessage.getFloat(0) == 0.0){
          motorOn = false; digitalWrite(led1, LOW);
          Serial.print(F("Button off"));}
    }



    //SEND
    /*OSCMessage outMessage("/pong");
    outMessage.addString("test");
    outMessage.addFloat(-3.14);
    outMessage.addInt(-1);
    outMessage.send(udp,OUT_IP,REMOTEPORT);*/
}
