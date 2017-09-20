
//
//    FILE: dht11_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: DHT library test sketch for DHT11 && Arduino
//     URL:
//
// Released to the public domain
//

#include <dht.h>

#define DHT11_PIN 5
dht DHT;
int DHTrtn;

void setup()
{
  Serial.begin(115200);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
}

void loop()
{
  // READ DATA
  Serial.print("> DHT11 Status =");
  DHTrtn = DHT.read11(DHT11_PIN);
  
  switch (DHTrtn)
  { case DHTLIB_OK:  
		   Serial.print("OK,\t"); 
		   break;
    case DHTLIB_ERROR_CHECKSUM: 
		   Serial.print("Checksum error"); 
		   break;
    case DHTLIB_ERROR_TIMEOUT: 
		   Serial.print("Time out error"); 
		   break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error");
        break;
    default: 
		    Serial.print("Unknown error"); 
		    break;
   }
  
  // DISPLAY DATA
  Serial.print("=> humidity(%)/temperature(C) = ");
  Serial.print(DHT.humidity,0);
  Serial.print("/");
  Serial.println(DHT.temperature,1);

  delay(2000);
}
//
// END OF FILE
//
