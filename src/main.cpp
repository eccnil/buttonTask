#include <Arduino.h>
#include "button.h"

#define pinBlue 32 //blinking led
#define pinGreen 33 //button associated led
#define pinButton 2 //button pin

Button btn (pinButton);

auto onclick = []() { 
  digitalWrite(pinGreen, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(pinGreen, LOW);
};

void setup() {
  pinMode(pinBlue, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  btn.init();
  btn.onClick = onclick;
}

void loop() {
  digitalWrite(pinBlue, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(pinBlue, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  btn.timer(millis());
}