/*
   Copyright (c) 2016 Intel Corporation.  All rights reserved.
   See the bottom of this file for full license terms.
*/

/*
   This sketch example demonstrates how the BMI160 accelerometer on the
   Intel(R) Curie(TM) module can be used to detect zero motion events
*/
#include <BMI160Gen.h>

boolean ledState = false;          // state of the LED
void setup() {
  Serial.begin(115200); // initialize Serial communication
  while(!Serial) ;    // wait for serial port to connect.

  /* Initialise the IMU */
  BMI160.begin();
  BMI160.attachInterrupt(eventCallback);

  /* Enable Zero Motion Detection */
  BMI160.setDetectionThreshold(CURIE_IMU_ZERO_MOTION, 50);  // 50mg
  BMI160.setDetectionDuration(CURIE_IMU_ZERO_MOTION, 2);    // 2s
  BMI160.interrupts(CURIE_IMU_ZERO_MOTION);

  /* Enable Motion Detection */
  BMI160.setDetectionThreshold(CURIE_IMU_MOTION, 20);      // 20mg
  BMI160.setDetectionDuration(CURIE_IMU_MOTION, 10);       // trigger times of consecutive slope data points
  BMI160.interrupts(CURIE_IMU_MOTION);

  Serial.println("IMU initialisation complete, waiting for events...");
}

void loop() {
  // if zero motion is detected, LED will be turned up. 
  digitalWrite(LED_BUILTIN, ledState);
}

static void eventCallback(void){
  if (BMI160.getInterruptStatus(CURIE_IMU_ZERO_MOTION)) {
    ledState = true; 
    Serial.println("zero motion detected...");
  }  
  if (BMI160.getInterruptStatus(CURIE_IMU_MOTION)) {
    ledState = false;
    if (BMI160.motionDetected(X_AXIS, POSITIVE))
      Serial.println("Negative motion detected on X-axis");
    if (BMI160.motionDetected(X_AXIS, NEGATIVE))
      Serial.println("Positive motion detected on X-axis");
    if (BMI160.motionDetected(Y_AXIS, POSITIVE))
      Serial.println("Negative motion detected on Y-axis");
    if (BMI160.motionDetected(Y_AXIS, NEGATIVE))
      Serial.println("Positive motion detected on Y-axis");
    if (BMI160.motionDetected(Z_AXIS, POSITIVE))
      Serial.println("Negative motion detected on Z-axis");
    if (BMI160.motionDetected(Z_AXIS, NEGATIVE))
      Serial.println("Positive motion detected on Z-axis");
  }  
}

/*
   Copyright (c) 2016 Intel Corporation.  All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/
