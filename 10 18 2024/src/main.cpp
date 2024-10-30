/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Theenash Muneeswaran And Grant Knect                      */
/*    Created:      Thu Oct 17 2024                                           */
/*    Description:  4478F 2024 Drive Code                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// mFrontRight          motor         16              
// mMidRight            motor         3               
// mBackRight           motor         11              
// mMidLeft             motor         5               
// mFrontLeft           motor         7               
// mBackLeft            motor         4               
// arm                  motor         2               
// Claw                 motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
void setVelo(int speed){
  mFrontLeft.setVelocity(speed, percent);
  mFrontRight.setVelocity(speed, percent);
  mMidLeft.setVelocity(speed, percent);
  mMidRight.setVelocity(speed, percent);
  mBackLeft.setVelocity(speed, percent);
  mBackRight.setVelocity(speed, percent);
}

void driveforward(int waitTime){
  mFrontLeft.spinFor(forward, waitTime, degrees, false);
  mFrontRight.spinFor(forward, waitTime, degrees, false);
  mMidLeft.spinFor(forward, waitTime, degrees, false);
  mMidRight.spinFor(forward, waitTime, degrees, false);
  mBackLeft.spinFor(forward, waitTime, degrees, false);
  mBackRight.spinFor(forward, waitTime, degrees, true);
}

void drivereverse(int waitTime){
  mFrontLeft.spinFor(reverse, waitTime, degrees, false);
  mFrontRight.spinFor(reverse, waitTime, degrees, false);
  mMidLeft.spinFor(reverse, waitTime, degrees, false);
  mMidRight.spinFor(reverse, waitTime, degrees, false);
  mBackLeft.spinFor(reverse, waitTime, degrees, false);
  mBackRight.spinFor(reverse, waitTime, degrees, true);
}

void turnright(int waitTime){
  mFrontLeft.spinFor(forward, waitTime, degrees, false);
  mFrontRight.spinFor(reverse, waitTime, degrees, false);
  mMidLeft.spinFor(forward, waitTime, degrees, false);
  mMidRight.spinFor(reverse, waitTime, degrees, false);
  mBackLeft.spinFor(forward, waitTime, degrees, false);
  mBackRight.spinFor(reverse, waitTime, degrees, true);
}

void turnleft(int waitTime){
  mFrontLeft.spinFor(reverse, waitTime, degrees, false);
  mFrontRight.spinFor(forward, waitTime, degrees, false);
  mMidLeft.spinFor(reverse, waitTime, degrees, false);
  mMidRight.spinFor(forward, waitTime, degrees, false);
  mBackLeft.spinFor(reverse, waitTime, degrees, false);
  mBackRight.spinFor(forward, waitTime, degrees, true);
}


void armup(int waittime){
  arm.spinFor(forward, waittime, degrees, true);
}

void armdown(int waittime){
  arm.spinFor(reverse, waittime, degrees, true);
}



int autono = 0;
void autonSelection(){
  if (autono <= 2){
    autono++;
  }
  else{
    autono=0;
  }
  switch(autono){
    case 0:
    Brain.Screen.clearLine();
    Brain.Screen.print("AWP");
    break;
    case 1:
    Brain.Screen.clearLine();
    Brain.Screen.print("Normal");
    break;
    case 2:
    Brain.Screen.clearLine();
    Brain.Screen.print("Skills");
    break;
  }
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.pressed(autonSelection);
  Controller1.Screen.print("hi");
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void AWP(){

}

void Normal(){
  driveforward(600);
  armup(90);
  turnleft(90);
  armdown(90);
  turnright(90);
  driveforward(600);
  armup(90);
  drivereverse(600);
  turnright(90);
  driveforward(700);
  armdown(90);
  drivereverse(700);
  turnright(90);
  driveforward(1000);
  armup(90);
  drivereverse(1000);
  turnleft(90);
  driveforward(700);
  armdown(90);
  drivereverse(700);
  turnleft(90);
}

void Skills(){

}

void autonomous(void) {
  switch(autono){
    case 0:
    AWP();
    break;
    case 1:
    Normal();
    break;
    case 2:
    Skills();
    break;
  }

}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    mFrontRight.spin(forward, (Controller1.Axis2.position(pct)), pct);
    mMidRight.spin(forward, (Controller1.Axis2.position(pct)), pct);
    mBackRight.spin(forward, (Controller1.Axis2.position(pct)), pct);
    mMidLeft.spin(forward, (Controller1.Axis3.position(pct)), pct);
    mFrontLeft.spin(forward, (Controller1.Axis3.position(pct)), pct);
    mBackLeft.spin(forward, (Controller1.Axis3.position(pct)), pct);

    if (Controller1.ButtonR1.pressing()) {
        arm.spin(forward);   
    }
    else if (Controller1.ButtonR2.pressing()) {
        arm.spin(reverse);
    }
    else{
      arm.stop(hold);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec); 
  }
}
