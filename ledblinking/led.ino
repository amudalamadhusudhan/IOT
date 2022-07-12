const int led =33;
void setup() {
  // put your setup code here, to run once:
 pinMode(led,OUTPUT);
 Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(led,HIGH);
Serial.print("LED IS ON\n");
delay(500);
digitalWrite(led,LOW);
Serial.print("LED IS OFF\n");
delay(500);
}
