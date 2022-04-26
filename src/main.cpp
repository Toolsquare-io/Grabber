#include <Arduino.h>

#define LEDPIN 13

void setup() {
  Serial.begin(9600);
  Serial.println("starting");
  // put your setup code here, to run once:
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  digitalWrite(LEDPIN, LOW);
  Serial.println("Low");
  delay(500);
  digitalWrite(LEDPIN, HIGH);
  Serial.println("High");
  delay(500);
}