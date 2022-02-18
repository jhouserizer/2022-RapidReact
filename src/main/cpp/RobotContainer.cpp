/*-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=*/
/*                       Blue Crew Robotics #6153                             */
/*                           Rapid React 2022                                 */
/*-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=*/
// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() : m_autonomousCommand(&m_subsystem) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Set the default command for the Drive Train
  m_subDriveTrain.SetDefaultCommand(CmdDriveWithController(&m_subDriveTrain, driverController));
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here

  // Setup the command to shift gears when right bumper is pressed
  driverController_button_rbump->WhenPressed(new CmdShiftGear(&m_subDriveTrain));
  
  driverController_button_a->WhileHeld(frc2::SequentialCommandGroup{
    //CmdTurnOnShooterLimelight(&m_subLimelightShooter), // Once limelight is functional use this to turn on LEDS
    //CmdAcquireShooterTarget(&m_subLimelightShooter,&m_subDriveTrain), // Once limelight is functional work on the targeting command
    CmdSetShooterAngle(&m_subShooter), 
    CmdSpinShooterWheels(&m_subShooter)});

  driverController_button_a->WhenReleased(frc2::SequentialCommandGroup{
    //CmdTurnOffShooterLimelight(&m_subLimelightShooter), // Once limelight is functional use this to turn off LEDS
    CmdResetShooterAngle(&m_subShooter),
    CmdStopShooterWheels(&m_subShooter)});

  //driverController_button_x->WhenPressed(new CmdFeedBallToShooter(&m_subIntake)); This new command needs to be created with the Shooter Feeder
  
  // Way to add debouce on the buttons
  //driverController_button_b->Debounce(60_ms,frc::Debouncer::kBoth).WhileActiveContinous(new CmdSetShooterAngle(&m_subShooter));

  driverController_button_y->WhileHeld(new CmdExtendIntake(&m_subIntake));
  driverController_button_y->WhenReleased(new CmdIntakeToHomePosition(&m_subIntake));

}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}

void RobotContainer::ConfigureDrive() {
  m_subDriveTrain.DriveTrainConfigure();
  m_subDriveTrain.GetPidFromDashboard();

}

void RobotContainer::ConfigureShooter() {
  m_subShooter.ConfigureShooter();
}

void RobotContainer::ConfigureCompressor() {
  m_subPneumatics.ConfigureCompressor();
}