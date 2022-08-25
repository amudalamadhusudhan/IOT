![PIR_Schematic](https://user-images.githubusercontent.com/105910992/178787347-ecc7ec11-7679-4c7b-9464-42487a53e006.png)
![Screenshot from 2022-07-13 22-17-28](https://user-images.githubusercontent.com/105910992/178787667-80ce9338-948e-4535-8673-31b42869a785.png)
PIR Sensor to detect human

	• Connect ESP32 to PC via USB cable
	• Connect PIR sensor to Digital Pin (D22)
	• Connect LED +ve terminal to digital IO pin (D12)
	• Connect LED -ve terminal to resistor & resistor to other terminal to GND
	• Turns on and off LED connected on digital pin when PIR sensor detects the human object.

Software:

	• Open the Arduino IDE & Select the ESP32 Board & Port in the Tools.
	• Add Library for Thingspeak and WiFi. → “Thingspeak.h” and “WiFi.h”.
	• Define Pinouts for the PIR sensor and LED. 
	• Define Credentials for the ThingsPeak.
	• Set baud rate 
	• Set Pin Mode - Input/Output.
	• Initialize WiFi Mode and Thingpeak.
	• Wait for the wifi to connect and proceed with below steps. 
	• Start measuring the values of the sensor – HIGH and LOW. On High, LED will glow (ON) and On Low, LED will OFF.
	• Upload the measured value (HIGH or LOW) on Thingspeak.
