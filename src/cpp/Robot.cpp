/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "RobotMap.h"

#include <iostream>
#include <SmartDashboard/SmartDashboard.h>
#include <DriverStation.h>

Robot::Robot() 
  : IterativeRobot()
{
  oi = new OI;

  claw = new Claw(
    kClawFrontPwm, kClawRearPwm,
    kClawSwitchDio,
    kPcmArm, kClawRamFwd, kClawRamBwd
  );
  arm = new Lifter(
    kPcmArm, Lifter::Position::kUp,
    kArmFwd, kArmBwd
  );
  lift = new Lifter(
    kPcmBody, Lifter::Position::kDown,
    kLiftFwd, kLiftBwd
  );
}
  

void Robot::RobotInit()
{
  // Sendable Choosers are option boxes sent to the Smart Dashboard,
  // Here we give two choosers options and the objects to return when chosen.

  // Starting Position: on the left or right
  startingPosition.AddDefault(kStartLeft, AutoCtl::StartPos::LEFT);
  startingPosition.AddObject(kStartRight, AutoCtl::StartPos::RIGHT);
  frc::SmartDashboard::PutData("Starting Position", &startingPosition);

  // Target Prefrence: switch, scale, or neither
  targetPreference.AddDefault(kPerfNone, AutoCtl::TargetPerf::NEITHER);
  targetPreference.AddObject(kPerfSwitch, AutoCtl::TargetPerf::SWITCH);
  targetPreference.AddObject(kPerfScale, AutoCtl::TargetPerf::SCALE);
  frc::SmartDashboard::PutData("Target Preference", &targetPreference);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
  drivetrain->Display();
}

void Robot::DisabledInit() {
  drivetrain->ArcadeDrive(0, 0);
}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard.
 */
void Robot::AutonomousInit()
{
  autoCtl = new AutoCtl(
      DriverStation::GetInstance().GetGameSpecificMessage(),
      targetPreference.GetSelected(), startingPosition.GetSelected()
  );
  autoCtl->Start();
}

void Robot::AutonomousPeriodic()
{
  frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit()
{
  // Stop Autonomous should it still be running
  if (autoCtl != nullptr) {
    autoCtl->Cancel();
    autoCtl = nullptr;
  }
  drivetrain->SetSafetyEnabled(true);
}

void Robot::TeleopPeriodic()
{
  double turnMod = kTeleopTurnNormSpeed;
  if (oi->joystick->GetRawButton(kHighSpeedButton))
    turnMod = kTeleopTurnHighSpeed;
  /* get gamepad stick values */
  double forw = -kTeleopDriveSpeed * oi->joystick->GetRawAxis(1); /* positive is forward */
  double turn = +turnMod * oi->joystick->GetRawAxis(2); /* positive is right */

  /* deadband gamepad 10% */
  if (fabs(forw) < 0.10)
    forw = 0;
  if (fabs(turn) < 0.10)
    turn = 0;

  /* drive robot */
  drivetrain->ArcadeDrive(forw, turn);

  /* lift/lower arm */
  if (oi->joystick->GetRawButton(4) && !joystickButton4DBounce
      && (lift->GetPosition() == Lifter::Position::kDown)) { // Y Button
    joystickButton4DBounce = true;
    arm->Toggle();
  } else
  if (!oi->joystick->GetRawButton(4)) {
    joystickButton4DBounce = false;
  }

  /* lift/drop lift */
  if (oi->joystick->GetRawButton(10) && !joystickButton10DBounce) { // Start Button
    joystickButton10DBounce = true;
    arm->Lift();
    lift->Toggle();
  } else if (!oi->joystick->GetRawButton(10)) {
    joystickButton10DBounce = false;
  }

  /* Pull/Eject cubes w/ the Claw */
  if (oi->joystick->GetRawButton(6)) { // Right Bumper
    claw->Pull();
  } else
  if (oi->joystick->GetRawButton(1)) { // X Button
    claw->PushFaster();
    frc::Wait(0.50);
  } else
  if (oi->joystick->GetRawButton(7)) { // Left Trigger
    claw->PushSlow();
  } else
  if (oi->joystick->GetRawButton(5)) { // Left Bumper
    claw->PushFast();
  } else {
    claw->Stop();
  }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
START_ROBOT_CLASS(Robot)
#endif