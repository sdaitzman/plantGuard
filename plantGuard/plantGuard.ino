//plantGuard.ino
// Copyright Sam Daitzman 2015
// CC CC BY-NC-SA License
// See http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
// Contact: samuel@daitzman.com
//          llamaswill@gmail.com
//          781-690-8717

// fetch from https://github.com/markruys/arduino-DHT
#include "DHT.h"

#define lightPin A1                  // light sensor
#define DHTPin 2                     // humidity & temp sensor
#define dataWriteFreq 1000 * 60 * 10 // write data every 10 minutes

int brightness, humidity, temp;

DHT dht; // humidity & temp

void setup() {
	delay(450);               // wait for serial to stabilize
	Serial.begin(9600);       // start talking
	pinMode(lightPin, INPUT); // set light sensor pin to INPUT
	dht.setup(DHTPin);        // initialize temp & humidity
}

void loop() {
	delay(dht.getMinimumSamplingPeriod()); // wait a little

	// get data
	brightness = analogRead(lightPin);
	humidity = dht.getHumidity();
	temp = dht.getTemperature();
	
	// print hella simple checksum
	Serial.print("c");
	Serial.print(brightness + humidity + temp);
	Serial.print(".");

	// print brightness
	Serial.print(brightness);
	Serial.print(".");

	// print humidity
	Serial.print(humidity);
	Serial.print(".");

	// print temperature
	Serial.print(temp);
	Serial.print(".");

	// print checksum again
	Serial.println(String(brightness + humidity + temp));
}
