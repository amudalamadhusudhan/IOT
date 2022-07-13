#include "ThingSpeak.h"
#include "WiFi.h"
  
//----------- Enter you Wi-Fi Details---------//
char ssid[] = "OnePlus 9Pro 5G"; //SSID
char pass[] = "123456789"; // Password
//-------------------------------------------//

const int trigger = 5;//16;
const int echo = 18;//5;
long T;
float distanceCM;
WiFiClient  client;

unsigned long myChannelField =  1798665; // Channel ID
const int ChannelField =1; // Which channel to write data
const char * myWriteAPIKey = "95400XBH1DR4499O"; // Your write API Key

void setup()
{
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}
void loop()
{
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
  
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  T = pulseIn(echo, HIGH);
  distanceCM = T * 0.034;
  distanceCM = distanceCM / 2;
  Serial.print("Distance in cm: ");
  Serial.println(distanceCM);
  ThingSpeak.writeField(myChannelField, ChannelField, distanceCM, myWriteAPIKey);
  delay(1000);
}