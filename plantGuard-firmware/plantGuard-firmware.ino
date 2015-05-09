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

//  past 5s array      past 1m array     past 10m array     mean over last 5s, 1m, 10m
int brightness5s[5]  , brightness1m[12], brightness10m[10], brightnessMean[3];
int humidity5s[5]    , humidity1m[12]  , humidity10m[10]  , humidityMean[3];
int temp5s[5]        , temp1m[12]      , temp10m[10]      , tempMean[3];

//   when to get 1s data       when to get 5s data       when to get 1m data        // when to get 10m data
long data1s = millis() + 1000, data5s = millis() + 5000, data1m = millis() + 60000, data10m = millis() + 600000;
bool hasBeen1s = false       , hasBeen5s = false       , hasBeen1m = false        , hasBeen10m = false;

DHT dht; // humidity & temp

void setup() {
	delay(450);               // wait for serial to stabilize
	Serial.begin(57600);      // start talking fast
	dht.setup(DHTPin);        // initialize temp & humidity

}

void loop() {

	if(millis() >= data10m) {
		data10m += 600000;
		hasBeen10m = true;
	}

	if(millis() >= data1m) {
		data1m += 60000;
		hasBeen1m = true;
	}

	if(millis() >= data5s) {
		data5s += 5000;
		hasBeen5s = true;
	}

	if(millis() >= data1s) {
		data1s += 1000;
		hasBeen1s = true;
	}


	if(hasBeen1s == true) {
		Serial.println("has been 1s");
	}

	if(hasBeen5s == true) {
		Serial.println("has been 5s");
	}

	if(hasBeen1m == true) {
		Serial.println("has been 1m");
	}

	if(hasBeen10m == true) {
		Serial.println("has been 10m");
	}





	// get data
	brightnessMean[0] = analogRead(lightPin);
	humidityMean[0] = dht.getHumidity();
	tempMean[0] = dht.getTemperature();







	// every second, read data and add to 5s rolling average

	// every 5s, write 5s rolling average to 60s rolling average

	// every 10m, average past  

	// clear hasBeens
	hasBeen1s = false;
	hasBeen5s = false;
	hasBeen1m = false;
	hasBeen10m = false;

}















