#include <WiFi.h>
#include "ThingSpeak.h"

char ssid[] = "OnePlus 9Pro 5G"; //SSID
char pass[] = "123456789"; // Password

WiFiClient  client;

unsigned long myChannelField =  1798810; // Channel ID
const int ChannelField =1; // Which channel to write data
const char * myWriteAPIKey = "V937FU3VFXGV01AF"; // Your write API Key

int led = 33;                // the pin that the LED is atteched to
int sensor = 12;              // the pin that the sensor is atteched to
int state;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

void setup() {
  pinMode(led,OUTPUT);      // initalize LED as an output
  pinMode(sensor,INPUT);    // initialize sensor as an input
  Serial.begin(115200);        // initialize serial
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop(){
   if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
    
  val = digitalRead(sensor);   // read sensor value
  
  if (val == HIGH) {          // check if the sensor is HIGH
    Serial.print("PIR  sensor is ");
    Serial.println( val);
    digitalWrite(led, HIGH);
    Serial.println("Motion detected!"); // turn LED ON
    delay(100);                // delay 100 milliseconds 
    } 
  else {
   Serial.print("PIR sensor is ");
     Serial.println("Motion stopped!");
      Serial.println( val);
      digitalWrite(led, LOW); // turn LED OFF
      delay(100);             // delay 200 milliseconds 
      
  }
     ThingSpeak.writeField(myChannelField, ChannelField,val, myWriteAPIKey);

}