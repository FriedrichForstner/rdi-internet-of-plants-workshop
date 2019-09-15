/*
   Exploration code for ReDI's InternetoPlants for kids workshop.
   Sensing plant related environmental paramters with Arduino and
   recording/plotting/processing them in Python.

   Author: ReDI School Munich
   License: GPL v3
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

//global sensor values
float airTemperature, airHumidity, soilTemperature, luminance;
uint16_t soilHumidity;

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

void setColor(char* color) {
  if (strcmp(color, "GREEN") == 0) {
    pixel.setPixelColor(0, 0, 128, 0);
  } else if (strcmp(color, "YELLOW") == 0) {
    pixel.setPixelColor(0, 255, 255, 0);
  } else if (strcmp(color, "RED") == 0) {
    pixel.setPixelColor(0, 255, 0, 0);
  }else if (strcmp(color, "INVISIBLE") == 0) {
    pixel.setPixelColor(0, 0, 0, 0);
  }
  pixel.show();
}

void printSensorValues() {
  // single line serial output with all parameter
  // air_temperature, air_humidity, soil_temperature, soil_humidity, luminance
  //Luft Temperatur, Luft Feuchtigkeit, Erde Temperatur, Erde Feuchtigkeit, Leuchtdichte
  Serial.println((String) airTemperature + "," + airHumidity + "," + soilTemperature + "," + soilHumidity + "," + luminance);
}

void initializeSensorValues() {
  // air sensor
  airTemperature = dht.readTemperature(); // air temperature in C
  airHumidity = dht.readHumidity(); // air humidity

  // soil sensor
  soilTemperature = soilSensor.getTemp();
  soilHumidity = soilSensor.touchRead(0);

  // luminance sensor
  sensors_event_t event;
  luminanceSensor.getEvent(&event);
  luminance = event.light;
}



void loop() {
  initializeSensorValues();
  printSensorValues();
  
  setColor("INVISIBLE");
  
  delay(150);
  
  // too much air temperature or humidiity
  if ((airTemperature > 24) | (airHumidity > 88)) {
    setColor("RED");
  }
  else{
    setColor("GREEN");
  }
  
  delay(300);
}
