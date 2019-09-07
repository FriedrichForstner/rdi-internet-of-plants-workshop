/*
 * Exploration code for ReDI's InternetoPlants for kids workshop. 
 * Sensing plant related environmental paramters with Arduino and 
 * recording/plotting/processing them in Python.
 * 
 * Author: ReDI School Munich
 * License: GPL v3
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

Adafruit_BME680 bme;
void setup() {
  Serial.begin(9600);
  while (!Serial);
  !bme.begin();
}

void loop() {
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  // single line serial output with all parameter
  // air_temperature, air_humidity, soil_humidity, brightness
  Serial.print(bme.temperature);
  Serial.print(",");
  Serial.print(bme.humidity);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.println("");
  delay(1000);
}
