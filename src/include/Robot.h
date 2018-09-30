/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <IterativeRobot.h>
#include <SmartDashboard/SendableChooser.h>

#include "OI.h"

#include "Subsystems/DriveTrain.h"
#include "Subsystems/Claw.h"
#include "Subsystems/Lifter.h"

#include <Commands/Scheduler.h>
#include "Commands/AutoCtl.h"

class Robot : public frc::IterativeRobot {
 public:
  static OI *oi;
  static DriveTrain *drivetrain;
  static Claw *claw;
  static Lifter *arm;
  static Lifter *lift;

  Robot();
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  AutoCtl *autoCtl = nullptr;
  frc::SendableChooser<AutoCtl::StartPos> startingPosition;
  const std::string kStartLeft = "Starting on the left of the switch";
  const std::string kStartRight = "Starting on the right of the switch";
  AutoCtl::StartPos autoStartingPos;
  frc::SendableChooser<AutoCtl::TargetPerf> targetPreference;
  const std::string kPerfNone = "Just Drive, no cube";
  const std::string kPerfSwitch = "Target the switch, scale as fallback";
  const std::string kPerfScale = "Target the scale, switch as fallback";
  AutoCtl::TargetPerf autoPerferedTarget;

  bool joystickButton4DBounce = false;
	bool joystickButton10DBounce = false;
};
