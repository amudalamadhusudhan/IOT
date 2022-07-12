#define Light 2
#define led 33

void setup()
{

    Serial.begin(9600);
    delay(100);
    pinMode(Light, INPUT);
    pinMode(led, OUTPUT);
}

void loop()
{
    int val = analogRead(Light);

    if (val > 500)
    {
        digitalWrite(led, LOW);
        Serial.println(val);
        Serial.print("MORE LIGHT\n");
    }
    else
    {
        digitalWrite(led, HIGH);
        Serial.println(val);
        Serial.print("LOW LIGHT\n");
    }
    delay(100);
}