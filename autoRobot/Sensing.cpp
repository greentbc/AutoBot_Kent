#include "Arduino.h"
#include "Sensing.h"
#include "Protocol.h"
#include "Localization.h"
#include "autoRobot.h"

int lineR = 0;
int lineL = 0;
int sonar = 0;

volatile long odometerR = 0;
volatile long odometerL = 0;

char sonarBuffer [SONAR_BUFFER_SIZE];

int updateSonar() {

  // Clears the trigPin
  digitalWrite(SONAR_TRIG, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(SONAR_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_TRIG, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds, and then caculate distance
  return pulseIn(SONAR_ECHO, HIGH, 100000) * 0.034 / 2 ;
}

void updateLineSensor() {
  lineR = digitalRead(LINE_RIGHT); lineL = digitalRead(LINE_LEFT);
  /*
    //debug
    if (!lineR) {
      //Serial.println("Right side reads black.");
      speedR = 100;
    }

    if (!lineL) {
      //Serial.println("Left side reads black.");
      speedL= 120;
    }

    //debug off
    if (lineR) {
      //Serial.println("Right side reads black.");
      speedR = 0;
    }
    if (lineL) {
      //Serial.println("Left side reads black.");
      speedL= 0;
    }
  */

}
void rightOdometer() {

  //Serial.println("rightOdometer triggered111");
  if (speedR >= 0) {
    odometerR ++;
  } else if (speedR < 0) {
    odometerR --;
  }
}
void leftOdometer() {
  //Serial.println("leftOdometer triggered111");
  if (speedL >= 0) {
    odometerL ++;
  } else if (speedL < 0) {
    odometerL --;
  }
}


void printOdometer(){
  Serial.println("The right odometer is " + String(odometerR) +
                 " The left odometer is " + String(odometerL));
}
