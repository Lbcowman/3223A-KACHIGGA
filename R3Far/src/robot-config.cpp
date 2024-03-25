#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RightMotorA = motor(PORT6, ratio6_1, false);
motor RightMotorB = motor(PORT5, ratio6_1, false);
motor_group Right = motor_group(RightMotorA, RightMotorB);
inertial Inertial2 = inertial(PORT21);
motor LeftMotorA = motor(PORT10, ratio6_1, true);
motor LeftMotorB = motor(PORT19, ratio6_1, true);
motor_group Left = motor_group(LeftMotorA, LeftMotorB);
motor Left3 = motor(PORT9, ratio6_1, true);
motor Right3 = motor(PORT11, ratio6_1, false);
motor PuncherMotorA = motor(PORT8, ratio36_1, true);
motor PuncherMotorB = motor(PORT12, ratio36_1, false);
motor_group Puncher = motor_group(PuncherMotorA, PuncherMotorB);
motor Intake = motor(PORT20, ratio6_1, false);
digital_out RightFlap = digital_out(Brain.ThreeWirePort.C);
digital_out LeftFlap = digital_out(Brain.ThreeWirePort.A);
digital_out HangDown1 = digital_out(Brain.ThreeWirePort.D);
digital_out Park = digital_out(Brain.ThreeWirePort.H);
inertial Inertial1 = inertial(PORT7);
inertial Inertial3 = inertial(PORT17);
digital_out HangDown2 = digital_out(Brain.ThreeWirePort.G);
digital_out HangUp1 = digital_out(Brain.ThreeWirePort.B);

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