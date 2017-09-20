////////////////////////////////////////////////////////////////////////////////////
// 
// http://embeddedgurus.com/stack-overflow/2010/01/a-tutorial-on-lookup-tables-in-c
//
// https://www.arduino.cc/en/Reference/PROGMEM
// https://playground.arduino.cc/Main/PROGMEM
// https://www.arduino.cc/en/Reference/Static
// https://manned.org/pgm_read_word_far
//https://electronics.stackexchange.com/questions/26682/accessing-data-past-64k-boundary-on-atmega1280
//
////////////////////////////////////////////////////////////////////////////////////

#include <avr/pgmspace.h>


// save some unsigned ints
// const PROGMEM  uint16_t charSet[]  = 
// { 65000, 32796, 16843, 10, 11234};
//

//==========================================================
// PROGMEM SECTION
//==========================================================
const char CharTable[] PROGMEM  = 
{"ABCDEFGHIJKLMNOPQRTUVWXYZ"};

const uint8_t ByteTable[] PROGMEM =
{
0x00U, 0x07U, 0x0EU, 0x09U, 0x1CU, 0x1BU, 0x12U, 0x15U,
0x38U, 0x3FU, 0x36U, 0x31U, 0x24U, 0x23U, 0x2AU, 0x2DU
};


const uint16_t WordTable[] PROGMEM =
{ 
101,1111,2222,3333,4444,5555,6666,7777,
8888,8999,1010,1111,1212,1313,1414,1515
};

const uint32_t DwordTable[] PROGMEM =
{ 
99101,99111,99222,93333,94444,95555,96666,97777,
98888,98999,91010,91111,91212,91313,91414,91515
};

const float FloatTable[] PROGMEM =
{ 
9.9101,9.9111,9.9222,9.3333,9.4444,9.5555,9.6666,9.7777,
9.8888,9.8999,9.1010,9.1111,9.1212,9.1313,9.1414,9.1515
};




//==========================================================
// PROGCODE SECTION
//==========================================================
static uint8_t xbyte;
static char xchar; 
static float xmv1, xmv2, xmv3;
//uint8_t xbyte;
//char xchar; 
//float xmv1, xmv2, xmv3;

void setup() {
  Serial.begin(115200);  
  Serial.println("Ready");    //Test the serial monitor
    
}

void loop() {

 for(int i=0;i<=15;i++)        
 {
  //RAM table lookup
  // xbyte = ByteTable[i];
  // xmv1 = WordTable[i] * 1;
  
  //PROGMEM table lookup
   xbyte = pgm_read_byte(ByteTable+i);
   xchar = char(pgm_read_byte(CharTable+i));

   xmv1 = pgm_read_word(WordTable+i) *.1 ;
   xmv2 = pgm_read_dword(DwordTable+i) *.1 ;
   xmv3 = pgm_read_float(FloatTable+i) * .1 ;
   
   Serial.print("    i=");  
   Serial.print(i);  

   Serial.print("    xchar=");  
   Serial.print(xchar);
   Serial.print("    xbyte=");  
   Serial.print(xbyte);

   Serial.print("    xmv1=");  
   Serial.print(xmv1,1);
   Serial.print("    xmv2=");  
   Serial.print(xmv2,1);
   Serial.print("    xmv3=");  
   Serial.print(xmv3,4);
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




//-----------------------------------------------------------------------------------
/*
// https://www.arduino.cc/en/Reference/PROGMEM?action=sourceblock&num=5
//
// PROGMEM string demo
// How to store a table of strings in program memory (flash),
// and retrieve them.
//
//  Information summarized from:
// http://www.nongnu.org/avr-libc/user-manual/pgmspace.html
//
// Setting up a table (array) of strings in program memory is slightly complicated, but
// here is a good template to follow.
//
// Setting up the strings is a two-step process. First define the strings.


#include <avr/pgmspace.h>

//PROGMEM section=============================================
//---"String 0" etc are strings to store - change to suit.
//---Then set up a table to refer to your strings.
const char string_0[] PROGMEM = "String 0";   
const char string_1[] PROGMEM = "String 1";
const char string_2[] PROGMEM = "String 2";
const char string_3[] PROGMEM = "String 3";
const char string_4[] PROGMEM = "String 4";
const char string_5[] PROGMEM = "String 5";

const char* const string_table[] PROGMEM = 
{string_0, string_1, string_2, string_3, string_4, string_5};


//PROGCODE section================================================
char buffer[30];    // make sure this is large enough for the largest string it must hold

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Serial.println("OK");
}


void loop()
{
  // Using the string table in program memory requires the use of special functions to retrieve the data.
  //   The strcpy_P function copies a string from program space to a string in RAM ("buffer").
  //   Make sure your receiving string in RAM  is large enough to hold whatever
  //   you are retrieving from program space.


  for (int i = 0; i < 6; i++)
  {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i]))); // Necessary casts and dereferencing, just copy.
    Serial.println(buffer);
    delay( 500 );
  }
}
*/
//-----------------------------------------------------------------------------------------------
