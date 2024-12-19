/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Theenash Muneeswaran And Grant Knect                      */
/*    Created:      Thu Oct 17 2024                                           */
/*    Description:  4478F Drive Code with autonomus                           */
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
// mintake              motor         19              
// mfrontintake         motor         6               
// RightN               digital_out   A               
// LeftN                digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----
//yougotpugged
#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

brain Brain;
controller Controller1;
motor mFrontRight = motor(PORT16, ratio18_1, false);
motor mMidRight = motor(PORT3, ratio18_1, false);
motor mBackRight = motor(PORT11, ratio18_1, false);
motor mMidLeft = motor(PORT5, ratio18_1, true);
motor mFrontLeft = motor(PORT7, ratio18_1, true);
motor mBackLeft = motor(PORT4, ratio18_1, true);
motor mintake = motor(PORT17, ratio18_1, false);
motor mfrontintake = motor(PORT6, ratio18_1, true);
digital_out bottomN = digital_out(Brain.ThreeWirePort.A);
digital_out topN = digital_out(Brain.ThreeWirePort.C);

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


void intakeup(int waittime){
  mintake.spinFor(reverse, waittime, degrees, true);
}

void intakedown(int waittime){
  mintake.spinFor(forward, waittime, degrees, true);
}

void frontintakeup(int waittime){
  mfrontintake.spinFor(forward, waittime, degrees, true);
}

void frontintakedown(int waittime){
  mfrontintake.spinFor(reverse, waittime, degrees, true);
}


void bothintakeup(int waittime){
  mfrontintake.spinFor(forward, waittime, degrees, false);
  mintake.spinFor(reverse, waittime, degrees, true);
}


void bothintakedown(int waittime){
  mfrontintake.spinFor(reverse, waittime, degrees, false);
  mintake.spinFor(forward, waittime, degrees, true);
}

void bothmoveintakeup(int waittime){
  mfrontintake.spinFor(forward, waittime, degrees, false);
  mintake.spinFor(reverse, waittime, degrees, true);
}


void bothmoveintakedown(int waittime){
  mfrontintake.spinFor(reverse, waittime, degrees, false);
  mintake.spinFor(forward, waittime, degrees, true);
}




void clamplock(){
  bottomN.set(true);
  topN.set(true);
}

void clampunlock(){
  bottomN.set(false);
  topN.set(false);
}


//Will,"you are a faluire!!!! (in asian accent)" 


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
  
  //Brain.Screen.pressed(autonSelection);
  Controller1.Screen.print("hi");
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void AWP(){
  
}

void Normal(){
  
}
   
void Skills(){
  drivereverse(180);
  clamplock();
  mintake.setVelocity(100, percent);
  intakeup(600);
  turnleft(255);
  setVelo(50);
  bothmoveintakedown(400);
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


  if (Controller1.ButtonL1.pressing()) {
      mfrontintake.spin(forward, 100, percent);
      mintake.spin(reverse, 100, percent);
    }
    else if (Controller1.ButtonL2.pressing()) {
      mfrontintake.spin(reverse, 100, percent);
      mintake.spin(forward, 100, percent);
    }
    else{
      mfrontintake.stop(hold);
      mintake.stop(hold);
    }

  //lock
    if (Controller1.ButtonY.pressing()){
      bottomN.set(true);
      topN.set(true);
      }
      //unlock
      else if (Controller1.ButtonB.pressing()){
      bottomN.set(false);
      topN.set(false);
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
