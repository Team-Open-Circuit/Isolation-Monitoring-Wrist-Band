# **Isolation-Monitoring-Wrist-Band**
e-Yantra Hackathon 2021 Team: *eYHC#1382*
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
* Fritzing IDE: To make a virtual Circuit with all the hardware.
* Ubitdots Cloud: Ubidots is used as the IoT Cloud which is communicated using MQTT protocol. Ubidots also allows to make an IoT dashboard which displays all the patient status.
# Circuit Diagram
![Circuit Diagram](/Images/Circuit.png)
# Ubidots Dashboard
![Ubidots Dashboard](/Images/Dashboard.png)
# Data Flow Diagram
![Data Flow Diagram](/Images/Working.jpg)
