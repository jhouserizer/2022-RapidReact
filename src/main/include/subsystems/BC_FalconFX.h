/*-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=*/
/*                       Blue Crew Robotics #6153                             */
/*                           Rapid React 2022                                 */
/*-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=-=+=*/

#pragma once
#include <ctre/Phoenix.h>
#include "Constants.h"

class BC_FalconFX : public virtual frc::SpeedController {
 public:
  BC_FalconFX(int device);


  // Overrides for SpeedController class
  void Set(double speed);
  void Disable();
	void StopMotor();
  double Get() const;
  void SetInverted(bool invert);
  bool GetInverted() const;

  // Sets the control mode of the TalonFX
  void SetControlMode(ctre::phoenix::motorcontrol::ControlMode mode);
  // Configure the feedforward tuning parameter
  void SetConfig_kF(int profileSlot, double value);
  // Configure the proportional tuning parameter
  void SetConfig_kP(int profileSlot, double value);
  // Configure the intergral tuning parameter
  void SetConfig_kI(int profileSlot, double value);
  // Configure the derivitive tuning parameter
  void SetConfig_kD(int profileSlot, double value);

  // Clear the sticky faults of the TalonFX
  void ClearStickyFault();
  // Set the follower
  void SetFollower(TalonFX* motor);
  // Get motor controller pointer
  TalonFX* GetMotorController();
  // Configure the feedback sensor
  void SetSelectedFeedbackSensor(FeedbackDevice device);
  // Configure the Stator current limit
  // enabled | Limit(amp) | Trigger Threshold(amp) | Trigger Threshold Time(s)
  void SetStatorCurrentLimit(bool enable, double limit, double trigger, double triggerTime);
  // Configure the Supply current limit
  // enabled | Limit(amp) | Trigger Threshold(amp) | Trigger Threshold Time(s)
  void SetSupplyCurrentLimit(bool enable, double limit, double trigger, double triggerTime);
  // Set nominal and peak outs on the motors
  void SetNominalPeakOutput(int profileSlot);
  


 private:
  TalonFX* ptr_falconFX = nullptr;

  ctre::phoenix::motorcontrol::ControlMode m_ControlMode = ctre::phoenix::motorcontrol::ControlMode::Velocity;

	double m_dSpeed = 0;
	double m_dMaxSpeed = VELOCITY_SP_MAX_LG;

};
