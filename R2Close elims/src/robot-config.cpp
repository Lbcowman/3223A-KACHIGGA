#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RightMotorA = motor(PORT6, ratio18_1, false);
motor RightMotorB = motor(PORT3, ratio18_1, false);
motor_group Right = motor_group(RightMotorA, RightMotorB);
inertial Inertial = inertial(PORT21);
motor LeftMotorA = motor(PORT2, ratio18_1, true);
motor LeftMotorB = motor(PORT1, ratio18_1, true);
motor_group Left = motor_group(LeftMotorA, LeftMotorB);
motor Left3 = motor(PORT16, ratio18_1, true);
motor Right3 = motor(PORT13, ratio18_1, false);
motor CataMotorA = motor(PORT10, ratio36_1, true);
motor CataMotorB = motor(PORT4, ratio36_1, false);
motor_group Cata = motor_group(CataMotorA, CataMotorB);
distance LowIntakeDist = distance(PORT19);
motor Intake = motor(PORT12, ratio6_1, false);
digital_out RightFlap = digital_out(Brain.ThreeWirePort.G);
digital_out LeftFlap = digital_out(Brain.ThreeWirePort.H);
rotation Rotation = rotation(PORT17, false);
digital_out LeftClimb = digital_out(Brain.ThreeWirePort.E);
digital_out RightClimb = digital_out(Brain.ThreeWirePort.F);
distance HighIntakeDist = distance(PORT8);
digital_out BlockerLeft = digital_out(Brain.ThreeWirePort.C);
digital_out BlockerRight = digital_out(Brain.ThreeWirePort.D);
optical LineSense = optical(PORT5);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}