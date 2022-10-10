#include "ThingSpeak.h"
#include "WiFi.h"
#include <dht.h> // Include library for dht

//----------- Enter you Wi-Fi Details---------//
char ssid[] = "Madhusudhan amudala"; // SSID
char pass[] = "12345678";       // Password
//-------------------------------------------//

#define dht_apin A0 // Analog Pin sensor is connected to
#define fan 2 
#define bulb 3
#define light 4
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
    pinMode(fan, OUTPUT);
    pinMode(bulb, OUTPUT);
    pinMode(light, OUTPUT); 
    //humidity and temperture
    //Serial.begin(9600);
    delay(500);//Delay to let system boot
    Serial.println("DHT11 Humidity & temperature Sensor\n\n");
    delay(1000);//Wait before accessing Sensor 
    //touch sensor
    pinMode(2, INPUT);
}
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
    // measuring the temparature and humidity
    temphumi();

        // Voice Assisted Control of home
        voice();
        //Monitor the room temp
        flame();
        //Use haptic feedback to wake up the device
        touch();
        //Monitor the outside light to control inside light
        light();
 // thinkspeak
 thingspeak();
}       

//temp sensor
dht DHT;

void temphumi()
{
    DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C");
    delay(5000);
}
//Voice Assisted Control of home (voice sensor) 
void voice()
{
   if(Serial.available() == 1)
  
  {
    String val = Serial.readString();
    Serial.println(val);
    if(val == "fan on")
    {
      digitalWrite(fan, HIGH);
    }
    if(val == "fan off")
    {
      digitalWrite(fan, LOW);
    }
    if(val == "bulb on")
    {
      digitalWrite(bulb, HIGH);
    }
    if(val == "bulb off")
    {
      digitalWrite(bulb, LOW);
    }
    if(val == "light off")
    {
      digitalWrite(light, LOW);
    }
    if(val == "light on")
    {
      digitalWrite(light, HIGH);
    }
    if(val == "all on")
    {
      digitalWrite(fan, HIGH);
      digitalWrite(bulb, HIGH);
      digitalWrite(light,HIGH);
    }
    if(val == "all off")
    {
      digitalWrite(bulb, LOW);
      digitalWrite(fan, LOW);
      digitalWrite(light, LOW);
    }
  }
}

//flame sensor
// lowest and highest sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum
void flame()
{
    // read the sensor on analog A0:
  int sensorReading = analogRead(A0);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  
  // range value:
  switch (range) {
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("** Close Fire **");
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("** Distant Fire **");
    break;
  case 2:    // No fire detected.
    Serial.println("No Fire");
    break;
  }
  delay(1);  // delay between reads
}

//Touch sensor
void touch()
{
  if (digitalRead(2) == HIGH);
  Serial.println("Sensor is touched");
  delay(500);
}

//light sensor
void light()
{
  int value = analogRead(A0);
  Serial.println("Analog value : ");
  Serial.println(value);
  delay(250);
}  

void thingspeak()
{
   ThingSpeak.writeField(myChannelField, ChannelField, temp, myWriteAPIKey);
    ThingSpeak.writeField(myChannelField, ChannelField1, humidity, myWriteAPIKey);
    ThingSpeak.writeField(myChannelField, ChannelField2, val, myWriteAPIKey);
    delay(1000);
}  
  
}
