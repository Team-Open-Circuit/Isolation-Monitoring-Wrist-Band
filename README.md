# **Isolation-Monitoring-Wrist-Band**
e-Yantra Hackathon 2021 Team: eYHC#1382

# Table of Contents
- [Description](#description)
- [Hardware](#hardware)
- [Software](#software)
- [INSTALLATION](#installation)
- [Circuit Diagram](#circuit-diagram)
- [Ubidots Dashboard](#ubidots-dashboard)
- [Data Flow Diagram](#data-flow-diagram)
- [References](#references)
## Description
Coronavirus is expanding its form in the form of different mutations leading to mass spreading waves around the globe. Though the vaccination process has begun, there is a need to monitor the health and isolation of many patients who prefer self isolation to control the spread, until the vaccination procedure is complete across the vast population in our country. So, the idea of this project is to make an IoT based wrist band called the *Isolation Monititoring Band* which has the following functionalities:
* Monitoring the patients' health conditions remotely by regular check of of parameters like Pulse-rate, Oxygen levels, Body Temperature.
* Tracking the status and location of the band (by medical authority) to ensure that the patient follows quarantine strictly.
* Connnects the patients and their health status to the nearby or concerned health care facilities.
* Emergency monitoring of the patient, to attend patient emergency situation based on health status fluctuation or emergency button pressed by patient.

## Hardware and Software Requirement
### Hardware:
* The NodeMCU ESP8266 WiFi enabled SoC as the opensource IoT Development Platform.
* The MLX90614 Contact and Temperature sensor for temperature and band contact status.
* The MAX30100 Pulse-Oximeter for Pulse-rate and Oxygen level measurements.
* A Push-button for emergency status.
* 0.96 inch IIC/I2C OLED displlay module for wrist band display.
* Ublox ne0-6m GPS module for Location tracking.
### Software:
* Arduino IDE: For ESP8266 NodeMCU programming.
* Fritzing IDE: To make a [Virtual Circuit Diagram](https://github.com/vbeyrc0768/Isolation-Monitoring-Wrist-Band/blob/main/README.md#circuit-diagram) with all the hardware.
* Ubitdots Cloud: Ubidots is used as the IoT Cloud which is communicated using MQTT protocol. Ubidots also allows to make a customized [IoT Dashboard](https://github.com/vbeyrc0768/Isolation-Monitoring-Wrist-Band#ubidots-dashboard) which displays all the patient statuses.

# INSTALLATION
* Download [Arduino IDE](https://www.arduino.cc/en/software)
* In Arduino ide, goto Preferences and add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` in addition board manager url as shown in the image.
![nodemcu_preference](/Images/nodemcu_preference.PNG)
* Goto board manager and download esp8266 board as shown in the image.
![esp8266](/Images/nodemcu_board_manager.PNG)
* Add the following libraries :
  * [MAX30100](/Libraries/MAX30100.zip)
  * [Adafruit_GFX](/Libraries/Adafruit_GFX_Library.zip)
  * [Adafruit_SSD1306](/Libraries/Adafruit_SSD1306.zip)
  * [TinyGPSPlus](/Libraries/TinyGPSPlus.zip)
  * [pubsubclient](/Libraries/pubsubclient.zip)
  * [ubidots-mqtt-esp](/Libraries/ubidots-mqtt-esp.zip)
* We have used oLED 64*128, so we need to make uncomment the line from the Adafruit_SSD1306 library file as shown.

![Adafruit_SSD1306](/Images/gfx.PNG)
* Now uncomment the line as shown.
![uncomment](/Images/uncomment.PNG)
* Now open the Ardunio file and compile and upload to your Nodemcu ESP8266.  

# Circuit Diagram
![Circuit Diagram](/Images/Circuit.png)

# Ubidots Dashboard
Here is a sample of Ubidots dashboard with various health and activity status of the user (patient). Once the NdeMCU publishes data to the Ubidots Cloud, the devices widgets automatically update the current status of the devices.
![Ubidots Dashboard](/Images/Dashboard.png)

# Data Flow Diagram
![Data Flow Diagram](/Images/Working.jpg)
The dataflow diagram below shows the total working of *Isolation Monitoring Wrist Band* prototype.
* The data from the sensor are frequently read by the NodeMCU and displayed in the wrist-band OLED display.
* The data is also published to the Ubidots Cloud via MQTT protocol.
* The Cloud updates the Dashboard which is accessed by the Health facilities and also visible to the patient.
* Frequent Health status is updated to the Healthcare database and the patient.
* The emergency is triggered with either large fluctuation in health parameters or manually by the patient (by pressing emergency button) to alert the Healthcare facility and the patient. This ensures that the patient is attended to by the Medical Aid when in emergency.

# References
* [Using MQTT broker with Ubidots](https://github.com/ubidots/ubidots-mqtt-esp)
* [Using oLED](https://create.arduino.cc/projecthub/Arnov_Sharma_makes/0-96-inch-oled-getting-started-guide-78163a)
* [Using max30100](https://create.arduino.cc/projecthub/iasonas-christoulakis/measure-spo2-heart-rate-and-bpt-using-arduino-68724d?ref=part&ref_id=10308&offset=9)
