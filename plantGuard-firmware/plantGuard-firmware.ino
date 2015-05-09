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

//  past 5s array      past 1m array     past 10m array     // mean over last 5s, 1m, 10m
int brightness5s[5]  , brightness1m[12], brightness10m[10], brightnessMean[3];
int humidity5s[5]    , humidity1m[12]  , humidity10m[10]  , humidityMean[3];
int temp5s[5]        , temp1m[12]      , temp10m[10]      , tempMean[3];

DHT dht; // humidity & temp

void setup() {
	delay(450);               // wait for serial to stabilize
	Serial.begin(9600);       // start talking
	dht.setup(DHTPin);        // initialize temp & humidity

}

void loop() {
	delay(dht.getMinimumSamplingPeriod()); // wait a little

	// get data
	brightnessMean[0] = analogRead(lightPin);
	humidityMean[0] = dht.getHumidity();
	tempMean[0] = dht.getTemperature();
	
	for(int i = 0;i<3;i++) {
		Serial.println(brightnessMean[i]);
	}




	// every second, read data and add to 5s rolling average

	// every 5s, write 5s rolling average to 60s rolling average

	// every 10m, average past  


}















