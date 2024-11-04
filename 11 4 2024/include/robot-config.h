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
extern motor mintake;
extern motor mfrontintake;
extern digital_out RightN;
extern digital_out LeftN;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );