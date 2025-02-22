/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Theenash Muneeswaran                                      */
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
// mflipper             motor         1
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
motor mflipper = motor(PORT11, ratio18_1, true);

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

void bothmoveforwardintakeup(int waittime){
  mfrontintake.spinFor(forward, waittime, degrees, false);
  driveforward(waittime);
  mintake.spinFor(reverse, waittime, degrees, true);
}


void bothmovebackwardintakeup(int waittime){
  mfrontintake.spinFor(forward, waittime, degrees, false);
  drivereverse(waittime);
  mintake.spinFor(reverse, waittime, degrees, true);
}

void motorstop(int waitTime){
  mFrontLeft.stop(hold);
  mFrontRight.stop(hold);
  mMidLeft.stop(hold);
  mMidRight.stop(hold);
  mBackLeft.stop(hold);
  mBackRight.stop(hold);
  wait(waitTime, msec);
}


void clamplock(){
  bottomN.set(false);
  topN.set(true);
}

void clampunlock(){
  bottomN.set(true);
  topN.set(false);
}


void flipperup(int waitTime){
  mflipper.spinFor(forward, waittime, degrees, true);
}


void flipperdown(int waitTime){
  mflipper.spinFor(reverse, waittime, degrees, true);
}


 bool pressedClamp = false;
 void toggleClamp(){
  pressedClamp = !pressedClamp;
  if(pressedClamp){
    bottomN.set(false);
      topN.set(true);
  }
  else if(!pressedClamp){
    bottomN.set(true);
      topN.set(false);
  }
 }


int autono = 0;
void autonSelection(){
  if (autono <= 3){
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
    Brain.Screen.print("red-right");
    break;
    case 2:
    Brain.Screen.clearLine();
    Brain.Screen.print("Skills");
    break;
    case 3:
    Brain.Screen.clearLine();
    Brain.Screen.print("Normal-left");
    break;

  }
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  
  Brain.Screen.pressed(autonSelection);
  /*Controller1.Screen.print("hi");
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Brain.Screen.setPenColor(red);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0, 0, 240, 120);
  Brain.Screen.setCursor(3 , 9);
  Brain.Screen.setPenColor(green);
  Brain.Screen.print("Left");
  Brain.Screen.setPenColor(blue);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(240, 0, 240, 120);
  Brain.Screen.setCursor(3, 32);
  Brain.Screen.setPenColor(yellow);
  Brain.Screen.print("Right");
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0, 120, 480, 240);
  Brain.Screen.setCursor(10, 24);
  Brain.Screen.setPenColor(white);
  Brain.Screen.print("Skills");*/
}



void AWP(){
  
}

void redright(){


  setVelo(50);
  drivereverse(380);
  //motorstop(500);
  turnleft(130);
  //motorstop(500);
  clampunlock();
  setVelo(20);
  drivereverse(250);
  clamplock();
  mintake.setVelocity(100, percent);
  intakeup(490);
  drivereverse(470);
  setVelo(100);
  mintake.setVelocity(100, percent);
  mfrontintake.setVelocity(100, percent);
  driveforward(175);
  turnleft(127);
  driveforward(500);
  bothintakeup(1000);
  driveforward(75);
  bothintakeup(1000);



}   




void Normalleft(){
  setVelo(50);
  drivereverse(310);
  motorstop(500);
  turnright(80);
  motorstop(500);
  clampunlock();
  setVelo(20);
  drivereverse(250);
  clamplock();
  mintake.setVelocity(100, percent);
  intakeup(490);
  drivereverse(570);
}   



void Skills(){
  clampunlock();
  drivereverse(190);
  clamplock();
  mintake.setVelocity(100, percent);
  mfrontintake.setVelocity(100, percent);
  intakeup(600);
  turnleft(300);
  setVelo(50);
  bothmoveforwardintakeup(800);
  intakeup(500);
  turnright(200);
  bothintakeup(800);
  drivereverse(400);
  turnleft(400);
  drivereverse(500);

  /*
  turnright(1020);
  drivereverse(200);
  bothintakeup(200);
  drivereverse(200);
  bothintakeup(200);
  turnright(510);  
  drivereverse(200);
  bothintakeup(200);
  turnleft(1275);
  drivereverse(200);
  clampunlock();
  driveforward(200);
  turnright(765);
  drivereverse(600);
  clamplock();
  turnleft(1020);
  driveforward(200);
  bothmoveintakeup(200);
  driveforward(200);
  bothmoveintakeup(200);
  turnleft(765);
  driveforward(200);
  bothintakeup(200);
  turnright(1020);
  drivereverse(200);
  clampunlock();
  */

}

void autonomous(void) {
  switch(autono){
    case 0:
    AWP();
    break;
    case 1:
    redright();
    break;
    case 2:
    Skills();
    break;
    case 3:
    Normalleft();
    break;
  }

}

void usercontrol(void) {
  // User control code here, inside the loop
  //drivetrain
  while (1) {
    mFrontRight.spin(forward, (Controller1.Axis2.position(pct)), pct);
    mMidRight.spin(forward, (Controller1.Axis2.position(pct)), pct);
    mBackRight.spin(forward, (Controller1.Axis2.position(pct)), pct);
    mMidLeft.spin(forward, (Controller1.Axis3.position(pct)), pct);
    mFrontLeft.spin(forward, (Controller1.Axis3.position(pct)), pct);
    mBackLeft.spin(forward, (Controller1.Axis3.position(pct)), pct);

  //intake system
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


  //clamp
  Controller1.ButtonX.pressed(toggleClamp);

    //flipper
    if (Controller1.ButtonR1.pressing()) {
      mflipper.spin(forward, 100, percent);
    }
    else if (Controller1.ButtonR2.pressing()) {
      mflipper.spin(reverse, 100, percent);
    }
    else{
      mfrontintake.stop(hold);
      mintake.stop(hold);
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

