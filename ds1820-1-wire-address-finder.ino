/* 

https://forum.arduino.cc/index.php?topic=143382.0

The sketch compiles ok and uploads fine.
When I open the serial monitor I get

"Looking for 1-Wire devices...
Done"

and no device addresses.
I have checked and rechecked pin numbers and connections 
but still no joy.
Any ideas pls

Cheers
Dennis

Re: Multiple DS18B20 Temperature Sensors on one bus
#3  Aug 23, 2013, 09:25 am 
It might just be the order of events in the code. 
This isn't much different, but it works.

*/

// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

#include <OneWire.h>

OneWire  ds(3);  // Connect your 1-wire device to pin 3

void setup(void) {
  Serial.begin(9600);
  discoverOneWireDevices();
}

void discoverOneWireDevices(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
 
  Serial.print("Looking for 1-Wire devices...\n\r");
  while(ds.search(addr)) {
    Serial.print("\n\rFound \'1-Wire\' device with address:\n\r");

    for( i = 0; i < 8; i++) {
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');
      }
      Serial.print(addr[i], HEX);

      if (i < 7) {
        Serial.print(", ");
      }
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.print("CRC is not valid!\n");
        return;
    }
  }
  Serial.print("\n\r\n\rThat's it.\r\n");
  ds.reset_search();
  return;
}

void loop(void) {
  // nothing to see here
}
