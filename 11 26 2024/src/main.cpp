#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
controller Controller1 = controller(primary);
motor mFrontRight = motor(PORT16, ratio18_1, false);

motor mMidRight = motor(PORT3, ratio18_1, false);

motor mBackRight = motor(PORT11, ratio18_1, false);

motor mMidLeft = motor(PORT5, ratio18_1, false);

motor mFrontLeft = motor(PORT7, ratio18_1, false);

motor mBackLeft = motor(PORT4, ratio18_1, false);

motor mintake = motor(PORT19, ratio18_1, false);

motor mfrontintake = motor(PORT6, ratio18_1, false);

digital_out RightN = digital_out(Brain.ThreeWirePort.A);
digital_out LeftN = digital_out(Brain.ThreeWirePort.B);


// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration
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

int xPosition();
int yPosition();



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


void intakeup(int waittime){
  mintake.spinFor(forward, waittime, degrees, true);
}

void intakedown(int waittime){
  mintake.spinFor(reverse, waittime, degrees, true);
}

void frontintakeup(int waittime){
  mfrontintake.spinFor(forward, waittime, degrees, true);
}

void frontintakedown(int waittime){
  mfrontintake.spinFor(reverse, waittime, degrees, true);
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
  vexcodeInit();
  //Brain.Screen.pressed(autonSelection);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Brain.Screen.setPenColor(red);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0, 0, 240, 120);
  Brain.Screen.setCursor(3, 8);
  Brain.Screen.print("Left");
  Brain.Screen.setPenColor(blue);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(240, 0, 240, 120);
  Brain.Screen.setCursor(3, 32);
  Brain.Screen.print("Right");
  Brain.Screen.setPenColor(green);
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(0, 120, 480, 240);
  Brain.Screen.setCursor(3, 32);
  Brain.Screen.print("Skills");
}

void AWPleft(){

}

void AWPright(){

}

void Normal(){
  
}
   
void Skills(){

}

void autonomous(void) {
  switch(autono){
    case 0:
      if (yPosition() <= 120) {
        if (xPosition() <= 240) {
          Brain.Screen.clearScreen();
          Brain.Screen.print("AWP LEFT ACTIVATED");
          AWPleft();
        }
        else {
          Brain.Screen.clearScreen();
          Brain.Screen.print("AWP RIGHT ACTIVATED");
          AWPright();
        }
      }
        
    break;
    case 1:
      Normal();
    break;
    case 2:
      if (yPosition() >= 120) {
        Brain.Screen.clearScreen();
        Brain.Screen.print("AWP LEFT ACTIVATED");
        Skills();
      }
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
      mintake.spin(forward, 100, percent);
    }
    else if (Controller1.ButtonR2.pressing()) {
      mintake.spin(reverse, 100, percent);
    }
    else{
      mintake.stop(hold);
    }

  if (Controller1.ButtonL1.pressing()) {
      mfrontintake.spin(forward, 100, percent);
    }
    else if (Controller1.ButtonL2.pressing()) {
      mfrontintake.spin(reverse, 100, percent);
    }
    else{
      mfrontintake.stop(hold);
    }

  
    if (Controller1.ButtonY.pressing()){
      RightN.set(false);
      LeftN.set(false);
     

      }
      else if (Controller1.ButtonB.pressing()){
      RightN.set(true);
      LeftN.set(true);
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
