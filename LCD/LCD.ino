#include <LiquidCrystal.h> //The library used to print text on the LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Pins the lcd is connected to

void setup() {
lcd.begin(16, 2); //Gives the dimensions of the the LCD in terms of how many characters can be displayed(16 width by 2 height)
}

void loop() {

  lcd.print("hello, world!"); //This will print hello world

}
