"""Exploration code for ReDI's InternetoPlants for kids workshop. 
   Sensing plant related environmental paramters with Arduino and 
   recording/plotting/processing them."""

__author__      = "ReDI School Munich"
__copyright__   = "GPLv3"

import serial
import pandas
import matplotlib.pyplot as pyplot

# configure serial port
serial_port = '/dev/tty.usbmodem14101'

## my devices cayenne example

import cayenne.client
import time
import serial
import config
from IPython.display import clear_output

# mydevices dashboard setup
def on_message(message):
    True
#     print("message received: " + str(message))
    # If there is an error processing the message return an error string, otherwise return nothing.

# initialise serial interface
ser = serial.Serial(serial_port)
ser.flushInput()

# name and sequence of data
sensor_parameter = ["air_temperature", "air_humidity", "soil_temperature","soil_humidity", "luminance"]

# init data array
sensor_data_panda = pandas.DataFrame(columns=sensor_parameter)

# number of samples to record
numberOfRecordings = 20
sampleNum = 0

client = cayenne.client.CayenneMQTTClient()
client.on_message = on_message
client.begin(config.MQTT_USERNAME, config.MQTT_PASSWORD, config.MQTT_CLIENT_ID)
# For a secure connection use port 8883 when calling client.begin:
# client.begin(MQTT_USERNAME, MQTT_PASSWORD, MQTT_CLIENT_ID, port=8883)

while True:
    
#     try:
    # read serial byte data
    sensor_data_raw = ser.readline()
    # convert byte data to UTF string
    sensor_data_str = sensor_data_raw[0:len(sensor_data_raw)-2].decode("utf-8")
    # convert UTF string to array
    sensor_data_arr = sensor_data_str.split(",")
    # length fits to parameter names, parse and store
    if len(sensor_data_arr) == len(sensor_parameter):
        # parse
        sensor_data_dict = {sensor_parameter[i]:float(sensor_data_arr[i]) for i in range(len(sensor_parameter))}
        # store
        sensor_data_panda = sensor_data_panda.append(sensor_data_dict,ignore_index=True)

        # upload readings to myDevices Cayenne 
        client.loop()
        client.celsiusWrite(1, sensor_data_dict["air_temperature"])
        client.virtualWrite(2, sensor_data_dict["air_humidity"],"rel_hum","p")
        client.celsiusWrite(3, sensor_data_dict["soil_temperature"])
        client.virtualWrite(4, sensor_data_dict["soil_humidity"],"null","analog_sensor")
        client.luxWrite(5, sensor_data_dict["luminance"])
        clear_output()
        print(sensor_data_arr)   
    else:
        clear_output()
        print(sensor_data_str)
        print("Sensor array length does match expected number of parameters.")

#     except:
#         print("Interrupt")
#         ser.close()
#         break
ser.close()