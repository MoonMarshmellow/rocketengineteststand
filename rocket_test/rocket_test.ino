#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int IGNITER = 8;
const int LED = 13;
int i=0;

HX711 scale;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(IGNITER, OUTPUT);
  
  Serial.begin(57600);
 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(-45364);
  scale.tare();
  Serial.println("Armed. Beginning Test in 10 Seconds.");
  for(i=0; i<=9; i++) {
    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
    delay(500);
  }
  digitalWrite(IGNITER, HIGH);  
  delay(500);
  digitalWrite(IGNITER, LOW);  
}

void loop() {
  Serial.println(scale.get_units());
  delay(50);
}
