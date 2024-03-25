using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group Right;
extern inertial Inertial;
extern motor_group Left;
extern motor Left3;
extern motor Right3;
extern motor_group Cata;
extern distance LowIntakeDist;
extern motor Intake;
extern digital_out RightFlap;
extern digital_out LeftFlap;
extern rotation Rotation;
extern digital_out LeftClimb;
extern digital_out RightClimb;
extern distance HighIntakeDist;
extern digital_out BlockerLeft;
extern digital_out BlockerRight;
extern optical LineSense;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );