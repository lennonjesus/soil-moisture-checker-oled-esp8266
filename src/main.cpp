#include <Arduino.h>
#include "SSD1306Wire.h"
#include "Wire.h"

/* OLED */
const int I2C_DISPLAY_ADDRESS = 0x3c;
const int SDA_PIN = D2;
const int SCL_PIN = D1;
SSD1306Wire display(I2C_DISPLAY_ADDRESS, SDA_PIN, SCL_PIN);

int soilMoisture = 0;
String soilMoistureState = "???";
bool isSoilDry = false;

void readSoilMoisture();
void displaySoilMoisture();
void displaySetup();

void setup() {
  Serial.begin(115200);
  displaySetup();
}

void loop() {
  Serial.println("Blah!");
  readSoilMoisture();
  delay(1000);
  displaySoilMoisture();
  delay(3000);
}

void readSoilMoisture() {

  delay(500);

  soilMoisture = 100 - (analogRead(A0) * 100 ) / 1023;
  Serial.println(soilMoisture);

  if (soilMoisture <= 30) {
    soilMoistureState = "Seco";
    isSoilDry = true;
    Serial.println(soilMoistureState);
  }
 
  if (soilMoisture > 30 && soilMoisture <= 50) {
    soilMoistureState = "Moderado";
    Serial.println(soilMoistureState); 
  }
   
  if (soilMoisture > 50 && soilMoisture <= 85) {
    soilMoistureState = "Umido";
    Serial.println(soilMoistureState);
  }

  if (soilMoisture > 85) {
    soilMoistureState = "Encharcado";
    Serial.println(soilMoistureState);
  }
}

void displaySoilMoisture() {
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "Solo");
  display.drawString(0, 23, "Umid: " + String(soilMoisture) + "%" );
  display.drawString(0, 48, "Est: " + soilMoistureState);
  display.display();
}

void displaySetup() {
  display.init();
  display.clear();
  display.display();
  
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 0, "Smart Garden");
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 52, "SW Ver.:");
  display.drawString(45, 52, "0.0.1");
  display.display();

  delay(500);
}