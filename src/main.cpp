#include <Arduino.h>
#include "button.h"

#define pinBlue 32 //blinking led
#define pinGreen 33 //button associated led
#define pinButton 26 //button pin

Button btn (pinButton);

auto onclick = []() { 
  digitalWrite(pinGreen, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(pinGreen, LOW);
  Serial.print("button - ");                    
  Serial.println(xPortGetCoreID());
};

void buttonTask (void *pvParameters){
  for(;;){
    btn.timer(millis());
    delay(10); //needed, now button runs too fast
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  btn.init();
  btn.onClick = onclick;
  TaskHandle_t buttonTaskH;
  
  // simple task creation 
  xTaskCreate(buttonTask, "button", 10000, NULL, 1, &buttonTaskH);

  // creattion pinned to core (loop runs on core 1)
  //xTaskCreatePinnedToCore(buttonTask, "button", 10000, NULL, 100, &buttonTaskH, 0);


}

//put something: delay or yield or cpu will starve
void loop() {
    digitalWrite(pinBlue, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(pinBlue, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
    Serial.print("loop - ");                    
    Serial.println(xPortGetCoreID());
}
