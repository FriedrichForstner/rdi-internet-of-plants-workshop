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
#include "DHT.h"
#include "Adafruit_TSL2591.h"
#include "Adafruit_seesaw.h"
#include <Adafruit_NeoPixel.h>

#define DHTTYPE DHT22
#define DHTPIN 6
#define LED_PIN 8
#define LED_COUNT 1

// init sensor objects
DHT dht(DHTPIN, DHTTYPE);
Adafruit_TSL2591 luminanceSensor = Adafruit_TSL2591(2591);
Adafruit_seesaw soilSensor;

// init LED
Adafruit_NeoPixel pixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // init environmental sensor
  dht.begin();

  // init soil sensor
  soilSensor.begin(0x36);

  // init luminance sensor
  luminanceSensor.begin();
  luminanceSensor.setGain(TSL2591_GAIN_LOW);
  luminanceSensor.setTiming(TSL2591_INTEGRATIONTIME_200MS);

  // Info LED
  pixel.begin();
  pixel.setBrightness(8);
  pixel.show();

}

void loop() {

  // air sensor
  float airTemperature = dht.readTemperature(); // air temperature in C
  float airHumidity = dht.readHumidity(); // air humidity

  // soil sensor
  float soilTemperature = soilSensor.getTemp();
  uint16_t soilHumidity= soilSensor.touchRead(0);

  // luminance sensor
  sensors_event_t event;
  luminanceSensor.getEvent(&event);
  float luminance = event.light;

  // single line serial output with all parameter
  // air_temperature, air_humidity, soil_temperature, soil_humidity, luminance
  Serial.print(airTemperature);
  Serial.print(",");
  Serial.print(airHumidity);
  Serial.print(",");
  Serial.print(soilTemperature);
  Serial.print(",");
  Serial.print(soilHumidity);
  Serial.print(",");
  Serial.print(luminance);
  Serial.println("");

  // all good
  if ((luminance>50.0) & (soilHumidity>500.0)){
    // green
    pixel.setPixelColor(0, 0, 255, 0);
  }

  // too dry soil
  if (luminance<=50.0){
    // yellow
    pixel.setPixelColor(0, 255, 255, 0);
  }

  // to low light
  if (soilHumidity<=500){    
    //red
    pixel.setPixelColor(0, 255, 0, 0);
  } 


  pixel.show();
  
  delay(2000);
}
