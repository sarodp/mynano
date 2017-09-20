//file:   timer1int.ino
//author: sarodp@yahoo.com
//date:   22-mar-2017
//
//================================================

const byte LED = LED_BUILTIN;

volatile long counter = 0;
volatile long counter0 = 0;
volatile long counterdiff = 0;
volatile boolean state = false;

ISR(TIMER1_COMPA_vect)
{
//static boolean state = false;
  state = !state;  // toggle
  digitalWrite (LED, state ? HIGH : LOW);
  counter = counter + 1;
}

void setup() {
  pinMode (LED, OUTPUT);
  
  // set up Timer 1
  TCCR1A = 0;          // normal operation
  TCCR1B = bit(WGM12) | bit(CS10);   // CTC, no pre-scaling
  OCR1A =  999;       // compare A register value (1000 * clock speed)
  TIMSK1 = bit (OCIE1A);             // interrupt on Compare A Match

  //serial
  Serial.begin(115200);
  Serial.println("hello.........");
}  // end of setup


void loop() {
  Serial.print("state/counter/counterdiff = ");
  Serial.print(state);
  Serial.print("/");
  Serial.print(counter);
  Serial.print("/");
  Serial.println(counterdiff);
  counter0 = counter;
  delay(1000);
  counterdiff = counter- counter0;
}
