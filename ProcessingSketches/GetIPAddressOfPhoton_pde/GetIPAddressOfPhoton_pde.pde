/**
 * oscP5parsing by andreas schlegel
 * example shows how to parse incoming osc messages "by hand".
 
 * You need to download and install the  oscP5 library: http://www.sojamo.de/oscP5
 
 * it is recommended to take a look at oscP5plug for an
 * alternative and more convenient way to parse messages.
 */

import oscP5.*;
import netP5.*;

OscP5 oscP5;

void setup() {
  size(400,400);
  frameRate(25);
  /* start oscP5, listening for incoming messages at port 7475 */
  oscP5 = new OscP5(this,7475);
  
}

void draw() {
  background(0);  
}


void oscEvent(OscMessage theOscMessage) {
  /* check if theOscMessage has the address pattern we are looking for. */
      println("### received an osc message. with address pattern "+theOscMessage.addrPattern());
  
  if(theOscMessage.checkAddrPattern("/photonip")==true) {
      int v1 = theOscMessage.get(0).intValue();  
      int v2 = theOscMessage.get(1).intValue();
      int v3 = theOscMessage.get(2).intValue();
      int v4 = theOscMessage.get(3).intValue();
      println("Photon IP Addresss is "+ v1 + "." +v2+ "." +v3 +"." +v4);
  } 
  else {
      println("It's a button! It's address pattern is " + theOscMessage.addrPattern());
      if(theOscMessage.checkTypetag("f")) { 
         //We're expecting a type 'f' (float)
        float f1 = theOscMessage.get(0).floatValue();  
        println("First value "+ f1);
      }
      else println("Aaargh it's not a float");
  } 
}