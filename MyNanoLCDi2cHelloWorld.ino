#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
/* NANO wiring
NANO LCD i2c BOARD
 GND --- GND
 +5V --- +5V
 D4  --- SDA
 D5  --- SCL
 */

// 0x27 or 0x3F = LCD Address for PCF8754 Controller 
// 20,4 = 20 chars, 4 lines
LiquidCrystal_I2C lcd(0x3F,20,4);
void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
  lcd.setCursor(0, 0);  //col0,row0
  lcd.print("Hello, world! ..row0");
  lcd.setCursor(0, 1);  //col0,row1
  lcd.print("Hello, world! ..row1");
  lcd.setCursor(0, 2);  //col0,row2
  lcd.print("Hello, world! ..row2");
  lcd.setCursor(0, 3);  //col0,row3
  lcd.print("Hello, world! ..row3");
}          //12345678901234567890  

void loop()
{
	// Do nothing here...
}
