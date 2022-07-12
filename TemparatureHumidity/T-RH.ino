/*****
   Brief: Code for ESP32 and DHT11
   :Sagar Chavan
*****/

#include <DHT.h> // Include library for dht

#define DHTPIN 4 // pin where the dht11 is connected

float humidity;
float temp;
DHT dht(DHTPIN, DHT11);

void setup()
{
    Serial.begin(115200);
    delay(10);
    dht.begin();
}

void loop()
{

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

    delay(10000);
}