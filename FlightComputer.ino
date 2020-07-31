#include <SD.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

const int CS_PIN = 10;

float PRES;
float P0;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciant:");
  pinMode(CS_PIN, OUTPUT);
  Serial.println("Buscnat SD Card:");
  if(!SD.begin()){
    Serial.println("SD Card no identificada!");
    while(1);
  }
  Serial.println("SD Card iniciada.");
  if(!bmp.begin()){
    Serial.println("Sensor BMP280 no identificat!");
    while(1);
  }
  Serial.println("Sensor BMP280 iniciat.");
  P0 = bmp.readPressure()/100;
}

void loop() {
  long timeStamp = millis();

  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile){
    dataFile.print(timeStamp);
    dataFile.print(",");
    dataFile.println(bmp.readAltitude(P0));
    dataFile.close();

    Serial.print(timeStamp);
    Serial.print(",");
    Serial.println(bmp.readAltitude(P0));
  }
  else{
    Serial.println("Incapacitat per obrir el log");
  }
  delay(5000);

}
