#include "ThingSpeak.h"
#include "WiFi.h"
#include <DHT.h> // Include library for dht11 temperature sensor
#include <Wire.h>
#define MYALTITUDE 262
// Register addresses
const int SENSORADDRESS = 0x60; // MPL3115A1 address from the datasheet
#define SENSOR_CONTROL_REG_1 0x26
#define SENSOR_DR_STATUS 0x00 // Address of DataReady status register
#define SENSOR_OUT_P_MSB 0x01 // Starting address of Pressure Data registers

char ssid[] = "Madhusudhan amudala";
char pass[] = "123456789";

#define DHTPIN 4 // pin where the dht11 is connected
#define Light 15
#define led 33
float humidity;
float temp;
double pressure;
DHT dht(DHTPIN, DHT11);
WiFiClient client;

unsigned long myChannelField = 1798218; // Channel ID
const int ChannelField = 1;             // Which channel to write data
const int ChannelField1 = 2;
const int ChannelField2 = 3;
const int ChannelField3 = 4;
const int ChannelField4 = 5;
const char *myWriteAPIKey = "A4M2Y9ENMZNXQV2A"; // Your write API Key
byte I2Cdata[5] = {0, 0, 0, 0, 0};              // buffer for sensor data

void setup()
{
    Serial.begin(115200);
    dht.begin();
    WiFi.mode(WIFI_STA);
    ThingSpeak.begin(client);
    delay(100);
    pinMode(Light, INPUT);
    pinMode(led, OUTPUT);

    I2C_Write(SENSOR_CONTROL_REG_1, 0b00000000);
    I2C_Write(SENSOR_CONTROL_REG_1, 0b00111000);
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
    temphum();

    // measuring the light intensity
    lightintensity();
    // measuring the windspeed
    windspeed();
    // meassuring the pressure
    pressureVal();
    // thinkspeak
    thingspeak();
}
void temphum()
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
}
void lightintensity()
{
    int val = analogRead(Light);

    if (val > 500)
    {
        digitalWrite(led, LOW);
        Serial.println(val);
        Serial.print("DAY LIGHT\n");
    }
    else
    {
        digitalWrite(led, HIGH);
        Serial.println(val);
        Serial.print("LOW LIGHT\n");
    }
    delay(1000);
}
void windspeed()
{
    float sensorValue = analogRead(A0);
    Serial.print("Analog Value =");
    Serial.println(sensorValue);

    float voltage = (sensorValue / 1024) * 5; // Arduino ADC resolution 0-1023
    Serial.print("Voltage =");
    Serial.print(voltage);
    Serial.println(" V");

    float wind_speed = mapfloat(voltage, 0.4, 2, 0, 32.4);
    float speed_mph = ((wind_speed * 3600) / 1609.344);
    Serial.print("Wind Speed =");
    Serial.print(wind_speed);
    Serial.println("m/s");
    Serial.print(speed_mph);
    Serial.println("mph");

    lcd.setCursor(0, 0);
    lcd.print("Wind Speed");
    // Here cursor is placed on second line
    lcd.setCursor(0, 1);
    lcd.print(wind_speed);
    lcd.print("m/s");

    Serial.println(" ");
    delay(300);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void thingspeak()
{
    ThingSpeak.writeField(myChannelField, ChannelField, temp, myWriteAPIKey);
    ThingSpeak.writeField(myChannelField, ChannelField1, humidity, myWriteAPIKey);
    ThingSpeak.writeField(myChannelField, ChannelField2, val, myWriteAPIKey);
    ThingSpeak.writeField(myChannelField, ChannelField3, speed_mph, myWriteAPIKey);
    ThingSpeak.writeField(myChannelField, ChannelField4, baropressure, myWriteAPIKey);
    delay(1000);
}

void pressureVal()
{
    float baroAltitudeCorrectionFactor = 1 / (pow(1 - MYALTITUDE / 44330.77, 5.255877));
    float temperature, pressure, baroPressure;
    Read_Sensor_Data();
    pressure = Calc_Pressure();
    baroPressure = pressure * baroAltitudeCorrectionFactor;
    Serial.print("Absolute pressure: ");
    Serial.print(pressure); // in Pascal
    Serial.print(" Pa, Barometer: ");
    Serial.print(baroPressure); // in Pascal

    void Read_Sensor_Data()
    {
        I2C_Write(SENSOR_CONTROL_REG_1, 0b00111010);
        do
        {
            Wire.requestFrom(SENSORADDRESS, 1);
        } while ((Wire.read() & 0b00000010) != 0);

        I2C_ReadData();
    }
    float Calc_Pressure()
    {
        unsigned long m_pressure = I2Cdata[0];
        unsigned long c_pressure = I2Cdata[1];
        float l_pressure = (float)(I2Cdata[2] >> 4) / 4;
        return ((float)(m_pressure << 10 | c_pressure << 2) + l_pressure);
    }
    void I2C_ReadData()
    {
        byte readUnsuccessful;
        do
        {
            byte i = 0;
            byte dataStatus = 0;
            Wire.beginTransmission(SENSORADDRESS);
            Wire.write(SENSOR_OUT_P_MSB);
            Wire.endTransmission(false);

            Wire.requestFrom(SENSORADDRESS, 5);
            while (Wire.available())
                I2Cdata[i++] = Wire.read();

            Wire.beginTransmission(SENSORADDRESS);
            Wire.write(SENSOR_DR_STATUS);
            Wire.endTransmission(false);
            Wire.requestFrom(SENSORADDRESS, 1);
            dataStatus = Wire.read();
            readUnsuccessful = (dataStatus & 0x60) != 0;

        } while (readUnsuccessful);
    }

    void I2C_Write(byte regAddr, byte value)
    {
        Wire.beginTransmission(SENSORADDRESS);
        Wire.write(regAddr);
        Wire.write(value);
        Wire.endTransmission(true);
    }
}