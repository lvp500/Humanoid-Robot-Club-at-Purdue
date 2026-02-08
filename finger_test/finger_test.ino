/*
* Program Description:
*   This code is written to test the movement of humanoid fingers 
*   composed of 2 linear actuators.
*
* OG Writer: Jeongin Shin
* editors: <put your name>
* 
* Written on: Feb 8th, 2026
*/

#include <Servo.h>

Servo actuator1, actuator2;
Servo actuator[2] = {actuator1, actuator2};
int pin[2] = {}; // define the pin numbers for actuator1 and actuator2

// the range of the angle in Servo.h is from 0 deg to 180 deg
int angle[2] = {90, 90}; // angle of the motor inside of the actuator1 and actuator2

// the joystick is analogue pin
// let x axis of the joystick to be the controller of actuator1
// and y axis to be the controller of actuator2
int pin_joystick[2] = {}; // put the analogue pin numbers of VRx (the first element) and VRy (the second element)

// and you won't neew SW pin unless you also want to use "switch" function of the joystick

void setup() {
  // connecting each actuators to their pins
  actuator[0].attach(pin[0]);
  actuator[1].attach(pin[1]);

  Serial.begin(9600);

  // Check if the two actuators are connected and can get inputs from the program
  actuator[0].write(angle[0]);
  actuator[1].write(angle[1]);
}

void loop() {
  int val[2];
  for (int i=0; i<2; i++){ // read the voltage inputs of the joystick
    // return of analogRead is between 0 to 1023
    // check https://components101.com/modules/joystick-module for more information
    val[i]= analogRead(pin_joystick[i]);
    moveAct(i,val[i]); // update the actuator's angle
  }
  delay (20);
}

void moveAct(byte num, int joy){

  if(joy > 767)
  {
    // the angle of the corresponding actuator increases by 1
    angle[num] += 1; 

    // if it is actuator1
    if(num == 0){ 
      if(angle[num] > 160){ // if the angle is over 160 deg
        // set it to 160 deg to prevent possible physical error
        angle[num] = 160; 
      }
    }
    // else if it is actuator2
    if(num == 1){ 
      if(angle[num] > 160){ // if the angle is over 160 deg
        // set it to 160 deg to prevent possible physical error
        angle[num] = 160; 
      }
    }

  }
  else if(joy < 255){
    // the angle of the corresponding actuator decreases by 1
    angle[num] -= 1; 

    // if it is actuator1
    if(num == 0){ 
      if(angle[num] < 20){ // if the angle is under 20 deg
        // set it to 20 deg to prevent possible physical error
        angle[num] = 20; 
      }
    }
    // else if it is actuator2
    else if(num == 1){ 
      if(angle[num] < 20){ // if the angle is under 20 deg
        // set it to 20 deg to prevent possible physical error
        angle[num] = 20; 
      }
    }
  }

  actuator[num].write(angle[num]);

}
