/* 
==============================================================
nano basic scope with lcd5110
http://mkme.org/forum/viewtopic.php?f=2&t=692
https://www.youtube.com/watch?v=7pHZiJ4RYlA
=============================================================
  
This is my version of the Arduino oscilloscope code.  This file is strictly the display code for 
one analog channel.  It will soon be merged into my data logger project.

This is shared so others may incorporate the display code into their projects.  It has been modified to 
play nice with the Adafruit 5110 LCD library.

This is a work in progress but hopefully it will help someone else by providing
a base to start and work from.

Please check out my Youtube videos here and consider a thumbs up if this helped you!
Youtube : http://www.youtube.com/user/Shadow5549

Original code comment text:
###########################################################
  Title:       Arduino Uno 3V Oscilloscope
  Purpose:     Use a Nokia 5110 LCD screen with the arduino
  Created by:  Brian O'Dell from the Fileark Arduino Oscilloscope.
  Note:        Please reuse, repurpose, and redistribute this code.
  Note:        This code uses the Adafruit PDC8544 LCD library  
###########################################################
 */
#include "Adafruit_GFX.h"
//#include "PCD8544.h"
#include "Adafruit_PCD8544.h"

/*
3V3 ----LCD VCC
Pin 11--[330 OHM Resistor]---LCD backlight PWM on the Nokia 5110
pin 7  - LCD Serial clock out (SCLK)
pin 6  - LCD Serial data out (DIN)
pin 5  - LCD Data/Command select (D/C)
pin 4  - LCD chip select (CS)
pin 3  - LCD reset (RST)
GND --- LCD GND
*/

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
#define xend 83
#define yend 47

//Analog Pins
int channelAI = A0;      // probe
int delayAI = A1;       // delay potentiometer

float delayVariable =5; // 10 seems good for decent update- bit fast
float scale = 0;
int xCounter = 0;
int yPosition = 0;
int readings[xend];
int rawvals[xend];
int rawmax, rawmin;
int counter = 0;
int ymin = 8;
int ymax = yend;
int dimval = 111; //0=very bright...230=very dim  
void setup() {
analogWrite(11,220);// PWM of LCD backlight but ebay unit is backwards- 
  //must go high + cycle to dim 
  //Very Dim=230
  
   
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
  Serial.println("CLEARDATA");
  Serial.println("LABEL,TIME,A0,A1,A2,A3,A4,A5");
  
  display.begin();//Display code
  display.setContrast(60);//Nokia 5110 works best at 50- no more flicker
  delay(1000);
  display.clearDisplay();     // clears the screen and buffer
  display.setTextSize(1);     // set text size
  display.setTextColor(BLACK);
  //delay(1000);
  
  
   // Splash Personal- taken from example code
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
//display.println("12345678901234");  
  display.println("    SARODP    ");
  display.println("  Data Logger ");
  display.println("              ");  
  display.println(" org: Eric's  ");
  display.println("              ");  
  display.println("  10.09.2017  ");  //max 14 char'd per line
  display.display();
  delay(2000);
  display.clearDisplay();     // clears the screen and buffer
 
}


void loop() 
{  
  //delayVariable = analogRead(delayAI);
  //delayVariable = (delayVariable/10);
  // commented out above delay items as no pot/encoder installed yet
  
  
//--get readings[0..yend]
  scale = (ymax-ymin)/1023.0; 
  for(xCounter = 0; xCounter < xend; xCounter += 1)
  {                                 
      yPosition = analogRead(channelAI);
      rawvals[xCounter] =  yPosition;
      readings[xCounter] = (yPosition*scale);
      delay (delayVariable);
  }


//---tstart draw graph 
 unsigned long tstart,tend,tdiff;
  tstart = millis();
  display.clearDisplay();

//---graph frame Lines
//display.drawLine( x0,y0,x1,y1, BLACK);
  display.drawLine( 0, ymin, 0, ymax, BLACK); 
  //display.drawLine( 0, ymin, xend, ymin, BLACK);
  //display.drawLine( 0, ymax, xend, ymax, BLACK);
  //display.drawLine( xend, ymin, xend, ymax, BLACK);
  //display.drawLine( 0, yend, xend, yend, BLACK);
  
//---graph tick mark
  display.drawLine( 0, ymax-(.166 *1023.0 * scale), 3, ymax-(.166 *1023.0 * scale), BLACK);
  display.drawLine( 0, ymax-(.33 *1023.0 * scale), 6, ymax-(.33 *1023.0 * scale), BLACK);
  
  display.drawLine( 0, ymax-(.5 *1023.0 * scale), 3, ymax-(.5 *1023.0 * scale), BLACK);
  display.drawLine( 0, ymax-(.5 *1023.0 * scale), 85, ymax-(.5 *1023.0 * scale), BLACK);

  display.drawLine( 0, ymax-(.66 *1023.0 * scale), 6, ymax-(.66 *1023.0 * scale), BLACK);
  display.drawLine( 0, ymax-(.84 *1023.0 * scale), 3, ymax-(.84 *1023.0 * scale), BLACK);


//--graph reading[0..85]
  rawmin = rawvals[0];
  rawmax = rawvals[0];  
  for(xCounter = 0; xCounter < xend; xCounter += 1)
    {
       display.drawPixel(xCounter, ymax-readings[xCounter], BLACK);
       if(xCounter>1){
         display.drawLine(xCounter-1, ymax-readings[xCounter-1], xCounter, ymax-readings[xCounter], BLACK);
       }
       
       if (rawvals[xCounter] > rawmax) rawmax = rawvals[xCounter];
       if (rawvals[xCounter] < rawmin) rawmin = rawvals[xCounter];
    }
  
//---graph title---
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);//set cursor top left
  display.print("AH AL:");
  display.print(rawmax);
  display.print(" ");
  display.print(rawmin);
 
//---display.done  
/*
  tend = millis();
  tdiff = tend- tstart;
  display.print(" ms=");
  display.println(tdiff);
*/
  display.display();     
} 


