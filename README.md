# esp8266speedtest
Using the NodeMCU 1.0 V2 board equipped with an ESP8266 WiFi module I made a simple speed test that ping's Google.
All my source code is documented for easy reading and implementation.


The white LED indicates that the remote host server is being pinged, blue LED inicates that the response time is less than 50 MS, green LED inicates that the response time is greater than 50 and less than 100 MS, yellow LED inicates that the response time is greater than 10 and less than 200 MS, red LED inicates that the response time is greater than 200 MS.


# Hardware Required
1. NodeMCU MicroController with ESP8266 WiFi Module
2. Breadboard
3. 12 Male-to-Male jumper wires
4. 5 LEDs (white, blue, green, yellow, and red)
5. 5 1k OHM resistors


# NodeMCU Purchase Link (non-affiliated)
https://www.amazon.com/Makerfocus-ESP8266-ESP-12E-Internet-Development/dp/B01IK9GEQG


# Circuit Diagram
<img src="https://image.ibb.co/jBawDc/esp8266speedtest_bb.png"/>


# Circuit Picture
<img src="https://image.ibb.co/cgrBDc/esp8266speedtest_sideways.png"/>


# Pin map
<img src="https://image.ibb.co/e4DSKH/NODEMCU_DEVKIT_V1_0_PINMAP.png"/>


# Libraries Used:
ESP8266Ping: https://github.com/dancol90/ESP8266Ping

ESP8266Wifi: Built-in


# Pictures
<img src="https://image.ibb.co/jrVApH/IMG_20180427_211552.jpg" />


<img src="https://preview.ibb.co/bW9LpH/IMG_20180427_211603.jpg" />

