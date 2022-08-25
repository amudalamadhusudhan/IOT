#include "ThingSpeak.h"
#include "WiFi.h"
#include <DHT.h> // Include library for dht

//----------- Enter you Wi-Fi Details---------//
char ssid[] = "OnePlus 9Pro 5G"; // SSID
char pass[] = "123456789";       // Password
//-------------------------------------------//

#define DHTPIN 4 // pin where the dht11 is connected
#define Light 15
#define led 33
float humidity;
float temp;
DHT dht(DHTPIN, DHT11);
WiFiClient client;

unsigned long myChannelField = 1798218; // Channel ID
const int ChannelField = 1;             // Which channel to write data
const int ChannelField1 = 2;
const int ChannelField2 = 3;
const char *myWriteAPIKey = "A4M2Y9ENMZNXQV2A"; // Your write API Key

void setup()
{
    Serial.begin(115200);
    dht.begin();
    WiFi.mode(WIFI_STA);
    ThingSpeak.begin(client);
          delay(100);
    pinMode(Light, INPUT);
    pinMode(led, OUTPUT);
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
    //measuring the temparature and humidity

    humidity = dht.readHumidity(); // read humidity for sensor
    temp = dht.readTemperature();  // read temperature for sensor

    if (isnan(humidity) || isnan(temp))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    /* printing the results on console*/
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" degrees Celcius, Humidity: ");
    Serial.print(humidity);
    Serial.println();
    // measuring the light intensity
    int val = analogRead(Light);

    if (val > 500)
    {
        digitalWrite(led, LOW);
        Serial.println(val);
        Serial.print("MORE LIGHT- day\n");
    }
    else
    {
        digitalWrite(led, HIGH);
        Serial.println(val);
        Serial.print("LOW LIGHT-night\n");
    }
    delay(1000);
    ThingSpeak.writeField(myChannelField, ChannelField, temp, myWriteAPIKey);
    ThingSpeak.writeField(myChannelField, ChannelField1, humidity, myWriteAPIKey);
    ThingSpeak.writeField(myChannelField, ChannelField2,val, myWriteAPIKey);
    delay(1000); 
}