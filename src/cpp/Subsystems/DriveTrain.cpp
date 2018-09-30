/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>

#include "Subsystems/DriveTrain.h"
#include <SmartDashboard/SmartDashboard.h>

DriveTrain::DriveTrain(int leftMotorCanId, int rightMotorCanId)
  : Subsystem("DriveTrain")
{
  leftDrive = new WPI_TalonSRX(leftMotorCanId);
  rightDrive = new WPI_TalonSRX(rightMotorCanId);
  robotDrive = new DifferentialDrive(*leftDrive, *rightDrive);
}

void DriveTrain::InitDefaultCommand() {}

void DriveTrain::ArcadeDrive(double xSpeed, double zRotation)
{
  robotDrive->ArcadeDrive(xSpeed, zRotation, false);
}

int DriveTrain::GetLeftEncoder()
{
  leftDrive->GetSelectedSensorPosition(0);
}

int DriveTrain::GetRightEncoder()
{
  rightDrive->GetSelectedSensorPosition(0);
}

void DriveTrain::ResetEncoders() {
  leftDrive->SetSelectedSensorPosition(0, 0, 100);
  rightDrive->SetSelectedSensorPosition(0, 0, 100);
}

void DriveTrain::Display()
{
  frc::SmartDashboard::PutNumber("Volts",
      ((leftDrive->GetMotorOutputVoltage() + rightDrive->GetMotorOutputVoltage()) / 2)
  );
  frc::SmartDashboard::PutNumber("Amps",
      ((leftDrive->GetOutputCurrent() + rightDrive->GetOutputCurrent()) / 2)
  );
  frc::SmartDashboard::PutNumber("Left Clicks",
      this->GetLeftEncoder()
  );
  frc::SmartDashboard::PutNumber("Right Clicks",
      this->GetRightEncoder()
  );
}

void DriveTrain::SetSafetyEnabled(bool enabled)
{
  robotDrive->SetSafetyEnabled(enabled);
}

void DriveTrain::PrintFaults()
{
  leftDrive->GetFaults(_faults_L);
  rightDrive->GetFaults(_faults_R);

  if (_faults_L.SensorOutOfPhase) {
    std::cout << " Left drive sensor is out of phase\n";
  }
  if (_faults_R.SensorOutOfPhase) {
    std::cout << " Right drive sensor is out of phase\n";
  }
}