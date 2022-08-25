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

