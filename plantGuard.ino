//plantGuard.ino
// Copyright Sam Daitzman 2015
// CC CC BY-NC-SA License
// See http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
// Contact: samuel@daitzman.com
//          llamaswill@gmail.com
//          781-690-8717

// fetch from https://github.com/markruys/arduino-DHT
#include "DHT.h"

#define lightPin A1
#define DHTPin 2

int brightness, humidity, temp;

DHT dht;

void setup() {
	delay(450);
	Serial.begin(9600);
	pinMode(lightPin, INPUT);
	dht.setup(DHTPin);
}

void loop() {
	delay(dht.getMinimumSamplingPeriod());
	brightness = analogRead(lightPin);
	humidity = dht.getHumidity();
	temp = dht.getTemperature();
	// print brightness
	Serial.print("b");
	Serial.println(brightness);

	// print humidity
	Serial.print("h");
	Serial.println(humidity);
	
	// print temperature
	Serial.print("t");
	Serial.println(temp);
	
	// print hella simple checksum
	Serial.print("c");
	Serial.println(String(brightness + humidity + temp));
}
