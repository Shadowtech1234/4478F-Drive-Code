using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor mFrontRight;
extern motor mMidRight;
extern motor mBackRight;
extern motor mMidLeft;
extern motor mFrontLeft;
extern motor mBackLeft;
extern motor arm;
extern motor Claw;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );