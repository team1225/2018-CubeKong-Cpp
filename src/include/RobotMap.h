/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/* Map of global constants, any number that should be unchanged during runtime
 * and known across the program. This is intended to reduce confusion and prevent
 * "Magic Numbers" from hiding inside the code
 */

/*
 * Button Map
 */
const int kHighSpeedButton = 12;

/*
 * Modifiers
 */
const double kTeleopDriveSpeed = 0.80;
const double kTeleopTurnNormSpeed = 0.50;
const double kTeleopTurnHighSpeed = 0.70;
const double kAutoDriveSpeed = 0.75;
const double kAutoTurnSpeed = 0.70;
const double kDriveBitsToInches = (4096 / (6*3.1415));

 /* 
  * Robot Portmap
  */
const int kPcmArm = 05;
const int kPcmBody = 06;

const int kTalonSrxDriveLeftChannel = 10;
const int kTalonSrxDriveRightChannel = 11;

const int kClawFrontPwm = 1;
const int kClawRearPwm = 0;
const int kClawSwitchDio = 0;
const int kClawRamFwd = 2;
const int kClawRamBwd = 3;

const int kArmFwd = 0; // kPcmArm
const int kArmBwd = 1;

const int kLiftFwd = 0; // kPcmBody
const int kLiftBwd = 1;