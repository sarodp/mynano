//file:   pwmtimer1int.ino
//author: sarodp@yahoo.com
//date:   22-mar-2017
//
//Board: Arduino Nano
//================================================

#define ACout1 PD4  //arduino nano
#define ACout2 PD5  //arduino nano
#define POTPIN A0    //arduino nano Potentiometer  

#define POTMAX 69    //adcmax/10 = 9xx/10

#define OFF LOW
#define ON HIGH


//================================================

const byte LED = LED_BUILTIN;

const unsigned int pwm1000msec = 16000;   // 1000msec
const unsigned int pwm500msec  =  8000;  //  500msec
const unsigned int pwm250msec  =  4000;   //  250msec


const unsigned int pwmcntmax = pwm250msec;
const unsigned int pwmcnt001 = pwmcntmax/100;

volatile unsigned int pwmcnt = 0;
volatile unsigned int pwmcntOFF = 0;   

// ___----------------________
//    |..pwmcntmax............|
//    |...pwmcntOFF..|

unsigned int xval;
unsigned int xpc;
unsigned int xfull;

//========================================================
ISR(TIMER1_COMPA_vect)
{
  //---pwmcnt
  pwmcnt = pwmcnt+1;
  if (pwmcnt > pwmcntmax) {
    pwmcnt = 0;
  }

  //ACout1
   if (pwmcnt >= pwmcntOFF) {
    digitalWrite(LED,OFF);
    digitalWrite(ACout1,OFF);
    digitalWrite(ACout2,OFF);
   }
   else {
    digitalWrite(LED,ON);
    digitalWrite(ACout1,ON);
    digitalWrite(ACout2,ON);
   }
}

//========================================================
void setup() {
  
//00-- set up Timer 1
  TCCR1A = 0;          // normal operation
  TCCR1B = bit(WGM12) | bit(CS10);   // CTC, no pre-scaling
  OCR1A =  999;       // compare A register value (1000 * clock speed)
  TIMSK1 = bit (OCIE1A);             // interrupt on Compare A Match

//0--init ADC  
// analogReference(EXTERNAL);
  
//1-- init pins Dout
  pinMode (LED, OUTPUT);
  pinMode(ACout1, OUTPUT);
  pinMode(ACout2, OUTPUT);
  
  digitalWrite(LED , OFF);
  digitalWrite(ACout1 , OFF);
  digitalWrite(ACout2 , OFF);

//2--serial
  Serial.begin(115200);
  Serial.println("hello.........");

}  // end of setup


//========================================================
void loop() {
//1--read VR10K --> calc xpc pwmon,pwmoff
//read xval  
  xval = analogRead(POTPIN);
  
//xpc 
  xpc = xval * 10 / POTMAX;
  if (xpc > 100)  xpc = 100;          
  if (xpc < 0)  xpc = 0;          

//pwmon,pwmoff  
  pwmcntOFF = xpc * pwmcnt001;

//2--print current pwm output setting  
  Serial.println("");
  Serial.println("---------------------------");
  
  Serial.print("POT value= ");
  Serial.println(xval);
   
  Serial.print ("% pwm on = ");
  Serial.print (xpc);
  Serial.println ("%");

  Serial.print ("pwmcntmax/pwncntOFF = ");
  Serial.print (pwmcntmax);
  Serial.print (" ");
  Serial.print (pwmcntOFF);
  Serial.print (" ");

//3----  
  delay(1000);
  
}

/*=============================================================  
  PWM Low Frequency SSR 220VAC Load Control
  Module: NodeMCU or Arduino Nano 
  =============================================================
  Turns on an AC Line Light Bulb as a heater
  with low frequency pwm concept.

  Use SSR G3MB 202P module as an AC line output module.
  
  1)OMRON G3MB 202P 
   -Solid State Relay with zero crossing input
   -220VAC, 1A output , 2A resistive fuse
  
    
  2)output wiring

   Arduiono Nano
   [SSR DC+] <---- 5VDC [pin VU]   //5V power supply from USB port
   [SSR DC-] <---- 0VDC [pin GND]  //power and signal ground
   [SSR CH1] <---- ACout1 [pin PD4]   //5V output signal :High=on,Low=off
   [SSR CH2] <---- ACout2 [pin PD5]   //5V output signal :High=on,Low=off spare

  
  3) SSR AC Load wiring
  
   line220VAC o------[Manual SW]------[AC LOAD1*]----|
                                                     |
                                                     | 
   line0VAC   o------[SSR A1]_/_[SSR B1]-------------|


   line220VAC o------[Manual SW]------[AC LOAD2*]----|
                                                     |
                                                     | 
   line0VAC   o------[SSR A2]_/_[SSR B2]-------------|


  
  4) AC Load1,2
    -intended loads function as heaters
    -test load = AC generic light bulbs
    -220VAC, 100W Test OK 
    -Max Load = 1A,220VAC by SSR spec.


  5) Potentiometer Input Wiring

    Arduino Nano
     GND-----VR 10K-------+3.3V
               |
               |
             ADC0 PIN

    -use analog input [pin A0] or [pin ADC0]
    -to adjust pwm output from 0% to 100%
   
*/
