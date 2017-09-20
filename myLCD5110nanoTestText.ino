/*
youtube sep2017:
https://www.youtube.com/watch?v=7pHZiJ4RYlA

blog sep,2017:
http://mkme.org/forum/viewtopic.php?f=2&t=692

=============================================================
This is the uber simple starter code 
so people can get an idea how the structure is set up:
=============================================================

This is a work in progress 
but hopefully it will help someone else 
by providing a base to start and work from.

Please check out my Youtube videos here and consider a thumbs up if this helped you!
Youtube : http://www.youtube.com/user/Shadow5549
Website, Forum and store are at http://mkme.org

3V3 ----LCD VCC
Pin 11--[330 OHM Resistor]---LCD backlight PWM on the Nokia 5110
pin 7  - LCD Serial clock out (SCLK)
pin 6  - LCD Serial data out (DIN)
pin 5  - LCD Data/Command select (D/C)
pin 4  - LCD chip select (CS)
pin 3  - LCD reset (RST)
GND --- LCD GND
*/


#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);//4 and 3 are reversed on the cheap eBay models

void setup() {

//01-- 
// PWM of LCD backlight but ebay unit is backwards- 
//must go high + cycle to dim 
//Very Dim=230
  analogWrite(11,50);

//02--
  Serial.begin(115200);
  Serial.println("Running..."); 

//03--  
  display.begin();//Display code
  display.setContrast(60);//Nokia 5110 works best around 50- change to suit your unit

  delay(1000);
  display.clearDisplay();     // clears the screen and buffer

  display.setTextSize(1);     // set text size
  display.setTextColor(BLACK);
  //delay(1000);

  
 // Splash Screen- taken from example code
  display.setTextSize(1);
  display.setTextColor(BLACK);
 
  display.setCursor(0,0);//set cursor top left
  display.println("0.TEST DISPLAY");
  //Prints the first line then a line break- 
  //leave off the ln characters to continue on the same line!
  
  display.println("1.01234567890-");
  display.println("2.ABCDEFGHIJK-");
  display.println("3.abcdefghijk-");
  display.println("4.mnopqrstuvw-");
  display.println("5.xyz[]!@%^()-");
 
  display.display();//this command writes all the preceeding info to the lcd

  delay(5000);//wait 2 seconds
  display.clearDisplay();     // clears the screen and buffer
 
}

void loop() {
 
LCDDisplay();

}

void LCDDisplay(){
  display.clearDisplay();              // clears the screen and buffer
  //--line0
  display.setCursor(0,0);
  display.setTextSize(1); //set text size back smaller
  display.println("Analog Pin 0");

  //--line1
  //display.setCursor(5, 1);
  display.println ("");

  //--line2
  display.setTextSize(1); //set text size back smaller
  display.println("Raw");
  display.print("Value ");

  //--line2a
  int sensorValue = analogRead(A0);
  display.setTextSize(2);     // set text sizebigger
  display.print(sensorValue);//print the pin value driectly


  //--doDisplay!
  display.display();
  //delay(2000);
}
    
  
   

