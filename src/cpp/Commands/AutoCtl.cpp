/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/AutoCtl.h"
#include "Robot.h"
#include "RobotMap.h"

AutoCtl::AutoCtl(
    std::string newTargets,
    TargetPerf newTarget, StartPos newStartingPosition
) : Command("AutoCtl")
{
  Requires(Robot::drivetrain);
  Requires(Robot::claw);
  Requires(Robot::arm);
  Requires(Robot::lift);

  targets = newTargets;
  perferedTarget = newTarget;
  startingPosition = newStartingPosition;
}

// Called just before this Command runs the first time
void AutoCtl::Initialize() {
  timer = new Timer();

  if (perferedTarget == TargetPerf::SCALE) {
    if (startingPosition == StartPos::LEFT) {
      if (targets[1] == 'L')
        finalTarget = Targets::LEFT_SCALE;
      else if (targets[0] == 'L')
        finalTarget = Targets::LEFT_SWITCH;
    }
    else if (startingPosition == StartPos::RIGHT) {
      if (targets[1] == 'R')
        finalTarget = Targets::RIGHT_SCALE;
      else if (targets[0] == 'R')
        finalTarget = Targets::RIGHT_SWITCH;
    }
  }

  else if (perferedTarget == TargetPerf::SWITCH) {
    if (startingPosition == StartPos::LEFT) {
      if (targets[0] == 'L')
        finalTarget = Targets::LEFT_SWITCH;
      else if (targets[1] == 'L')
        finalTarget = Targets::LEFT_SCALE;
    }
    else if (startingPosition == StartPos::RIGHT) {
      if (targets[0] == 'R')
        finalTarget = Targets::RIGHT_SWITCH;
      else if (targets[1] == 'R')
        finalTarget = Targets::RIGHT_SCALE;
    }
  }

  else if ((perferedTarget == TargetPerf::NEITHER)
      && (finalTarget == Targets::NONE)) {
    finalTarget = Targets::NONE_SCALE;
  }

  timer->Reset();
  Robot::drivetrain->ResetEncoders();

  timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void AutoCtl::Execute() {
  double curTime = timer->Get();

  /* Drive for 3 Seconds */
  if (IsBetween(curTime, 0, 2.25)) {
    DriveStraight();
    Robot::claw->Stop();
    Robot::lift->Drop();
    Robot::arm->Lift();
  }

  /* Paths Diverge */
  switch (finalTarget) {
    case Targets::LEFT_SCALE:
      if (IsBetween(curTime, 2.25, 6)) {
        DriveStraight();
        Robot::claw->Stop();
        Robot::lift->Lift();
      }
      if (IsBetween(curTime, 6, 6.5)) {
        Robot::drivetrain->ArcadeDrive(0, kAutoTurnSpeed);
        Robot::claw->Stop();
        Robot::lift->Lift();
        Robot::arm->Lift();
      }
      if (IsBetween(curTime, 6.5, 7.5)) {
        Robot::drivetrain->ArcadeDrive(0, 0);
        Robot::claw->Stop(); //claw->PushFaster();
        Robot::lift->Lift();
        Robot::arm->Lift();
      }
      if (IsBetween(curTime, 7.5, 8)) {
        Robot::drivetrain->ArcadeDrive(-kAutoDriveSpeed, 0);
        Robot::claw->Stop();
        Robot::lift->Lift();
        Robot::arm->Lift();
      }
      if (curTime > 8) {
        Robot::drivetrain->ArcadeDrive(0, 0);
        Robot::claw->Stop();
        //lift->Drop();
        //arm->Drop();
        finalTarget = Targets::NONE;
      }
      break;
    case Targets::RIGHT_SCALE:
      if (IsBetween(curTime, 2.25, 6)) {
        DriveStraight();
        Robot::claw->Stop();
        Robot::lift->Lift();
        Robot::arm->Lift();
      }
      if (IsBetween(curTime, 6, 6.5)) {
        Robot::drivetrain->ArcadeDrive(0, -kAutoTurnSpeed);
        Robot::claw->Stop();
        Robot::lift->Lift();
        Robot::arm->Lift();
      }
      if (IsBetween(curTime, 6.5, 7.5)) {
        Robot::drivetrain->ArcadeDrive(0, 0);
        Robot::claw->Stop(); //claw->PushFaster();
        Robot::lift->Lift();
        Robot::arm->Lift();
      }
      if (IsBetween(curTime, 7.5, 8)) {
        Robot::drivetrain->ArcadeDrive(-kAutoDriveSpeed, 0);
        Robot::claw->Stop();
        Robot::lift->Lift();
        Robot::arm->Lift();
      }
      if (curTime > 8) {
        Robot::drivetrain->ArcadeDrive(0, 0);
        Robot::claw->Stop();
        //lift->Drop();
        //arm->Drop();
        finalTarget = Targets::NONE;
      }
      break;
    case Targets::NONE_SCALE:
      if (IsBetween(curTime, 2.25, 6)) {
        DriveStraight();
        Robot::claw->Stop();
        Robot::lift->Lift();
        Robot::arm->Lift();
      }
      if (curTime > 6) {
        Robot::drivetrain->ArcadeDrive(0, 0);
        Robot::claw->Stop();
        Robot::lift->Lift();
        Robot::arm->Lift();
        finalTarget = Targets::NONE;
      }
      break;
    case Targets::LEFT_SWITCH:
      if (IsBetween(curTime, 2.25, 4)) {
        Robot::drivetrain->ArcadeDrive(kAutoDriveSpeed, kAutoTurnSpeed);
        Robot::claw->Stop();
      }
      if (IsBetween(curTime, 4, 5)) {
        Robot::drivetrain->ArcadeDrive(0, 0);
        Robot::claw->PushSlow();
      }
      if (curTime > 5) {
        Robot::drivetrain->ArcadeDrive(0, 0);
        Robot::claw->Stop();
        Robot::lift->Lift();
        Robot::arm->Drop();
        finalTarget = Targets::NONE;
      }
      break;
    case Targets::RIGHT_SWITCH:
      if (IsBetween(curTime, 2.25, 4)) {
        Robot::drivetrain->ArcadeDrive(kAutoDriveSpeed, -kAutoTurnSpeed);
        Robot::claw->Stop();
      }
      if (IsBetween(curTime, 4, 5)) {
        Robot::drivetrain->ArcadeDrive(0, 0);
        Robot::claw->PushSlow();
      }
      if (curTime > 5) {
        Robot::drivetrain->ArcadeDrive(0, 0);
        Robot::claw->Stop();
        finalTarget = Targets::NONE;
      }
      break;
    case Targets::NONE:
      if (IsBetween(curTime, 2.25, 4)) {
        DriveStraight();
        Robot::claw->Stop();
      }
      else {
        Robot::drivetrain->ArcadeDrive(0, 0);
        Robot::claw->Stop();
      }
      break;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool AutoCtl::IsFinished() { return false; }

// Called once after isFinished returns true
void AutoCtl::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoCtl::Interrupted() {}


void AutoCtl::DriveStraight() {
  double motorDiff = 
      Robot::drivetrain->GetRightEncoder()
        - Robot::drivetrain->GetLeftEncoder();
    motorDiff = motorDiff * kDriveBitsToInches;
    if (motorDiff > 0.20) { motorDiff = 0.20; }

    Robot::drivetrain->ArcadeDrive(kAutoDriveSpeed, motorDiff);
};


bool AutoCtl::IsBetween(float number, double lower, double upper) {
  if ((number > lower) && (number <= upper))
    return true;
  else
    return false;
};