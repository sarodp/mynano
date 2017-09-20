/*
 Fading

 This example shows how to fade an LED using the analogWrite() function.

 The circuit:
 * LED attached from digital pin 9 to ground.

 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe

 http://www.arduino.cc/en/Tutorial/Fading

 This example code is in the public domain.


 Potentiometer Input Wiring

    Arduino Nano
     GND-----VR 10K-------+3.3V
               |
               |
             ADC0 [pinA0]

    -use analog input [pin A0] or [pin ADC0]
    -to adjust pwm output from 0% to 100%


*/ 
#define POTPIN A0    //arduino nano Potentiometer  
#define POTMAX 68    //adcmax/10 = 9xx/10

int PWMPin = PD3;    // LED connected to digital pin 9
int led0 = LED_BUILTIN;

unsigned int xval;
unsigned int xpc255;
unsigned int xfull;


void setup() {
//0--init ADC  
// analogReference(EXTERNAL);
  
//1-- init pins Dout
//  pinMode (LED, OUTPUT);
//  digitalWrite(LED , OFF);

//2--serial
  Serial.begin(115200);
  Serial.println("LED Dimmer V1.0");


}

void loop() 
{
//1--read VR10K --> calc xpc pwmon,pwmoff
//read xval  
  xval = analogRead(POTPIN);
  
//xpc255 
  xpc255 = xval * 25 / POTMAX;     
  if (xpc255 > 255) xpc255 = 255;          
  if (xpc255 < 0)  xpc255 = 0;         



//2--print current pwm output setting  
  Serial.println("");
  Serial.println("---------------------------");
  
  Serial.print("POT value= ");
  Serial.println(xval);
   
  Serial.print ("pwm on = ");
  Serial.print (xpc255);
  Serial.println ("");

  analogWrite(PWMPin, xpc255);
  delay(20);
}  
 
/*  
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(PWMPin, fadeValue);
    analogWrite(led0, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(PWMPin, fadeValue);
    analogWrite(led0, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}
*/

