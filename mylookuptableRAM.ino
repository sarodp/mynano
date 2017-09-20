////////////////////////////////////////////////////////////////////////////////////
// 
// http://embeddedgurus.com/stack-overflow/2010/01/a-tutorial-on-lookup-tables-in-c
//
// https://www.arduino.cc/en/Reference/PROGMEM
// https://playground.arduino.cc/Main/PROGMEM
// https://www.arduino.cc/en/Reference/Static
//
// ***************************
////////////////////////////////////////////////////////////////////////////////////



static const uint8_t hexlookup[16] =
{
0x00U, 0x07U, 0x0EU, 0x09U, 0x1CU, 0x1BU, 0x12U, 0x15U,
0x38U, 0x3FU, 0x36U, 0x31U, 0x24U, 0x23U, 0x2AU, 0x2DU
};


static const uint16_t mvlookup[16] =
{ 
101,1111,2222,3333,4444,5555,6666,7777,8888,8999,1010,1111,1212,1313,1414,1515
};


static uint8_t xhex; 
static float xmv;

void setup() {
  Serial.begin(115200);  
  Serial.println("Ready");    //Test the serial monitor
    
}

void loop() {

 for(int i=0;i<=15;i++)        
 {
   xhex = hexlookup[i];
   xmv = mvlookup[i] * 1;
   
   Serial.print("    i=");  
   Serial.print(i);  
   Serial.print("    xhex=");  
   Serial.print(xhex);
   Serial.print("    xmv=");  
   Serial.print(xmv,1);
   Serial.println(" ");
 } 
   Serial.println("================================");
   delay(1000);
}


//------------------------------------------------------------------------------------
// decimal-to-string-float function
//
//  dtostrf(floatVar, minStringWidthIncDecimalPoint, numVarsAfterDecimal, charBuf);
//
//------------------------------------------------------------------------------------
// ====sample code
//
/*
  float xF = 1.25;
  char xbuffer[16];
  
    dtostrf(xF,5,2,xbuffer);
    Serial.print("Float : ");
    Serial.println(xbuffer);
*/
//
//-----------------------------------------------------------------------------------

