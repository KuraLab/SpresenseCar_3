#include <Arduino.h>

// using namespace MAX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(asdf);

  pinMode(LED0, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED0, HIGH);
  delay(1000);
  digitalWrite(LED0, LOW);
  delay(1000);
}