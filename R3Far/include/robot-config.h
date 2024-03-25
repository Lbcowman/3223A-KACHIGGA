using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group Right;
extern inertial Inertial2;
extern motor_group Left;
extern motor Left3;
extern motor Right3;
extern motor_group Puncher;
extern motor Intake;
extern digital_out RightFlap;
extern digital_out LeftFlap;
extern digital_out HangDown1;
extern digital_out Park;
extern inertial Inertial1;
extern inertial Inertial3;
extern digital_out HangDown2;
extern digital_out HangUp1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );