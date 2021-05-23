/*
 
 eYHC#1382
 e-yantra hakathon
 BMS College Of engineering
 Team_members: Sanketh J, Suryadatta, Satvik, Vinayak
 
*/

// lib s for mqtt with ubidots
#include <PubSubClient.h>         
#include <UbidotsESPMQTT.h>

// lib s for gps module
#include <TinyGPS++.h>            
#include <SoftwareSerial.h>

#include <Wire.h>       // lib for wiring

// lib s for oled display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 

#include <Adafruit_MLX90614.h>      // lib for temperature
#include "MAX30100_PulseOximeter.h"   // lib for pulse and spo2

#define REPORTING_PERIOD_MS     1000        // to report for every 1 second
#define TOKEN "BBFF-zhlQgSLnqxveWHNLFgQI73665dciuF" // Put your Ubidots' TOKEN
#define WIFINAME "testing"        //Your SSID
#define WIFIPASS "123456"         // Your Wifi password

PulseOximeter pox;            
uint32_t tsLastReport = 0;

Ubidots client(TOKEN);        // sending token for ubidots client

Adafruit_MLX90614 mlx = Adafruit_MLX90614();      

Adafruit_SSD1306 display(-1);     // oled display

int BUTTON_PIN = 6;              // choose the input pin (for a pushbutton)
int status = 0;                  // variable for reading the pin status

TinyGPSPlus gps;                // The TinyGPS++ object
SoftwareSerial ss(4, 5);        // The serial connection to the GPS device
float latitude , longitude;
String lat_str , lng_str, time_str;
int hour, minute, second, pm;
char str_temp[16];      // temperory char s, created to store data of latitude and longitude
char str_temp2[16];

void onBeatDetected()
{
  Serial.println("Beat Detected!");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived ["); Serial.print(topic); Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup()   
{                
  Serial.begin(115200);   // for starting serial monitor
  ss.begin(9600);   // for gps module
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);    // initialize oled

  pinMode(BUTTON_PIN,INPUT);          // initialize button pin

  mlx.begin();

  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);    // connecting to nearby wifi
  client.begin(callback);
  
  display.begin();      // oled initialize
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  Serial.print("Initializing pulse oximeter..");

  if (!pox.begin()){ 
    Serial.println("FAILED");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(0, 0);
    display.println("FAILED");
    display.display();
    }
  else{
    Serial.println("SUCCESS");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(0, 0);
    display.println("SUCCESS");
    display.display();
    
    pox.setIRLedCurrent(MAX30100_LED_CURR_24MA);
    pox.setOnBeatDetectedCallback(onBeatDetected); // Register a callback for the beat detection
    }
}

void loop(){
  if(!client.connected()){      // to check connected and if not reconnect to ubidots (mqtt)
    client.reconnect();
    }
    
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())     // to get latitude and longitude
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
      }

      if (gps.time.isValid())       // to get time to display on oled screen
      {
        time_str = "";
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();

        minute = (minute + 30);
        if (minute > 59)
        {
          minute = minute - 60;
          hour = hour + 1;
        }
        hour = (hour + 5) ;
        if (hour > 23)
          hour = hour - 24;

        if (hour >= 12)
          pm = 1;
        else
          pm = 0;

        hour = hour % 12;

        if (hour < 10)
          time_str = '0';
        time_str += String(hour);

        time_str += " : ";

        if (minute < 10)
          time_str += '0';
        time_str += String(minute);

        time_str += " : ";

        if (second < 10)
          time_str += '0';
        time_str += String(second);

        if (pm == 1)
          time_str += " PM ";
        else
          time_str += " AM ";

      }
    }
    // emergency push button
  status = digitalRead(BUTTON_PIN);
  if(status==HIGH )
     {
      int val1 = 1;
       client.add("emergency", val1);
     }
     else {
      Serial.println("");
      Serial.println("There's no Emergency situation.");
     }
  
  
  pox.update();   // update pox for every 1 second
  float  temp = mlx.readObjectTempF();    // reading and storig temeprature value
  float pulse = pox.getHeartRate();       // reading and storig pulse level
  float  SpO2 = pox.getSpO2();            // reading and storig oxygen level 
  
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("Pulse: ");
    Serial.println(pox.getHeartRate());
    Serial.print("SpO2: ");
    Serial.print(pox.getSpO2());
    Serial.println("%");
    Serial.print("Temperature: ");
    Serial.print(mlx.readObjectTempF());
    Serial.println("*F");
    Serial.print("Time: ");
    Serial.println(time_str);
    Serial.print("Latitude: ");
    Serial.print(lat_str);
    Serial.print("  Longitude: ");
    Serial.println(lng_str);

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(0, 0);
    display.print("Pulse: ");
    display.println(pox.getHeartRate());
 
    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(0, 20);
    display.print("Spo2: ");
    display.println(pox.getSpO2());

    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(0, 30);
    display.print("Temp: ");
    display.print(mlx.readObjectTempC());
    display.println("*C");

    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(0, 40);
    display.print("Time: ");
    display.println(time_str);
    display.display();
    
    tsLastReport = millis();
  }
  
    // adding variables in ubidots cloud
    client.add("heart-rate", pulse);
    client.add("oxygen-level", SpO2);
    client.add("temperature", temp); 
    dtostrf(latitude, 4, 2, str_temp);
    dtostrf(longitude, 4, 2, str_temp2);
    char context[100]; // storing string data of latitude and longitude
    sprintf(context,"lat=%s,lng=%s",str_temp,str_temp2);
    client.ubidotsPublish("demo");
    client.add("gps",2, context);
    client.loop();
    delay(6000);

}
