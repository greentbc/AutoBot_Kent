#include "Arduino.h"
#include "Action.h"
#include "Sensing.h"
#include "Protocol.h"
#include "Localization.h"
#include "autoRobot.h"


void updateMotor() {
  //Serial.println("Right Speed is " + String(speedR) + " Left Speed is " + String(speedL));//debug
  if ( speedR > 0) {
    digitalWrite(MOTOR_RIGHT_A, LOW); digitalWrite(MOTOR_RIGHT_B, HIGH); analogWrite(MOTOR_RIGHT_ENABLE, speedR);
  } else if ( speedR < 0) {
    digitalWrite(MOTOR_RIGHT_A, HIGH); digitalWrite(MOTOR_RIGHT_B, LOW); analogWrite(MOTOR_RIGHT_ENABLE, abs(speedR));
  } else {
    digitalWrite(MOTOR_RIGHT_A, LOW); digitalWrite(MOTOR_RIGHT_B, LOW); analogWrite(MOTOR_RIGHT_ENABLE, 0);
  }
  if ( speedL > 0) {
    digitalWrite(MOTOR_LEFT_A, HIGH); digitalWrite(MOTOR_LEFT_B, LOW); analogWrite(MOTOR_LEFT_ENABLE, speedL);
  } else if ( speedL < 0) {
    digitalWrite(MOTOR_LEFT_A, LOW); digitalWrite(MOTOR_LEFT_B, HIGH ); analogWrite(MOTOR_LEFT_ENABLE, abs(speedL));
  } else {
    digitalWrite(MOTOR_LEFT_A, LOW); digitalWrite(MOTOR_LEFT_B, LOW); analogWrite(MOTOR_LEFT_ENABLE, 0);
  }
}

void turn(int degree) {

  long targetOdometerR;
  long targetOdometerL;
  //90 degree for the robot is 20 ticks it seems
  //so 90/4.5

  int numberOfTicks = degree / 4.5;
  //Serial.println("number of ticks: " + String(numberOfTicks));
  //set the targets depending on the direction. +is counter clock -is clockwise
  //if (degree > 0) {
  targetOdometerR = odometerR + numberOfTicks;
  targetOdometerL = odometerL - numberOfTicks;




  //+ case
  while ((targetOdometerR > odometerR) || (targetOdometerL < odometerL)) {
    //Serial.println("should be turning now. SpeedR is " + String(speedR) + " speedL is " + String(speedL));
    if (targetOdometerR > odometerR) {
      speedR = +150;
    }
    else {
      speedR = 0;
    }
    if (targetOdometerL < odometerL) {
      speedL = -150;
    }
    else {
      speedL = 0;
    }
    updateMotor();
  }


  //- case

  while ((targetOdometerR < odometerR) || (targetOdometerL > odometerL)) {
    //Serial.println("should be turning now. SpeedR is " + String(speedR) + " speedL is " + String(speedL));
    if (targetOdometerR < odometerR) {
      speedR = -150;
    }
    else {
      speedR = 0;
    }
    if (targetOdometerL > odometerL) {
      speedL = 150;
    }
    else {
      speedL = 0;
    }
    updateMotor();
  }
  speedR = 0; speedL = 0;
  updateMotor();
  //printOdometer();

}
