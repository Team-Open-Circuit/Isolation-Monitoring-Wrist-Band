# **Isolation-Monitoring-Wrist-Band**
e-Yantra Hackathon 2021 Team: *eYHC#1382*

## Description
Coronavirus is expanding its form in the form of different mutations leading to mass spreading waves around the globe. Though the vaccination process has begun, there is a need to monitor the health and isolation of many patients who prefer self isolation to control the spread, until the vaccination procedure is complete across the vast population in our country. So, the idea of this project is to make an IoT based wrist band called the *Isolation Monititoring Band* which has the following functionalities:
* Monitoring the patients' health conditions remotely by regular check of of parameters like Pulse-rate, Oxygen levels, Body Temperature.
* Tracking the status and location of the band (by medical authority) to ensure that the patient follows quarantine strictly.
* Connnects the patients and their health status to the nearby or concerned health care facilities.
* Emergency monitoring of the patient, to attend patient emergency situation based on health status fluctuation or emergency button pressed by patient.
* 
## Hardware and Software Requirement
### Hardware:
* The NodeMCU ESP8266 WiFi enabled SoC as the opensource IoT Development Platform.
* The MLX90614 Contact and Temperature sensor for temperature and band contact status.
* The MAX30100 Pulse-Oximeter for Pulse-rate and Oxygen level measurements.
* A Push-button for emergency status.
* 0.96 inch IIC/I2C OLED displlay module for wrist band display.
* Ublox ne0-6m GPS module for Location tracking.
### Software:
* Arduino IDE: For ESP8266 NodeMCU programming. The Libraries used are:
  * [MAX30100](/Libraries/MAX30100.zip)
  * [OakOLED](/Libraries/OakOLED.zip)
  * [TinyGPSPlus](/Libraries/TinyGPSPlus.zip)
  * [pubsubclient](/Libraries/pubsubclient.zip)
  * [ubidots-mqtt-esp](/Libraries/ubidots-mqtt-esp.zip)
* Fritzing IDE: To make a [Virtual Circuit Diagram](https://github.com/vbeyrc0768/Isolation-Monitoring-Wrist-Band/blob/main/README.md#circuit-diagram) with all the hardware.
* Ubitdots Cloud: Ubidots is used as the IoT Cloud which is communicated using MQTT protocol. Ubidots also allows to make an IoT dashboard which displays all the patient status.

# Circuit Diagram
![Circuit Diagram](/Images/Circuit.png)

# Data Flow Diagram
![Data Flow Diagram](/Images/Working.jpg)
The dataflow diagram below shows the total working of *Isolation Monitoring Wrist Band* prototype.
* The data from the sensor are frequently read by the NodeMCU and displayed in the wrist-band OLED display.
* The data is also published to the Ubidots Cloud via MQTT protocol.
* The Cloud updates the Dashboard which is accessed by the Health facilities and also visible to the patient.
* Frequent Health status is updated to the Healthcare database and the patient.
* The emergency is triggered with either large fluctuation in health parameters or manually by the patient (by pressing emergency button) to alert the Healthcare facility and the patient. This ensures that the patient is attended to by the Medical Aid when in emergency.

# Ubidots Dashboard
Here is a sample of Ubidots dashboard with various health and activity status of the user (patient). Once the NdeMCU publishes data to the Ubidots Cloud, the devices widgets automatically update the current status of the devices.
![Ubidots Dashboard](/Images/Dashboard.png)
