/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <ctre/Phoenix.h>
#include <Drive/DifferentialDrive.h>
#include <Commands/Subsystem.h>

class DriveTrain : public frc::Subsystem {
 private:
  static WPI_TalonSRX *rightDrive;
  static WPI_TalonSRX *leftDrive;
  Faults _faults_L;
  Faults _faults_R;
  static DifferentialDrive *robotDrive;

 public:
  DriveTrain(int leftMotorCanId, int rightMotorCanId);
  void InitDefaultCommand() override;

  void ArcadeDrive(double xSpeed, double zRotation);
  int  GetLeftEncoder();
  int  GetRightEncoder();
  void ResetEncoders();

  void Display();
  void SetSafetyEnabled(bool enabled);
  void PrintFaults();
};
