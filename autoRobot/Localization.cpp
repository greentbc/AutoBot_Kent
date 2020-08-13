#include "Arduino.h"
#include "Localization.h"
#include "Sensing.h"
#include "autoRobot.h"
#include "math.h"

int speedRobot = 0;
int angle = 0;
int positionX = 0;
int positionY = 0;
int speedR = 0;
int speedL = 0;

//tyler added
int odometerDistance = 0;
int oldOdometerDistance = 1;
int smoothSpeed[3] = {0, 0, 0};
int smoothSpeedIndex = 0;

                        //currentMillis
                        //previousMillis
                        //ODOMETER_PER_DISTANCE
                        //odometerR
                        //units are in mm

void updateOdometer() {
  //distance is in mm
  odometerDistance = ((abs(odometerR) + abs(odometerL)) * ODOMETER_PER_DISTANCE) / 2;
}


void updateSpeedmeter() {
  double speedcm = 0;

  updateOdometer();//get new reading

  smoothSpeed[smoothSpeedIndex] = (odometerDistance - oldOdometerDistance);
  // broken into parts becasue I was haveing logic errors
  smoothSpeed[smoothSpeedIndex] = (smoothSpeed[smoothSpeedIndex] / (currentMillis - previousMillis)) * 1000;


  oldOdometerDistance = odometerDistance;

  //get an average
  for (int i=0; i < 3; i++){
    speedcm += smoothSpeed[i];
  }
  speedcm /= 3;
  
  smoothSpeedIndex++;
  if (smoothSpeedIndex > 3){smoothSpeedIndex=0;}


}
