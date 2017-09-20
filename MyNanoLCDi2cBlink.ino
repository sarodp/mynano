#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 20, 4);

void setup()
{
	// initialize the LCD
	lcd.begin();
}

void loop()
{
	bool blinking = true;
	lcd.noCursor();
  lcd.cursor();

	while (1) {
		if (blinking) {
			lcd.clear();
      lcd.cursor();
      lcd.noBlink();
	  	lcd.print("Cursor not blink");
			blinking = false;
		} else {
			lcd.clear();
      lcd.cursor();
      lcd.blink();
			lcd.print("Cursor blinking");
			blinking = true;
		}
		delay(3000);
	}
}
