#include <IRremote.h>  //includes the IRRemote library
int RECV_PIN = 10;  // declares the pin it is connected to
IRrecv irrecv(RECV_PIN);  //tells IRRecv library what pin the IR sensor is connected to
decode_results results;  //where the IRRecv library puts results
int recievedNumber;      //where we store results temporarily

void setup(){  // RUNS ONCE
  Serial.begin(9600);
  irrecv.enableIRIn();    //enable the IR sensor
}

void loop(){ //LOOPS FOREVER
  if(irrecv.decode(&results)){   // if a signal is detected, do the following
    recievedNumber = results.value, HEX;  //stores the results into an int
    Serial.println(recievedNumber);     //prints that int to the serial output
    irrecv.resume();                  //resumes looking for the next input
  }
  delay(2000);                        //waits 2 seconds until looping again
}

