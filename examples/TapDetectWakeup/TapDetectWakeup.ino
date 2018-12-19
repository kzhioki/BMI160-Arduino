/*
 * Copyright (c) 2016 Intel Corporation.  All rights reserved.
 * See the bottom of this file for the license terms.
 */

/*
   This sketch example demonstrates how the BMI160 accelerometer on the
   Intel(R) Curie(TM) module can be used to detect tap events
*/

#include <LowPower.h>
#include <BMI160Gen.h>

const char* boot_cause_strings[] = {
  "Power On Reset with Power Supplied",
  "System WDT expired or Self Reboot",
  "Chip WDT expired",
  "WKUPL signal detected in deep sleep",
  "WKUPS signal detected in deep sleep",
  "RTC Alarm expired in deep sleep",
  "USB Connected in deep sleep",
  "Others in deep sleep",
  "SCU Interrupt detected in cold sleep",
  "RTC Alarm0 expired in cold sleep",
  "RTC Alarm1 expired in cold sleep",
  "RTC Alarm2 expired in cold sleep",
  "RTC Alarm Error occurred in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "SEN_INT signal detected in cold sleep",
  "PMIC signal detected in cold sleep",
  "USB Disconnected in cold sleep",
  "USB Connected in cold sleep",
  "Power On Reset",
};

void printBootCause(bootcause_e bc)
{
  Serial.println("--------------------------------------------------");
  Serial.print("Boot Cause: ");
  Serial.print(boot_cause_strings[bc]);
  if ((COLD_GPIO_IRQ36 <= bc) && (bc <= COLD_GPIO_IRQ47)) {
    // Wakeup by GPIO
    int pin = LowPower.getWakeupPin(bc);
    Serial.print(" <- pin ");
    Serial.print(pin);
  }
  Serial.println();
  Serial.println("--------------------------------------------------");
}

void setup() {
  Serial.begin(115200); // initialize Serial communication
  while(!Serial) ;    // wait for serial port to connect.

  // Initialize LowPower library
  LowPower.begin();

  // Get the boot cause
  bootcause_e bc = LowPower.bootCause();

  if ((bc == POR_SUPPLY) || (bc == POR_NORMAL)) {
    Serial.println("Example for tap wakeup from cold sleep");
  } else {
    Serial.println("wakeup from cold sleep");
  }

  // Print the boot cause
  printBootCause(bc);

  // Initialise the IMU
  BMI160.begin();
  BMI160.attachInterrupt(eventCallback);

  // Increase Accelerometer range to allow detection of stronger taps (< 4g)
  BMI160.setAccelerometerRange(4);

  // Reduce threshold to allow detection of weaker taps (>= 750mg)
  BMI160.setDetectionThreshold(CURIE_IMU_TAP, 750); // (750mg)

  // Enable Double-Tap detection
  BMI160.interrupts(CURIE_IMU_TAP);

  Serial.println("IMU initialization complete, waiting for events...");

  // Cold sleep
  Serial.print("Go to cold sleep...");
  delay(1000);
  LowPower.coldSleep();
}

void loop() {
  // nothing happens in the loop because all the action happens
  // in the callback function.
}

static void eventCallback()
{
  if (BMI160.getInterruptStatus(CURIE_IMU_TAP)) {
    if (BMI160.tapDetected(X_AXIS, NEGATIVE))
      Serial.println("Tap detected on negative X-axis");
    if (BMI160.tapDetected(X_AXIS, POSITIVE))
      Serial.println("Tap detected on positive X-axis");
    if (BMI160.tapDetected(Y_AXIS, NEGATIVE))
      Serial.println("Tap detected on negative Y-axis");
    if (BMI160.tapDetected(Y_AXIS, POSITIVE))
      Serial.println("Tap detected on positive Y-axis");
    if (BMI160.tapDetected(Z_AXIS, NEGATIVE))
      Serial.println("Tap detected on negative Z-axis");
    if (BMI160.tapDetected(Z_AXIS, POSITIVE))
      Serial.println("Tap detected on positive Z-axis");
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
