#include "simple-OSC.h"

UDP udp;

const IPAddress OUT_IP(172, 20, 10, 2);
const unsigned int OUT_PORT = 7475;
const unsigned int IN_PORT = 7475;
const bool USING_SIMPLE_OSC = true;

int led1 = D0;


void setup()
{
    /* Network setup */
    Serial.begin(9600);
    udp.begin(IN_PORT);

    while (!WiFi.ready())
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    IPAddress photonIP = WiFi.localIP();

    sendPhotonIDToComputer("/photonip", photonIP);

    /* Actuator/LED setup */
    pinMode(led1, OUTPUT);


}

void sendPhotonIDToComputer(String addr, IPAddress ip){
  Serial.print(F("Photon IP : ")); Serial.print(ip);
  Serial.print(F(" : ")); Serial.print(IN_PORT);

  if (USING_SIMPLE_OSC)
  {
    OSCMessage outMessage(addr);
    outMessage.addInt(ip[0]);
    outMessage.addInt(ip[1]);
    outMessage.addInt(ip[2]);
    outMessage.addInt(ip[3]);
    outMessage.send(udp,OUT_IP,OUT_PORT);
  }
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
        if( inMessage.parse())
        {
            //inMessage.route("/ping", PING);
            Serial.println(inMessage.getFloat(0));
        }

        // I received something! Blink!
        digitalWrite(led1, HIGH);
        delay(200);
        digitalWrite(led1, LOW);

    }

    //SEND
    /*OSCMessage outMessage("/pong");
    outMessage.addString("test");
    outMessage.addFloat(-3.14);
    outMessage.addInt(-1);
    outMessage.send(udp,OUT_IP,OUT_PORT);*/
}

void PING(OSCMessage &inMessage)
{
    //Do something
}
