#include <Printers.h>
#include <XBee.h>

#include <SD.h>

//This code records the percent moisture from 11 moisture sensors and
//saves them to an SD card, along with the date and time of the reading.
//also reads and prints amount of rain fallen

#include <DS3231.h>
#include <avr/sleep.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <DateTime.h>

DS3231 rtc(SDA,SCL);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  void sync(time_t time);
  long UnixTime = rtc.getUnixTime(rtc.getTime());  //read Unix time
  int Time = (int)UnixTime;
  Serial.println("The time is");
  Serial.println(Time);
}
