#include <Servo.h>

Servo myservo;
int vcc = 7;          // Actually I needed more pin for VCC
int trigPin = 11;     // Trigger
int echoPin = 12;     // Echo
int t_sanit = 3;

void do_sanitize();
long calculate_distance();

void setup() {
  myservo.attach(9);
  Serial.begin (9600);
  pinMode(vcc, OUTPUT);
  digitalWrite(vcc, HIGH);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (calculate_distance() <= 3)
  {
    for (int i = 0; i < t_sanit; i++)
    {
      do_sanitize();
    }
    delay(2000);
  }
}

void do_sanitize() {
  Serial.println("+++++++++++++++++++++++++++++sanitizing");
  int t_pos = 90;
  int pos = 0;
  for (pos = 0; pos <= t_pos; pos += 1) {
    myservo.write(pos);
    //Serial.print(pos);
    //Serial.print("\t");
    delay(5);
  }
  for (pos = t_pos; pos >= 0; pos -= 1) {
    myservo.write(pos);
    //Serial.print(pos);
    //Serial.print("\t");
    delay(5);
  }
}

long calculate_distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  long duration = pulseIn(echoPin, HIGH);
  return (duration / 2) / 74;
}
