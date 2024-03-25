                                                                                                                                                           /*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Authaor:       TVO                                                       */
/*    Created:      10/24/21                                                  */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Right                motor_group   6, 3            
// Inertial             inertial      21              
// Left                 motor_group   2, 1            
// Left3                motor         16              
// Right3               motor         13              
// Cata                 motor_group   10, 4           
// LowIntakeDist        distance      19              
// Intake               motor         12              
// RightFlap            digital_out   G               
// LeftFlap             digital_out   H               
// Rotation             rotation      17              
// LeftClimb            digital_out   E               
// RightClimb           digital_out   F               
// HighIntakeDist       distance      8               
// BlockerLeft          digital_out   C               
// BlockerRight         digital_out   D               
// LineSense            optical       5               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"
using namespace vex;
// A global instance of competition   
competition Competition;
//Define variables.
  double wheelDiameterIN = 3.25; //wheelDiameter is the measurement of a wheel from edge to edge in centimeters.
  double DriveDistanceIN; //travelTarget will define how far we want the robot to move in centimeters.
  //Calculate wheel circumferance: circumference = (wheelDiameter)(PI)
  double circumference = wheelDiameterIN * M_PI; //Note that M_PI is from the math library which is included on line 11.
  double degreesToRotate;
  int DriveSpeedPCT;
  int DegreeAmount;
  int SlowTurn = 3;
  int SlowPosition = 25;
  float PositionDegrees;
  timer TimeOut;
  float TimeOutsec = 1000;
  bool l1Hold = false;
  int loadSpeed = 80;
  int cataWait = 0;
  std::string intakeMode;
  bool shoot = false;
  int TriballHeight = 110;
  int lineBrightness = 30;


// Functions
  void straight(void) {
    // This is the stright drive block: Variables are DriveDistanceCM and DriveSpeedPCT
    degreesToRotate = ((360 * DriveDistanceIN) / circumference) * 0.6; 
    //All calculations are complete. Start the rest of the program.
    //Set the velocity of the left and right motor. This command will not make the motor spin.
    Left.setVelocity(DriveSpeedPCT, percent); 
    Right.setVelocity(DriveSpeedPCT, percent);
    Left3.setVelocity(DriveSpeedPCT, percent); 
    Right3.setVelocity(DriveSpeedPCT, percent);
    TimeOut.clear();
    //Rotate the Left and Right Motor for degreesToRotate. 
    Left.spinFor(forward, degreesToRotate, degrees, false); 
    Right.spinFor(forward, degreesToRotate, degrees, false);
    Left3.spinFor(forward, degreesToRotate, degrees, false); 
    Right3.spinFor(forward, degreesToRotate, degrees, false);
    waitUntil((Left.isDone() && Right.isDone()) or (TimeOut >= (TimeOutsec*1000)));
    Right.stop(brake);
    Left.stop(brake);
    Right3.stop(brake);
    Left3.stop(brake);
    TimeOutsec=1000;
  }

  int AutoHang(){

    wait(104.9,sec);
    RightClimb.set(false);
    LeftClimb.set(false);

    return 0;
  }

  int Intaker(){
    while(1){
      if (Controller1.ButtonL2.pressing()){
        Intake.setMaxTorque(100, pct);
        Intake.setVelocity(600, rpm);
        Intake.spin(reverse);
      } else {
        if (Controller1.ButtonR1.pressing()){
          Intake.setMaxTorque(100, pct);
          Intake.setVelocity(600, rpm);
          Intake.spin(fwd);
        } else{
          if ((LowIntakeDist.objectDistance(mm) < 40) && (HighIntakeDist.objectDistance(mm) > TriballHeight)){
            Intake.spin(fwd);
            Intake.setVelocity(600, rpm);
            Intake.setMaxTorque(3, pct);
          } else if(HighIntakeDist.objectDistance(mm) < TriballHeight - 10){
            Intake.spin(reverse);
            Intake.setVelocity(-50, rpm);
            Intake.setMaxTorque(90, pct);
          } else if(Controller1.ButtonR2.pressing()){
              Intake.setMaxTorque(50, pct);
              Intake.setVelocity(400, rpm);
              Intake.spin(fwd);
          } else {
            Intake.stop(coast);
          }
        }
      }
      wait(20, msec);
    }
    return 0;
  }

  int Antaker(){
    while(1){
      if (intakeMode == "reverse"){
        Intake.setMaxTorque(100, pct);
        Intake.setVelocity(600, rpm);
        Intake.spin(reverse);
      }
      if (intakeMode == "cata"){
        Intake.setMaxTorque(100, pct);
        Intake.setVelocity(500, rpm);
        Intake.spin(fwd);
        wait(350, msec);
        Intake.stop(coast);
      } 
      if (intakeMode == "hold"){
          if ((LowIntakeDist.objectDistance(mm) < 30) && (HighIntakeDist.objectDistance(mm) > TriballHeight)){
            Intake.spin(fwd);
            Intake.setVelocity(600, rpm);
            Intake.setMaxTorque(10, pct);
          } else if(HighIntakeDist.objectDistance(mm) < TriballHeight - 10){
            Intake.spin(reverse);
            Intake.setVelocity(-50, rpm);
            Intake.setMaxTorque(90, pct);
          } else if((LowIntakeDist.objectDistance(mm) > 30) && (HighIntakeDist.objectDistance(mm) > TriballHeight)){
              Intake.setMaxTorque(30, pct);
              Intake.setVelocity(200, rpm);
              Intake.spin(fwd);
          } 
      }
      if(intakeMode == "stop"){
        Intake.stop(coast);
      }
      if(intakeMode == "break"){
        break;
      }
      wait(20, msec);
    }
    return 0;
  }

  void ElevateUp(){
      RightClimb.set(true);
      LeftClimb.set(true);
  }

  void ElevateDown(){
      RightClimb.set(false);
      LeftClimb.set(false);
  }

  void BlockerTog(){
    if (BlockerLeft.value()){
      BlockerLeft.set(false);
      BlockerRight.set(false);
    } else{
      BlockerLeft.set(true);
      BlockerRight.set(true);
    }
  }

  void FlapsDual(){
    if (LeftFlap.value() || RightFlap.value()){
      RightFlap.set(false);
      LeftFlap.set(false);
    } else {
      RightFlap.set(true);
      LeftFlap.set(true);
    }
  }

  void whenControllerLeftPressed(){
    if (LeftFlap.value()){
      LeftFlap.set(false);
    } else {
      LeftFlap.set(true);
    }
  }

  void whenControllerRightPressed(){
    if (RightFlap.value()){
      RightFlap.set(false);
    } else {
      RightFlap.set(true);
    }
  }

  int L1LongPress(){
    while (1) {
      if (Controller1.ButtonL1.pressing()){
        l1Hold = true;
        wait(110, msec);
      } else {
        l1Hold = false;
        wait(20, msec);
      }
    }
    return 0;
  }


  int alwaysOnCata() {
    while(1){
      if (Controller1.ButtonX.pressing() && !(Rotation.angle() < 20)){
        Cata.spin(reverse);
      }else if (l1Hold){
        Cata.setVelocity(loadSpeed, pct);
        Cata.spin(fwd);
      }else{
        if(Rotation.angle() > 281 || Rotation.angle() < 260){
          if (Rotation.angle() < 295){Cata.setVelocity(45, pct);
          }else {Cata.setVelocity(65, pct);}
        Cata.spin(fwd);
        }else{
          Cata.stop(coast);
        }
      }
        if(intakeMode == "break"){
        break;
      }
    }
      return 0;
  }

  int Print(){
    while (1) {

      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      //Print Wheel RPM
      Brain.Screen.print("Heading: ");
      Brain.Screen.print(Inertial.heading(degrees));
      Brain.Screen.newLine();
      Brain.Screen.print("Rotation: ");
      Brain.Screen.print(Inertial.rotation(degrees));
      Brain.Screen.newLine();
      Brain.Screen.print("LineSense Value: ");
      Brain.Screen.print(LineSense.brightness());
      Brain.Screen.newLine();
      Brain.Screen.print("Line Sensed: ");
      Brain.Screen.print((LineSense.brightness() > lineBrightness));
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(4, 1);
      Controller1.Screen.print("cata angle: ");
      Controller1.Screen.print(Rotation.angle());
      wait(300, msec);
    }
    return 0;
  }

  void straightLine(void) {
    LineSense.setLight(ledState::on);
    LineSense.setLightPower(50, pct);
    // This is the stright drive block: Variables are DriveDistanceCM and DriveSpeedPCT
    degreesToRotate = ((360 * DriveDistanceIN) / circumference) * 0.6; 
    //All calculations are complete. Start the rest of the program.
    //Set the velocity of the left and right motor. This command will not make the motor spin.
    Left.setVelocity(DriveSpeedPCT, percent); 
    Right.setVelocity(DriveSpeedPCT, percent);
    Left3.setVelocity(DriveSpeedPCT, percent); 
    Right3.setVelocity(DriveSpeedPCT, percent);
    TimeOut.clear();
    //Rotate the Left and Right Motor for degreesToRotate. 
    Left.spinFor(forward, degreesToRotate, degrees, false); 
    Right.spinFor(forward, degreesToRotate, degrees, false);
    Left3.spinFor(forward, degreesToRotate, degrees, false); 
    Right3.spinFor(forward, degreesToRotate, degrees, false);
    waitUntil((Left.isDone() && Right.isDone()) || (TimeOut >= (TimeOutsec*1000)) || (LineSense.brightness() > lineBrightness));
    Right.stop(brake);
    Left.stop(brake);
    Right3.stop(brake);
    Left3.stop(brake);
    TimeOutsec=1000;
  } 

  void Turn(std::string TurnType) {
    Inertial.setRotation(0, degrees);   
    Left.setVelocity(DriveSpeedPCT, percent); 
    Right.setVelocity(DriveSpeedPCT, percent);
    Left3.setVelocity(DriveSpeedPCT, percent); 
    Right3.setVelocity(DriveSpeedPCT, percent); 
    TimeOut.clear();
    //turns left
    if (PositionDegrees<0){
      // calculate incremental degrees from haeding if an absolute Turn 
      if (TurnType == "Abs") {
        PositionDegrees = -PositionDegrees - Inertial.heading(degrees);
          if (PositionDegrees > 0) {
            PositionDegrees = PositionDegrees - 360;
        }
      }
      //turn left
      Left.spin(reverse); 
      Right.spin(forward);
      Left3.spin(reverse); 
      Right3.spin(forward);
      //wait until close to stop
      waitUntil((Inertial.rotation(degrees) <= (PositionDegrees+SlowPosition)) or (TimeOut >= (TimeOutsec*  1000)));
      // set motor speeds slow 
      Left.setVelocity(-SlowTurn, percent); 
      Right.setVelocity(SlowTurn, percent);
      Left3.setVelocity(-SlowTurn, percent); 
      Right3.setVelocity(SlowTurn, percent);
      //wait until stop
      waitUntil((Inertial.rotation(degrees) <= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    //turns right
    } else {
      // calculate incremental degrees from haeding if an absolute Turn 
      if (TurnType == "Abs") {
        PositionDegrees = PositionDegrees - Inertial.heading(degrees);
        if (PositionDegrees < 0) {
          PositionDegrees = PositionDegrees + 360; 
        }
      }
    //turn Right
      Left.spin(forward); 
      Right.spin(reverse);  
      Left3.spin(forward); 
      Right3.spin(reverse);
      //wait until close to stop
      waitUntil((Inertial.rotation(degrees) >= (PositionDegrees-SlowPosition))  || (TimeOut >= (TimeOutsec * 1000)));
      // set motor speeds slow 
      Left.setVelocity(SlowTurn, percent); 
      Right.setVelocity(-SlowTurn, percent);
      Left3.setVelocity(SlowTurn, percent); 
      Right3.setVelocity(-SlowTurn, percent);
      //wait until stop
      waitUntil((Inertial.rotation(degrees) >= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    }
    Left.stop();
    Right.stop();
    Left3.stop();
    Right3.stop();
    TimeOutsec = 1000;
  }

  void TurnSingle(std::string TurnType) {
    Inertial.setRotation(0, degrees);   
    Left.setVelocity(DriveSpeedPCT, percent); 
    Right.setVelocity(DriveSpeedPCT, percent);
    Left3.setVelocity(DriveSpeedPCT, percent); 
    Right3.setVelocity(DriveSpeedPCT, percent); 
    TimeOut.clear();
    //turns left
    if (PositionDegrees<0){
      // calculate incremental degrees from haeding if an absolute Turn 
      if (TurnType == "Abs") {
        PositionDegrees = -PositionDegrees - Inertial.heading(degrees);
          if (PositionDegrees > 0) {
            PositionDegrees = PositionDegrees - 360;
        }
      }
      //turn left
      Right.spin(forward);
      Right3.spin(forward);
      //wait until close to stop
      waitUntil((Inertial.rotation(degrees) <= (PositionDegrees+SlowPosition)) or (TimeOut >= (TimeOutsec*  1000)));
      // set motor speeds slow 
      Right.setVelocity(SlowTurn*4, percent);
      Right3.setVelocity(SlowTurn*4, percent);
      //wait until stop
      waitUntil((Inertial.rotation(degrees) <= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    //turns right
    } else {
      // calculate incremental degrees from haeding if an absolute Turn 
      if (TurnType == "Abs") {
        PositionDegrees = PositionDegrees - Inertial.heading(degrees);
        if (PositionDegrees < 0) {
          PositionDegrees = PositionDegrees + 360; 
        }
      }
    //turn Right
      Left.spin(forward); 
      Left3.spin(forward); 
      //wait until close to stop
      waitUntil((Inertial.rotation(degrees) >= (PositionDegrees-SlowPosition))  || (TimeOut >= (TimeOutsec * 1000)));
      // set motor speeds slow 
      Left.setVelocity(SlowTurn*4, percent); 
      Left3.setVelocity(SlowTurn*4, percent); 
      //wait until stop
      waitUntil((Inertial.rotation(degrees) >= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    }
    Left.stop();
    Right.stop();
    Left3.stop();
    Right3.stop();
    TimeOutsec = 1000;
  }

void pre_auton(void) {
  vexcodeInit();
  
  LeftFlap = false;
  RightFlap = false;

  Inertial.calibrate();

  waitUntil(!Inertial.isCalibrating());
  task CataTask = task(alwaysOnCata);
}

void autonomous(void) { 
  task PrintTask = task(Print);
  task AntakeTask = task(Antaker);
   task CataTask = task(alwaysOnCata);
  
  LeftFlap = true;

    PositionDegrees = -155; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
  Turn("Abs");

  LeftFlap = false;

    PositionDegrees = -66; //Drive Distance CM
    DriveSpeedPCT = 20; //Drive Speed %
  Turn("Abs");

    cataWait = 700;
  l1Hold = true;
  wait(500, msec);
 l1Hold = false;

     PositionDegrees = -36; //Drive Distance CM
    DriveSpeedPCT = 20; //Drive Speed %
  Turn("Abs");

    DriveDistanceIN = -28; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec=5; 
  straight();

  intakeMode = "cata";

    PositionDegrees = 179; //Drive Distance CM
    DriveSpeedPCT = 20; //Drive Speed %
  Turn("Abs");

    DriveDistanceIN = 17.5; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec=5; 
  straight();

    DriveDistanceIN = -6; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec=5; 
  straight();

    PositionDegrees = -85; //Drive Distance CM
    DriveSpeedPCT = 23; //Drive Speed %
  Turn("Abs");
    
    cataWait = 200;

  l1Hold = true; 
  

  

  DriveDistanceIN = 3; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec=.5; 
  straight();
    l1Hold = false;


    PositionDegrees = -273; // Distance CM
    DriveSpeedPCT = 23; //Drive Speed %
  Turn("Abs");
  RightFlap = true;

    DriveDistanceIN = 21; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec = 1; 
  straight();

 RightFlap = false;

  LeftFlap = true;
  wait(.2, sec);
  LeftFlap = false;



    PositionDegrees = 355; //Drive Distance CM
    DriveSpeedPCT = 23; //Drive Speed %
  Turn("Abs");

    DriveDistanceIN = 63; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec=9; 
  straight();


  LeftFlap = true;

  

  intakeMode = "stop";
  intakeMode = "break";
}
void usercontrol(void) {
  intakeMode = "stop";
  intakeMode = "break";
    RightFlap = false;
  intakeMode = "somethingelse";   
  task HangTask = task (AutoHang);
  task IntakeTask = task(Intaker);
  task PrintTask = task(Print);
 // task ResetTask = task(cataReset);
  task ControllerTask = task(L1LongPress);

// Register callbacks to controller button 'pressed' events.
      Controller1.ButtonY.pressed(FlapsDual);
      Controller1.ButtonB.pressed(ElevateUp);
  Controller1.ButtonLeft.pressed(whenControllerLeftPressed);
  Controller1.ButtonRight.pressed(BlockerTog);
  //Controller1.ButtonL1.pressed(whenControllerL1Pressed);
  //Controller1.ButtonL1.released(whenControllerL1Pressed);
      Controller1.ButtonUp.pressed(whenControllerRightPressed);
      Controller1.ButtonDown.pressed(ElevateDown);

// Deadband stops the motors when Axis values are close to zero.
  int deadband = 5;
// User control code here, inside the loop
  while (1) {
    // Get the velocity percentage of the left motor. (Axis3)
    int leftMotorSpeed = Controller1.Axis3.position(); 

    // Get the velocity percentage of the right motor. (Axis2)
    int rightMotorSpeed = Controller1.Axis2.position();

    // Set the speed of the left motor. If the value is less than the deadband, 
    // set it to zero.
    if (abs(leftMotorSpeed) < deadband) {
      // Set the speed to zero.
      Left.setVelocity(0, percent);
      Left3.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      Left.setVelocity(leftMotorSpeed, percent);
      Left3.setVelocity(leftMotorSpeed, percent);
    }
    // Set the speed of the right motor. If the value is less than the deadband, 
    // set it to zero.
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      Right.setVelocity(0, percent);
      Right3.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      Right.setVelocity(rightMotorSpeed, percent);
      Right3.setVelocity(rightMotorSpeed, percent);
    }
    // Spin both motors in the forward direction.
    Left.spin(forward);
    Right.spin(forward);  
    Left3.spin(forward);
    Right3.spin(forward);

    wait(20, msec);
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