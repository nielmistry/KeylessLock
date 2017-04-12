/*-----( Import needed libraries )-----*/
#include <Stepper.h>

/*-----( Declare Constants, Pin Numbers )-----*/
//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 32

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 16  //2048  


/*-----( Declare objects )-----*/

//The pin connections need to be 4 pins connected to the Motor Driver 1N1, 1N2, 1N3, 1N4  and then the pins entered here in the sequence 1-3-2-4 for proper sequencing
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 8,10,9,11);

int  Steps2Take;

void setup()   /*----( THIS WILL RUN ONCE AFTER DECLARING ALL THE VARIABLES)----*/
{
//  Nothing present because the motor inputs have already been declared
}/*--(END OF SETUP)---*/

void loop()   /*----( LOOP: KEEP RUNNING CONSTANTLY )----*/
{
  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION ;  // Rotate CW 90 degrees
  small_stepper.setSpeed(500); //SETS THE SPEED OF THE MOTOR IN ROTATIONS PER MINUTE
  small_stepper.step(Steps2Take); //Sets the number of steps the motor has to take
  delay(1000); // 1000ms delay (Aka 1 second)

  //Runs the same code as above except the motor runs in the other direction 
  Steps2Take  =  - STEPS_PER_OUTPUT_REVOLUTION; // A negative is present in front of the STEPS_PER_OUTPUT_REVOLUTION to indicate the direction
  small_stepper.setSpeed(500);  
  small_stepper.step(Steps2Take);
  delay(2000);

}/* --(end main loop )-- */

/* ( THE END ) */

