
# Setup of ESP32 with the Arduino
 Prerequisites:
 
    • PC Ubuntu(version > 16.04)
    
    • ESP32 Board(WROOM-32)
    
    • Arduino IDE(Latest version)
    
 Steps:
 
    • Install Arduino IDE if not installed.
    
    • sudo snap install arduino
    
    • After installation of Arduino IDE, open the IDE and go to file -> preferences
    
    • Now in the Additional boards manager URLs text box, paste the below links
    
    ◦ <https://dl.espressif.com/dl/package_esp32_index.json>,<http://arduino.esp8266.com/stable/package_esp8266com_index.json>
    
    • After pasting the URL click on OK.
    
    • Now go to Tools->Board->Boards Manager
    
    ◦ In this board manager, type ESP32 in the text box.
    
    • It shows esp32 by Espressif systems, select the version (prefer latest one) and then click on install.
    
    • It will take some time to install
    ◦ After installation, close the window.
    
    • This completes the ESP32 installation in the Arduino IDE.
    
 Configuration of ESP32 board in Arduino IDE:
 
    • Once installation is done, Select your Board in Tools > Board -> ESP32 Arduino -> FireBeetle-ESP32.
    
    • Then next select the COM port of your ESP32 in Tools-> ports.
    
    • This completes the ESP32 configuration with Arduino IDE.
    
    • Now you can write your programs, compile, and flash on ESP32 board through Arduino IDE.

![WhatsApp Image 2022-07-10 at 6 04 29 PM](https://user-images.githubusercontent.com/105910992/178448443-72730d8e-b2e1-4762-b824-2ca43ea28f34.jpeg)



                                                         THINGSPEAK
ThingSpeak is an IoT analytics platform service that allows you to aggregate, visualize, and analyze live data streams in the cloud. You can send data to ThingSpeak from your devices, create instant visualization of live data, and send alerts without setting up servers or developing web software.
Installing the ThingSpeak Library
To send sensor readings to ThingSpeak, we’ll use the thingspeak-arduino library. You can install this library through the Arduino Library Manager. Go to Sketch > Include Library > Manage Libraries… and search for “ThingSpeak” in the Library Manager. Install the ThingSpeak library by MathWorks.



ThingSpeak – Getting Started
Go to ThingSpeak an click the “Get Started For Free” button to create a new account. This account is linked to a Mathworks account. So, if you already have a Mathworks account, you should log in with that account.

Creating New Channel
After your account is ready, sign in, open the “Channels” tab and select “My Channels“.

Press the “New Channel” button to create a new channel.


Type a name for your channel and add a description.For example, If you want to publish multiple readings (like humidity and temperature), you can enable more fields as you’ll see later in this if needed.
ThingSpeak Edit Add New Channel Settings Configuration

Click the Save Channel button to create and save your channel.

Customizing Chart
The chart can be customized, go to your Private View tab and click on the edit icon.

API Key & channel ID
To send values from the ESP32 to ThingSpeak, you need the Write API Key.
Open your newly created channel and select the API Keys tab to copy your API Key.



# Mosquitto Brocker

## How to setup :
1. MQTT Brocker
2. MQTT Publisher
3. MQTT Subscriber

### MQTT Broker Local
 - on Ubuntu open terminal
 - command to install mosquitto brocker
```bash
sudo apt install mosquitto
sudo apt-get install mosquitto-clients 
```
- Start the brocker

```bash 
 sudo systemctl status mosquitto.service
 sudo systemctl stop mosquitto.service
 mosquitto -v
```
```bash
open new terminal 
mosquitto_sub -t test 
it waits for the message
```
```bash
open new terminal2 
mosquitto_pub -t test -m "hello" 
it sends the message
```

### MQTT Brocker 
- On either Ubuntu or on Raspberry Pi
- Command to install mosquitto brocker

```bash
sudo apt install mosquitto
sudo apt-get install mosquitto-clients 
```
- Start the brocker

```bash 
sudo systemctl status mosquitto.service
sudo systemctl stop mosquitto.service
In home of the teminal create a filename.txt using following data
             listener 1883
             allow_anonymous true
mosquitto -c filename.txt -v 
```

### 2. MQTT Publisher
 - On other Raspberry Pi or Ubuntu terminals
- Command to install mosquitto 

```bash
sudo apt-get install mosquitto
sudo apt-get install mosquitto-clients
```
- Now start sending data 

```bash 
mosquitto_pub -h ipaddress -t test -m "Hello from Raspberry Pi" # ip of brocker
```

### 3. MQTT Subscriber
- On other Raspberry Pi or Ubuntu terminals
- Command to install mosquitto 
- Now start receiving data 

```bash
mosquitto_sub -h ipaddress -t test # ip of Brocker
```

### MQTT Dashboard (Mobile Application)
- Enter the details of your brocker
  - Brocker Name: mosquitto (or any name)
  - Address of brocker: 192.168.43.75 (ip adress)
  - Port number: 1883 or 8883
  - Client Id: MqttDashboard-1341078
  - topic: test 

- Save all these details
- Now we have enter topic name: test
- all device has to be connected to same network use ifconfig to find ip address


### For More info 
[mosquitto_Auth](https://mosquitto.org/documentation/authentication-methods/)



