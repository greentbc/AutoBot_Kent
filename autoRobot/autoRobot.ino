
#include "Arduino.h"
#include "autoRobot.h"
#include "Protocol.h"
#include "Localization.h"
#include "Sensing.h"
#include "Action.h"

int stopFlag = 0;
int autoFlag = -1;   // Auto or Manual Control


unsigned long sonarClock = 0;
unsigned long lineClock = 0;
unsigned long odometerClock = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

void setup() {
  initialization();
}


void loop() {
  currentMillis = millis();
  updateSpeedmeter();
  updateCommand();  //protocol.h read in command
  updateSensors();  //function is in SDR_SUGV
  updatePlan();
  updateAction();
  previousMillis = currentMillis;

}

void updatePlan() {


  if (stopFlag ) {
    speedR = 0; speedL = 0;
  }
  else if (autoFlag == 1) { //Auto-driving

    //both read white
    if (!lineR && !lineL) {

      speedR = 150; speedL = 150;
    }

    //Right hit a black line. Turn left
    if (lineR && !lineL) {
      turn(45);
    }

    //left hit a black line. Turn right
    if (!lineR && lineL) {
      turn(-45);
    }

    //hit a will dead on, turn around
    if (lineR && lineL) {
      turn(180);
    }


  } else if (autoFlag == 0) {
    //manual control?
  } else {
    speedR = 0; speedL = 0;
  }


}

void updateAction() {

  updateMotor();
}



void updateSensors() {
  updateLineSensor();
  sonar = updateSonar();

  //Serial.println("Sonar is " + String(sonar));
  if (sonar < 10) {
    stopFlag = 1;
  }
  else {
    stopFlag = 1;
  }
}





void initialization() {
  currentMillis = millis();
  init_communication();
  init_pin();

}

void init_communication() {
  Serial.begin(115200); Serial.println("Program Start...vTyler");
  init_buffer();
}

void init_pin() {
  //Motor pin setting
  pinMode(MOTOR_LEFT_ENABLE, OUTPUT); pinMode(MOTOR_LEFT_A, OUTPUT); pinMode(MOTOR_LEFT_B, OUTPUT);
  pinMode(MOTOR_RIGHT_ENABLE, OUTPUT); pinMode(MOTOR_RIGHT_A, OUTPUT); pinMode(MOTOR_RIGHT_B, OUTPUT);
  //Sonar pin setting
  pinMode(SONAR_ECHO, INPUT); pinMode(SONAR_TRIG, OUTPUT);
  pinMode(LINE_LEFT, INPUT_PULLUP); pinMode(LINE_RIGHT, INPUT_PULLUP);
  attachInterrupt(0, rightOdometer, CHANGE);//function in snesing
  attachInterrupt(1, leftOdometer, CHANGE);
}
