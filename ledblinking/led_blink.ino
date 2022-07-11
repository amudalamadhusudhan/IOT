const int led =22;

void setup() {
  // put your setup code here, to run once:
 pinMode(led,OUTPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(led,HIGH);
Serial.print("LED IS ON\n");
delay(5000);
digitalWrite(led,LOW);
Serial.print("LED IS OFF\n");
delay(5000);
}
