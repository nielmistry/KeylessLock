#include <IRremote.h>  //Include IR remote library
#include <LiquidCrystal.h>  // include LCD library
#include <Stepper.h>  //include Stepper library
#define STEPS_PER_MOTOR_REVOLUTION 32   //define steps per rev
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 16 //define steps per output revolution
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  //declares the lcd and what pins the LCD is connected to
int IR_PIN = 10; //defines the pin that the IR Reciever is connected to
IRrecv irrecv(IR_PIN);  //tells the IRRecv library what pin the IR Reciever is connected to
decode_results results; //initalizes a place to put the recieved IR numbers

// Password variables
int p1 = 0xFF6897; // first digit of the password
int p2 = 0xFF6897; // second digit of the password
int p3 = 0xFF6897; // third digit of the password
int p4 = 0xFF6897; // fourth digit of the password
//Variable declarations
int a, b, c, d;  //variables to store the inputted number
int i = 0; // initializes and sets the loop counter to 0
int incorrect = 0; //intializes and sets the incorrect attempt counter to 0
int recievedNumber; //intitializes an integer to place the recieved number in
boolean OPEN = false; //intializes a boolean to monitor the state of the lock (open and close), and sets it to closed


//variables for motor
int Steps2Take; // a general integer to store the amount of steps to take
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 6, 8, 7, 9); //declares the stepper motor controller and what pins it is connected to

void setup() {  // RUNS ONLY ONCE WHEN ARDUINO IS STARTED
  Serial.begin(9600);  //starts a serial session on port 9600 (for debugging only)
  irrecv.enableIRIn(); //enables the irreciever library
  lcd.begin(16, 2);  // Declares that the LCD is 16 by 2
  printToLCD("Please enter your password");

}


void loop() {  //LOOPS FOREVER
  if (!OPEN) {  // Only enters the next set of statements if the lock is not open
    if (irrecv.decode( & results)) { //If there is a result to be decoded, enters the next set of statte3ments
      recievedNumber = results.value, HEX;  //stores the recieved number by the library in a hex form into an int
      Serial.println(recievedNumber);  //Prints recieved number on the serial interface (FOR DEBUGGING ONLY)
      if (i < 4) {  //Enters the next set of statements only if the amount of times a button has been pressed is 4 or less.
        switch (i) {   // based on what the value of i is, it will do different things
          case 0:    // If i = 0 (first number to be inputted)
            {
              a = recievedNumber;    //stores the recieved number into variable a
              lcd.clear();           //clears anything that was on the lcd
              lcd.print(convertNumbers(a));  //prints a human readable number on the screen
              irrecv.resume();        //resumes looking for an IR value
              break;                  //breaks out of the whole switch statement
            }
          case 1:                         //If i = 1
            {
              b = recievedNumber;           //stores the recieved number into variable b
              lcd.print(convertNumbers(b));     //prints out human readable number on the screen
              irrecv.resume();                  //resumes looking for an IR value
              break;                            //breaks out of the whole switch statement
            }
          /*
               THE REST OF THE SWITCH STATEMENT WORKS IN THE SAME WAY
          */
          case 2:
            {
              c = recievedNumber;
              lcd.print(convertNumbers(c));
              irrecv.resume();
              break;
            }
          case 3:
            {
              d = recievedNumber;
              lcd.print(convertNumbers(d));
              irrecv.resume();
              break;
            }
          default:
            {
              Serial.println("no value");   //debugging purposes, if i does not equal 0,1,2 or 3 (should never happen)
            }

        }
        i++;    //adds one to the loop counter, so that the next number can be inputted
      }
    }
  } else {    //If the lock is NOT open
    if (irrecv.decode(&results)) {  //if there is an ir value to decode, go to the next lines
      recievedNumber = results.value, HEX; //stores recieved number into an int
      Serial.println(recievedNumber);  //debugging only, prints number out to serial
      if (recievedNumber == 765) {   // If play/pause button is hit
        closeLock();                 // Closes the lock
      }
      irrecv.resume();               // begins looking for new IR inputs

    }
  }

  if (a && b && c && d != NULL) { //only enters next statements if a, b, c and d all have values assigned to them

    if (correctPass(a, b, c, d, p1, p2, p3, p4)) {   //if the correctPass function (which takes the inputted numbers and the correct numbers) returns true, open the lock, and prints correct password to the LCD
      if (!OPEN) {  //only does this if the locks closed
        Serial.println("correctPass");
        printToLCD("correct Password!");
        openLock();
      }

    } else {    //if the correctPass function returns false, prints "wrong code, try again" to the LCD
      Serial.println("Incorrect");
      printToLCD("Wrong code, try again");

      reset(true);  //calls the reset function with the wrong argument to be true

    }
  }

  if (incorrect >= 3) { //if the amount of attempts is equal to 3, print "too many attempts, locked" to the LCD
    Serial.println("TOO MANY ATTEMPTS");  //debug
    printToLCD("Too many attempts, locked");
    while (1) {  // An infinite loop containing nothing, so the program will stay in this loop forever (until arduino is physically reset)

    }
  }

  delay(2000); //Waits 2 seconds before doing the loop again
}


boolean correctPass(int a, int b, int c, int d, int p1, int p2, int p3, int p4) { //takes in the inputted numbers and the right numbers for each of the 4 digits
  if ((a == p1 && b == p2 && c == p3 && d == p4)) { // if the numbers are correct and entered in the right order, return true to whatever called
    return true;
  } else {                                          // otherwise return false
    return false;

  }

}

void printToLCD(String output) { //a function to properly format outputs to the LCD
  lcd.clear(); //clears LCD first
  if (output.length() > 16) {   //If the output length is greater than 16 (width of lcd), do the following things: cut it into a 16 character string and put the rest into a new string
    String string1 = output.substring(0, 16);
    String string2 = output.substring(16, output.length());
    lcd.print(string1);  //print the first 16 character string
    lcd.setCursor(0, 1); //set the cursor to the next row
    lcd.print(string2);  //print the rest of the string
    lcd.setCursor(0, 0); //put the cursor back at the beginning
  } else  {
    lcd.print(output);   // if the string is than 16 characters, just print it
  }
}


void openLock() { // this function opens the lock
  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION ;  // Rotate CW 1 turn
  small_stepper.setSpeed(500);
  small_stepper.step(Steps2Take);
  OPEN = true;
}

void closeLock() {//this function closes the lock
  Steps2Take  =  - STEPS_PER_OUTPUT_REVOLUTION;  // Rotate CCW 1 turn
  small_stepper.setSpeed(700);  // 700 a good max speed??
  small_stepper.step(Steps2Take);
  OPEN = false;
  reset(false);   //calls the reset function while passing false to the wrong parameter
}

void reset(boolean wrong) {  //a function that resets the arduino depending on whether it was an incorrect password attempt or if it was meant to be locked
  if (wrong) {  //if it is an incorrect password attempt, add 1 to the incorrect counter
    incorrect++;
  } else {     // if the lock was intentionally locked, set the incorrect counter to 0 and print Please enter your password to the lcd.
    incorrect = 0;
    printToLCD("Please enter your password");
  }
  i = 0;      //regardless if it was an incorrect attempt or not, set the loop counter to 0
  a, b, c, d = NULL;  //set a, b, c, d (the ints that store the recieved numbers)

}

String convertNumbers(int originalNum) {   // converts a recieved encoded IR number to the human-readable equivilant
  switch (originalNum) {
    case 0xFF6897: {
        return String(0);
      }
    case 0xFF30CF: {
        return String(1);
      }
    case 0xFF18E7: {
        return String(2);
      }
    case 0xFF7A85: {
        return String(3);
      }
    case 0xFF10EF: {
        return String(4);
      }
    case 0xFF38C7: {
        return String(5);
      }
    case 0xFF5AA5: {
        return String(6);
      }
    case 0xFF42BD: {
        return String(7);
      }
    case 0xFF4AB5: {
        return String(8);
      }
    case 0xFF52AD: {
        return String(9);
      }
    default: {
        return "X";  // if it is not a number from 0-9, or the reciever malfunctions, return an "X"
      }
  }
}



