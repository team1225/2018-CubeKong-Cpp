/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>
#include <Timer.h>

class AutoCtl : public frc::Command {
 public:
  enum StartPos {
    LEFT, RIGHT
  };
  enum TargetPerf {
    SWITCH, SCALE, NEITHER
  };

  AutoCtl(
      std::string newTargets,
      TargetPerf newTarget, StartPos newStartingPosition
  );
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

 private:
  enum Targets {
    LEFT_SWITCH, RIGHT_SWITCH,
    LEFT_SCALE, RIGHT_SCALE,
    NONE_SCALE, NONE
  };

  void DriveStraight();
  bool IsBetween(float number, double lower, double upper);

  std::string targets;
  TargetPerf perferedTarget;
  StartPos startingPosition;
  Targets finalTarget = Targets::NONE;
  frc::Timer* timer;
};
