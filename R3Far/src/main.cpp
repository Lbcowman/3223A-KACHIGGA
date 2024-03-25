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
// Right                motor_group   6, 5            
// Inertial2            inertial      21              
// Left                 motor_group   10, 19          
// Left3                motor         9               
// Right3               motor         11              
// Puncher              motor_group   8, 12           
// Intake               motor         20              
// RightFlap            digital_out   C               
// LeftFlap             digital_out   A               
// HangDown1            digital_out   D               
// Park                 digital_out   H               
// Inertial1            inertial      7               
// Inertial3            inertial      17              
// HangDown2            digital_out   G               
// HangUp1              digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"
#include "cmath"
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
  int SlowPCT = 99;
  int SlowPosition = 25;
  float straightSlowPosition = 1.7;
  float PositionDegrees;
  timer TimeOut;
  float TimeOutsec = 1000;
  bool l1Hold = false;
  int loadSpeed = 80;
  int cataWait = 0;
  std::string intakeMode;
  std::string cataMode;
  bool shoot = false;
  int TriballHeight = 110;
  int lineBrightness = 30;
  int deadInertial = 0; // a count for the amount of unplugged inertial sensors
  float diff1;
  float diff2;
  float diff3;


// Functions
  void straight() {
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

  void straightStep() {
    // This is the stright drive block: Variables are DriveDistanceCM and DriveSpeedPCT
    degreesToRotate = ((360 * DriveDistanceIN) / circumference) * 0.6; 
    straightSlowPosition = ((360 * straightSlowPosition) / circumference) * 0.6; 
    //All calculations are complete. Start the rest of the program.
    //Set the velocity of the left and right motor. This command will not make the motor spin.
    Left.setVelocity(DriveSpeedPCT, percent); 
    Right.setVelocity(DriveSpeedPCT, percent);
    Left3.setVelocity(DriveSpeedPCT, percent); 
    Right3.setVelocity(DriveSpeedPCT, percent);
    TimeOut.clear();
    //Rotate the Left and Right Motor for degreesToRotate. 
    Left.spinFor(forward, degreesToRotate - straightSlowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false); 
    Right.spinFor(forward, degreesToRotate - straightSlowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false);
    Left3.spinFor(forward, degreesToRotate - straightSlowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false); 
    Right3.spinFor(forward, degreesToRotate - straightSlowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false);
    waitUntil((Left.isDone() && Right.isDone()) || (TimeOut >= (TimeOutsec*1000)));
    Left.setVelocity(SlowTurn, percent); 
    Right.setVelocity(SlowTurn, percent);
    Left3.setVelocity(SlowTurn, percent); 
    Right3.setVelocity(SlowTurn, percent);
    //Rotate the Left and Right Motor for degreesToRotate. 
    Left.spinFor(forward, straightSlowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false); 
    Right.spinFor(forward, straightSlowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false);
    Left3.spinFor(forward, straightSlowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false); 
    Right3.spinFor(forward, straightSlowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false);
    waitUntil((Left.isDone() && Right.isDone()) || (TimeOut >= (TimeOutsec*1000)));
    Right.stop(hold);
    Left.stop(hold);
    Right3.stop(hold);
    Left3.stop(hold);
    TimeOutsec=1000;
  }

  void straightStep(int slowPosition, int slowSpeed) {
    // This is the stright drive block: Variables are DriveDistanceCM and DriveSpeedPCT
    degreesToRotate = ((360 * DriveDistanceIN) / circumference) * 0.6; 
    slowPosition = ((360 * slowPosition) / circumference) * 0.6; 
    //All calculations are complete. Start the rest of the program.
    //Set the velocity of the left and right motor. This command will not make the motor spin.
    Left.setVelocity(DriveSpeedPCT, percent); 
    Right.setVelocity(DriveSpeedPCT, percent);
    Left3.setVelocity(DriveSpeedPCT, percent); 
    Right3.setVelocity(DriveSpeedPCT, percent);
    TimeOut.clear();
    //Rotate the Left and Right Motor for degreesToRotate. 
    Left.spinFor(forward, degreesToRotate - slowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false); 
    Right.spinFor(forward, degreesToRotate - slowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false);
    Left3.spinFor(forward, degreesToRotate - slowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false); 
    Right3.spinFor(forward, degreesToRotate - slowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false);
    waitUntil((Left.isDone() && Right.isDone()) || (TimeOut >= (TimeOutsec*1000)));
    Left.setVelocity(slowSpeed, percent); 
    Right.setVelocity(slowSpeed, percent);
    Left3.setVelocity(slowSpeed, percent); 
    Right3.setVelocity(slowSpeed, percent);
    //Rotate the Left and Right Motor for degreesToRotate. 
    Left.spinFor(forward, slowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false); 
    Right.spinFor(forward, slowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false);
    Left3.spinFor(forward, slowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false); 
    Right3.spinFor(forward, slowPosition * (degreesToRotate/fabs(degreesToRotate)), degrees, false);
    waitUntil((Left.isDone() && Right.isDone()) || (TimeOut >= (TimeOutsec*1000)));
    Right.stop(hold);
    Left.stop(hold);
    Right3.stop(hold);
    Left3.stop(hold);
    TimeOutsec=1000;
  }

  int AutoHang(){

    wait(104.9,sec);
    HangDown1.set(true);
    HangDown2.set(true);
    return 0;
  }

  float Gyro(std::string reading){
    float angleSum = 0; // variable for the angle as it is totaled

      if (!Inertial1.installed() && diff1 < 9000){ deadInertial++; diff1 = 9999;} // decides if any sensors are unplugged or bad, if so add one to the count and 
      if (!Inertial2.installed() && diff2 < 9000){ deadInertial++; diff2 = 9999;} // set its difference really high so that it will be left out of the other 2 are ok
      if (!Inertial3.installed() && diff3 < 9000){ deadInertial++; diff3 = 9999;}

    if (reading == "rotation"){ // if user is trying to read from the rotation reading of the sensors
      angleSum = (Inertial1.rotation(deg) + Inertial2.rotation(deg) + Inertial3.rotation(deg))/3; // temporarily sets the angle sum to the average of all inertials

      if (diff1 < 9000) diff1 = fabs(angleSum - fabs(Inertial1.rotation(degrees))); // finds the difference between the average of all 3 and the individual sensor
      if (diff2 < 9000) diff2 = fabs(angleSum - fabs(Inertial2.rotation(degrees)));
      if (diff3 < 9000) diff3 = fabs(angleSum - fabs(Inertial3.rotation(degrees)));

      // if less than 2 sensors are bad then use these checks
      if(diff1 > diff2 && diff1 > diff3 && deadInertial < 2) angleSum = (Inertial2.rotation(deg) + Inertial3.rotation(deg)); // this finds the outlier of the 3
      if(diff2 > diff1 && diff2 > diff3 && deadInertial < 2) angleSum = (Inertial1.rotation(deg) + Inertial3.rotation(deg)); // of the three sensors and finds
      if(diff3 > diff1 && diff3 > diff2 && deadInertial < 2) angleSum = (Inertial1.rotation(deg) + Inertial2.rotation(deg)); // the total of the 2 best options

      // if 2 sensors are bad then use these checks
      if(diff2 == 9999 && diff3 == 9999 && deadInertial == 2) angleSum = Inertial1.rotation(deg); // this will find both of the bad inertial sensors and 
      if(diff1 == 9999 && diff3 == 9999 && deadInertial == 2) angleSum = Inertial2.rotation(deg); // set the total to the 1 inertial that is good
      if(diff1 == 9999 && diff2 == 9999 && deadInertial == 2) angleSum = Inertial3.rotation(deg);

    } else { // this else clause is a copy of the if clause, reading the heading instead of the inertial look back to clarify
      angleSum = (Inertial1.heading(deg) + Inertial2.heading(deg) + Inertial3.heading(deg))/3; // temporarily sets the angle sum to the average of all inertials
  
      if (diff1 < 9000) diff1 = fabs(angleSum - fabs(Inertial1.heading(degrees))); // finds the difference between the average of all 3 and the individual sensor
      if (diff2 < 9000) diff2 = fabs(angleSum - fabs(Inertial2.heading(degrees)));
      if (diff3 < 9000) diff3 = fabs(angleSum - fabs(Inertial3.heading(degrees)));

      if(diff1 > diff2 && diff1 > diff3 && deadInertial  == 0) angleSum = (Inertial2.heading(deg) + Inertial3.heading(deg));
      if(diff2 > diff1 && diff2 > diff3 && deadInertial == 0) angleSum = (Inertial1.heading(deg) + Inertial3.heading(deg));
      if(diff3 > diff1 && diff3 > diff2 && deadInertial == 0) angleSum = (Inertial1.heading(deg) + Inertial2.heading(deg));

      if (deadInertial == 1 && (
        (fabs(Inertial1.heading(deg)-Inertial2.heading(deg)) > 180 && !(diff3>9000)) || 
        (fabs(Inertial3.heading(deg)-Inertial1.heading(deg)) > 180 && !(diff2>9000)) || 
        (fabs(Inertial2.heading(deg)-Inertial3.heading(deg)) > 180 && !(diff1>9000)) )){

        if (diff3 == 9999 && fabs(Inertial1.heading(deg)-Inertial2.heading(deg)) > 180) angleSum = (Inertial1.heading(deg) + Inertial2.heading(deg))/2+180;
        else if (diff2 == 9999 && fabs(Inertial3.heading(deg)-Inertial1.heading(deg)) > 180) angleSum = (Inertial1.heading(deg) + Inertial3.heading(deg))/2+180;
        else if (diff1 == 9999 && fabs(Inertial2.heading(deg)-Inertial3.heading(deg)) > 180) angleSum = (Inertial2.heading(deg) + Inertial3.heading(deg))/2+180;
        while (angleSum > 360.0){ angleSum -= 360;}
        return angleSum;
      } else if (deadInertial == 1 && !(
        (fabs(Inertial1.heading(deg)-Inertial2.heading(deg)) > 180 && !(diff3>9000)) || 
        (fabs(Inertial3.heading(deg)-Inertial1.heading(deg)) > 180 && !(diff2>9000)) || 
        (fabs(Inertial2.heading(deg)-Inertial3.heading(deg)) > 180 && !(diff1>9000)) )){

        if(!(diff1>9000)) return (Inertial2.heading(deg) + Inertial3.heading(deg))/2; // this finds the outlier of the 3
        if(!(diff2>9000)) return (Inertial1.heading(deg) + Inertial3.heading(deg))/2; // of the three sensors and finds
        if(!(diff3>9000)) return (Inertial1.heading(deg) + Inertial2.heading(deg))/2; // the total of the 2 best options

      }


      if(!(diff1>9000) && deadInertial == 2) return Inertial1.heading(deg);
      if(!(diff2>9000) && deadInertial == 2) return Inertial2.heading(deg);
      if(!(diff3>9000) && deadInertial == 2) return Inertial3.heading(deg);

    }
    // if all 3 sensors are bad use this
    if(deadInertial == 3){ // if 3 sensors are bad, this will use the straight function to jerk the robot back and forth until either the program ends or a rotation becomes unplugged
      waitUntil(Inertial1.rotation(deg) != 0.00 || Inertial2.rotation(deg) != 0.00 || Inertial3.rotation(deg) != 0.00); // drives forward and backward until an inertial get plugged in
      return Gyro(reading); // once at least 1 sensor gets a reading, it reruns the function and returns the value
    }else if (deadInertial == 2) return angleSum; // outputs the single value
    else return angleSum / 2; // outputs the average of the two most valid values
  }

  void Punch(){
    Puncher.setVelocity(loadSpeed, pct);
    Puncher.spin(fwd);
    waitUntil(!Controller1.ButtonL1.pressing());
    Puncher.stop(coast);
  }

  void RevPunch(){
    Puncher.setVelocity(20, pct);
    Puncher.spin(reverse);
    waitUntil(Controller1.ButtonUp.pressing());
    Puncher.stop(coast);
  }

  int Intaker(){
    while(1){
      if (Controller1.ButtonR2.pressing()){
        Intake.setMaxTorque(100, pct);
        Intake.setVelocity(600, rpm);
        Intake.spin(reverse);
      } else if (Controller1.ButtonR1.pressing()){
        Intake.setMaxTorque(70, pct);
        Intake.setVelocity(600, rpm);
        Intake.spin(fwd);
      } else{
        Intake.setMaxTorque(20, pct);
        Intake.setVelocity(100, rpm);
        Intake.spin(fwd);
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
      if (intakeMode == "intake"){
        Intake.setMaxTorque(70, pct);
        Intake.setVelocity(600, rpm);
      } 
      if (intakeMode == "hold"){
        Intake.setMaxTorque(10, pct);
        Intake.setVelocity(100, rpm);
        Intake.spin(fwd);
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

  void HangUp(){
      HangDown1.set(false);
      HangDown2.set(false);
      HangUp1.set(true);
  }

  void HangDown(){
      HangDown1.set(true);
      HangDown2.set(true);
      HangUp1.set(false);
  }

  void HangTog(){
    if (!HangUp1.value()){
      HangUp();
    } else{
      HangDown();
    }
    waitUntil(!Controller1.ButtonRight.pressing());
  }

  void ParkUp(){
      Park.set(true);
  }

  void ParkDown(){
      Park.set(false);
  }

  void ParkTog(){
    Park.set(!Park.value());
    waitUntil(!Controller1.ButtonY.pressing());
  }

  //flap Controls
    void FlapsTog(){
      if (LeftFlap.value() || RightFlap.value()){
        RightFlap.set(false);
        LeftFlap.set(false);
      } else {
        RightFlap.set(true);
        LeftFlap.set(true);
      }
      waitUntil(!Controller1.ButtonL2.pressing());
    }

    void FlapsHold(){
        RightFlap.set(true);
        LeftFlap.set(true);
        waitUntil(!Controller1.ButtonL2.pressing());
        RightFlap.set(false);
        LeftFlap.set(false);
    }

    void LeftFlapHold(){
      RightFlap.set(false);
      LeftFlap.set(true);
      waitUntil(!Controller1.ButtonDown.pressing());
      LeftFlap.set(RightFlap.value());
    }

    void RightFlapHold(){
      LeftFlap.set(false);
      RightFlap.set(true);
      waitUntil(!Controller1.ButtonB.pressing());
      RightFlap.set(LeftFlap.value());
    }

    void RightFlapTog(){
      RightFlap.set(!RightFlap.value());
    }

    void LeftFlapTog(){
      LeftFlap.set(!LeftFlap.value());
    }
  //

  int Print(){
    while (1) {

      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      //display inertial values
        Brain.Screen.print("Headings: ");
        Brain.Screen.newLine();
        Brain.Screen.print("1: %.1lf", Inertial1.heading(degrees));
        Brain.Screen.print(" | 2: %.1lf", Inertial2.heading(degrees));
        Brain.Screen.print(" | 3: %.1lf", Inertial3.heading(degrees));
        Brain.Screen.newLine();
        Brain.Screen.print("Rotations: ");
        Brain.Screen.newLine();
        Brain.Screen.print("1: %.1lf", Inertial1.rotation(degrees));
        Brain.Screen.print(" | 2: %.1lf", Inertial2.rotation(degrees));
        Brain.Screen.print(" | 3: %.1lf", Inertial3.rotation(degrees));
        Brain.Screen.newLine();
        //* 
        Brain.Screen.print("Gyro Output: ");
        Brain.Screen.newLine();
        Brain.Screen.print("Heading: %.1lf", Gyro("heading"));
        Brain.Screen.print(" | Rotation: %.1lf", Gyro("rotation"));
        Brain.Screen.newLine();
        Brain.Screen.print("Dead Inertials: ");
        Brain.Screen.newLine();
        Brain.Screen.print("1: %.1lf", diff1);
        Brain.Screen.print(" | 2: %.1lf", diff2);
        Brain.Screen.print(" | 3: %f", diff3);
        Brain.Screen.print(" | num: %d", deadInertial);
        Brain.Screen.newLine();

        /*
        Brain.Screen.print("Left: ");
        Brain.Screen.newLine();
        Brain.Screen.print("Group: %.1lf", Left.temperature(pct));
        Brain.Screen.print(" | Single: %.1lf", Left3.temperature(pct));
        Brain.Screen.newLine();

        Brain.Screen.print("Right: ");
        Brain.Screen.newLine();
        Brain.Screen.print("Group: %.1lf", Right.temperature(pct));
        Brain.Screen.print(" | Single: %.1lf", Right3.temperature(pct));
        Brain.Screen.newLine();
        //*/
        wait(250,msec);
    }
  }

  void Turn() {
    Inertial1.setRotation(0, degrees);   
    Inertial2.setRotation(0, degrees); 
    Inertial3.setRotation(0, degrees); 
    Left.setVelocity(DriveSpeedPCT, percent); 
    Right.setVelocity(DriveSpeedPCT, percent);
    Left3.setVelocity(DriveSpeedPCT, percent); 
    Right3.setVelocity(DriveSpeedPCT, percent); 
    TimeOut.clear();
    //turns left
    if (PositionDegrees<0){
      // calculate incremental degrees from haeding if an absolute Turn 
        PositionDegrees = -PositionDegrees - Gyro("heading");
        if (PositionDegrees > 0) PositionDegrees -= 360;
      //turn left
      Left.spin(reverse); 
      Right.spin(forward);
      Left3.spin(reverse); 
      Right3.spin(forward);
      //wait until close to stop
      waitUntil((Gyro("rotation") <= (PositionDegrees-PositionDegrees * (SlowPCT * .01))) or (TimeOut >= (TimeOutsec*  1000)));
      // set motor speeds slow 
      Left.setVelocity(-SlowTurn, percent); 
      Right.setVelocity(SlowTurn, percent);
      Left3.setVelocity(-SlowTurn, percent); 
      Right3.setVelocity(SlowTurn, percent);
      //wait until stop
      waitUntil((Gyro("rotation") <= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    //turns right
    } else {
      // calculate incremental degrees from haeding if an absolute Turn 
        PositionDegrees = PositionDegrees - Inertial1.heading(deg);
        if (PositionDegrees < 0) PositionDegrees += 360;
    //turn Right
      Left.spin(forward); 
      Right.spin(reverse);  
      Left3.spin(forward); 
      Right3.spin(reverse);
      //wait until close to stop
      waitUntil((Inertial1.rotation(deg) >= (PositionDegrees-PositionDegrees * (SlowPCT * .01)))  || (TimeOut >= (TimeOutsec * 1000)));
      // set motor speeds slow 
      Left.setVelocity(SlowTurn, percent); 
      Right.setVelocity(-SlowTurn, percent);
      Left3.setVelocity(SlowTurn, percent); 
      Right3.setVelocity(-SlowTurn, percent);
      //wait until stop
      waitUntil((Inertial1.rotation(deg) >= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    }
    Left.stop(hold);
    Right.stop(hold);
    Left3.stop(hold);
    Right3.stop(hold);
    TimeOutsec = 1000;
  }

  void Turn(int slowPosition, int slowSpeed) {
    Inertial1.setRotation(0, degrees);   
    Inertial2.setRotation(0, degrees); 
    Inertial3.setRotation(0, degrees); 
    Left.setVelocity(DriveSpeedPCT, percent); 
    Right.setVelocity(DriveSpeedPCT, percent);
    Left3.setVelocity(DriveSpeedPCT, percent); 
    Right3.setVelocity(DriveSpeedPCT, percent); 
    TimeOut.clear();
    //turns left
    if (PositionDegrees<0){
      // calculate incremental degrees from haeding if an absolute Turn 
        PositionDegrees = -PositionDegrees - Inertial1.heading(deg);
        while (PositionDegrees > 0) PositionDegrees -= 360;
      //turn left
      Left.spin(reverse); 
      Right.spin(forward);
      Left3.spin(reverse); 
      Right3.spin(forward);
      //wait until close to stop
      waitUntil((Inertial1.rotation(deg) <= (PositionDegrees+slowPosition)) or (TimeOut >= (TimeOutsec*  1000)));
      // set motor speeds slow 
      Left.setVelocity(-slowSpeed, percent); 
      Right.setVelocity(slowSpeed, percent);
      Left3.setVelocity(-slowSpeed, percent); 
      Right3.setVelocity(slowSpeed, percent);
      //wait until stop
      waitUntil((Inertial1.rotation(deg) <= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    //turns right
    } else {
      // calculate incremental degrees from haeding if an absolute Turn 
        PositionDegrees = PositionDegrees - Inertial1.heading(deg);
        while (PositionDegrees < 0) PositionDegrees += 360;
    //turn Right
      Left.spin(forward); 
      Right.spin(reverse);  
      Left3.spin(forward); 
      Right3.spin(reverse);
      //wait until close to stop
      waitUntil((Inertial1.rotation(deg) >= (PositionDegrees-slowPosition))  || (TimeOut >= (TimeOutsec * 1000)));
      // set motor speeds slow 
      Left.setVelocity(slowSpeed, percent); 
      Right.setVelocity(-slowSpeed, percent);
      Left3.setVelocity(slowSpeed, percent); 
      Right3.setVelocity(-slowSpeed, percent);
      //wait until stop
      waitUntil((Inertial1.rotation(deg) >= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    }
    Left.stop();
    Right.stop();
    Left3.stop();
    Right3.stop();
    TimeOutsec = 1000;
  }

  void TurnSingle() {
    Inertial1.setRotation(0, degrees);   
    Inertial2.setRotation(0, degrees); 
    Inertial3.setRotation(0, degrees); 
    Left.setVelocity(DriveSpeedPCT, percent); 
    Right.setVelocity(DriveSpeedPCT, percent);
    Left3.setVelocity(DriveSpeedPCT, percent); 
    Right3.setVelocity(DriveSpeedPCT, percent); 
    TimeOut.clear();
    //turns left
    if (PositionDegrees<0){
      // calculate incremental degrees from haeding if an absolute Turn 
        PositionDegrees = -PositionDegrees - Gyro("heading");
        while (PositionDegrees > 0) PositionDegrees -= 360;
      //turn left
      Right.spin(forward);
      Right3.spin(forward);
      //wait until close to stop
      waitUntil((Gyro("rotation") <= (PositionDegrees+SlowPosition)) or (TimeOut >= (TimeOutsec*  1000)));
      // set motor speeds slow 
      Right.setVelocity(SlowTurn*4, percent);
      Right3.setVelocity(SlowTurn*4, percent);
      //wait until stop
      waitUntil((Gyro("rotation") <= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    //turns right
    } else {
      // calculate incremental degrees from haeding if an absolute Turn 
        PositionDegrees = PositionDegrees - Gyro("heading");
        while (PositionDegrees < 0) PositionDegrees += 360;
    //turn Right
      Left.spin(forward); 
      Left3.spin(forward); 
      //wait until close to stop
      waitUntil((Gyro("rotation") >= (PositionDegrees-SlowPosition))  || (TimeOut >= (TimeOutsec * 1000)));
      // set motor speeds slow 
      Left.setVelocity(SlowTurn*4, percent); 
      Left3.setVelocity(SlowTurn*4, percent); 
      //wait until stop
      waitUntil((Gyro("rotation") >= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    }
    Left.stop();
    Right.stop();
    Left3.stop();
    Right3.stop();
    TimeOutsec = 1000;
  }

  void TurnSingle(int slowPosition, int slowSpeed) {
    Inertial1.setRotation(0, degrees);   
    Inertial2.setRotation(0, degrees); 
    Inertial3.setRotation(0, degrees); 
    Left.stop(hold);
    Right.stop(hold);
    Left3.stop(hold);
    Right3.stop(hold);
    Left.setVelocity(DriveSpeedPCT, percent); 
    Right.setVelocity(DriveSpeedPCT, percent);
    Left3.setVelocity(DriveSpeedPCT, percent); 
    Right3.setVelocity(DriveSpeedPCT, percent); 
    TimeOut.clear();
    //turns left
    if (PositionDegrees<0){
      // calculate incremental degrees from haeding if an absolute Turn 
        PositionDegrees = -PositionDegrees - Gyro("heading");
        while (PositionDegrees > 0) PositionDegrees -= 360;
      //turn left
      Right.spin(forward);
      Right3.spin(forward);
      //wait until close to stop
      waitUntil((Gyro("rotation") <= (PositionDegrees+SlowPosition)) or (TimeOut >= (TimeOutsec*  1000)));
      // set motor speeds slow 
      Right.setVelocity(slowSpeed*4, percent);
      Right3.setVelocity(slowSpeed*4, percent);
      //wait until stop
      waitUntil((Gyro("rotation") <= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    //turns right
    } else {
      // calculate incremental degrees from haeding if an absolute Turn 
        PositionDegrees = PositionDegrees - Gyro("heading");
        while (PositionDegrees < 0) PositionDegrees += 360;
    //turn Right
      Left.spin(forward); 
      Left3.spin(forward); 
      //wait until close to stop
      waitUntil((Gyro("rotation") >= (PositionDegrees-SlowPosition))  || (TimeOut >= (TimeOutsec * 1000)));
      // set motor speeds slow 
      Left.setVelocity(slowSpeed*4, percent); 
      Left3.setVelocity(slowSpeed*4, percent); 
      //wait until stop
      waitUntil((Gyro("rotation") >= PositionDegrees) || (TimeOut >= (TimeOutsec * 1000)));
    }
    Left.stop(hold);
    Right.stop(hold);
    Left3.stop(hold);
    Right3.stop(hold);
    TimeOutsec = 1000;
  }


void pre_auton(void) {
  vexcodeInit();
  
  LeftFlap = false;
  RightFlap = false;

  Inertial1.calibrate();
  Inertial2.calibrate();
  Inertial3.calibrate();

  waitUntil(!Inertial1.isCalibrating() && !Inertial1.isCalibrating() && !Inertial1.isCalibrating());
}

void autonomous(void) { 

    DriveSpeedPCT = 50; //Drive Speed %
  PositionDegrees = 90;
  Turn();

  wait(2,sec);

  PositionDegrees = -270;
  Turn();

  wait(2,sec);

  PositionDegrees = 360; 
  Turn();

  /* PositionDegrees = -350; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
  Turn();
  wait(1,sec);

   PositionDegrees = 350; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
  Turn(1000,3);


  task Intake = task (Antaker);


    DriveDistanceIN = 5; //Drive Distance CM
    DriveSpeedPCT = 40; //Drive Speed %
    TimeOutsec=8; 
  straight();
    RightFlap = true;
    

 PositionDegrees = -294; //Drive Distance CM
    DriveSpeedPCT = 55; //Drive Speed %
  TurnSingle();

 RightFlap = false;

 
     



       DriveDistanceIN = 40; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec=.7; 
  straight();

    DriveDistanceIN = -8; //Drive Distance CM
    DriveSpeedPCT = 50; //Drive Speed %
    TimeOutsec=2; 
  straight();




   PositionDegrees = -203; //Drive Distance CM
    DriveSpeedPCT = 23; //Drive Speed %
  Turn();

   intakeMode = "cata";



    DriveDistanceIN = 47; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec=5; 
  straight();

     intakeMode = "hold";


  wait(200, msec);

   PositionDegrees = 328; //Drive Distance CM
    DriveSpeedPCT = 23; //Drive Speed %
  Turn();

   intakeMode = "reverse";

    DriveDistanceIN = 19; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec=5; 
  straight();

    PositionDegrees = -215; //Drive Distance CM
    DriveSpeedPCT = 22; //Drive Speed %
  Turn();

  intakeMode = "cata";

     DriveDistanceIN =23; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec=5; 
  straight();

  intakeMode = "hold";

  wait(200, msec);

  PositionDegrees = 1; //Drive Distance CM
    DriveSpeedPCT = 22; //Drive Speed %
  Turn();
 
     DriveDistanceIN =-3; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec=.5; 
  straight();

   LeftFlap = true;
  RightFlap = true;

  intakeMode = "reverse";

    DriveDistanceIN = 40; //Drive Distance CM
    DriveSpeedPCT = 100; //Drive Speed %
    TimeOutsec=1; 
  straight();

  LeftFlap = false;
  RightFlap = false;

    DriveDistanceIN = -15; //Drive Distance CM
    DriveSpeedPCT = 60; //Drive Speed %
    TimeOutsec=3; 
  straight();
  */
}
void usercontrol(void) {
  autonomous();
  /*
  intakeMode = "stop";
  intakeMode = "break";
  cataMode = "break";
  RightFlap = false;
  intakeMode = "somethingelse";   
  cataMode = "somethingelse";
  task HangTask = task (AutoHang);
  task IntakeTask = task(Intaker);
  task PrintTask = task(Print);

  // Register callbacks to controller button 'pressed' events.
    Controller1.ButtonY.pressed(ParkTog);
    Controller1.ButtonRight.pressed(HangTog);
    Controller1.ButtonB.pressed(RightFlapHold);
    Controller1.ButtonDown.pressed(LeftFlapHold);
    Controller1.ButtonL2.pressed(FlapsHold);
    Controller1.ButtonL1.pressed(Punch);
    Controller1.ButtonUp.pressed(RevPunch);

    Left.setStopping(coast);
    Left3.setStopping(coast);
    Right.setStopping(coast);
    Right3.setStopping(coast);
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
    Left.setStopping(coast);
    Left3.setStopping(coast);
    Right.setStopping(coast);
    Right3.setStopping(coast);
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
    Left.setStopping(coast);
    Left3.setStopping(coast);
    Right.setStopping(coast);
    Right3.setStopping(coast);
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
  } //*/
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