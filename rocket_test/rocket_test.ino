#include <Arduino.h>
#include "HX711.h"
#include <SD.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int IGNITER = 8;
const int LED = 9;
const int SD_ERROR = 7;
const int SD_SPI_CS = 5;
int i=0;
float thrust = 0;
int x = 0;

HX711 scale;
File myFile;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SD_ERROR, OUTPUT);
  pinMode(IGNITER, OUTPUT);
  
  Serial.begin(57600);

  if (!SD.begin(SD_SPI_CS)){
    Serial.println("SD CARD FAILED OR NOT PRESENT");
    digitalWrite(SD_ERROR, HIGH)
    while (1);
  }

  if (!SD.exists("data.txt")){
    Serial.println("data.txt does not exist, creating it now...");
    myFile = SD.open("data.txt", FILE_WRITE);
    myFile.close();
  }

  if (SD.exists("data.txt")){
    Serial.println("data.txt found, continuing...");
  }

  myFile = SD.open("data.txt", FILE_WRITE);

 
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
  thrust = scale.get_units();
  Serial.println(thrust);
  myFile.println(thrust);
  x++;
  if (x>49 && thrust<0.05){
    myFile.close();
    while (1);
  }
  delay(50);
}
