#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RightMotorA = motor(PORT3, ratio18_1, false);
motor RightMotorB = motor(PORT11, ratio18_1, false);
motor_group Right = motor_group(RightMotorA, RightMotorB);
inertial Inertial = inertial(PORT21);
motor LeftMotorA = motor(PORT8, ratio18_1, true);
motor LeftMotorB = motor(PORT16, ratio18_1, true);
motor_group Left = motor_group(LeftMotorA, LeftMotorB);
motor Left3 = motor(PORT19, ratio18_1, true);
motor Right3 = motor(PORT12, ratio18_1, false);
motor CataMotorA = motor(PORT9, ratio36_1, false);
motor CataMotorB = motor(PORT10, ratio36_1, true);
motor_group Cata = motor_group(CataMotorA, CataMotorB);
distance LowIntakeDist = distance(PORT17);
motor Intake = motor(PORT2, ratio6_1, false);
digital_out RightFlap = digital_out(Brain.ThreeWirePort.D);
digital_out LeftFlap = digital_out(Brain.ThreeWirePort.E);
rotation Rotation = rotation(PORT20, false);
digital_out LeftClimb = digital_out(Brain.ThreeWirePort.G);
digital_out RightClimb = digital_out(Brain.ThreeWirePort.F);
distance HighIntakeDist = distance(PORT5);
digital_out BlockerLeft = digital_out(Brain.ThreeWirePort.C);
digital_out BlockerRight = digital_out(Brain.ThreeWirePort.A);
optical LineSense = optical(PORT6);

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