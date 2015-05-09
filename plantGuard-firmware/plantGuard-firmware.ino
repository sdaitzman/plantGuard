//plantGuard.ino
// Copyright Sam Daitzman 2015
// CC CC BY-NC-SA License
// See http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
// Contact: samuel@daitzman.com
//          llamaswill@gmail.com
//          781-690-8717

// fetch from https://github.com/markruys/arduino-DHT
#include "DHT.h"
#include <Average.h>

#define lightPin A1                  // light sensor
#define DHTPin 2                     // humidity & temp sensor

Average<int> brightness5s(5)  , brightness1m(12), brightness10m(10);
Average<int> humidity5s(5)    , humidity1m(12)  , humidity10m(10)  ;
Average<int> temp5s(5)        , temp1m(12)      , temp10m(10)      ;

int brightnessMean[4], humidityMean[4], tempMean[4];

//   when to get 1s data       when to get 5s data       when to get 1m data        // when to get 10m data
long data1s = millis() + 1000, data5s = millis() + 5000, data1m = millis() + 60000, data10m = millis() + 600000;
bool hasBeen1s = false       , hasBeen5s = false       , hasBeen1m = false        , hasBeen10m = false;

DHT dht; // humidity & temp

void setup() {
	delay(2000);               // wait for serial to stabilize
	Serial.begin(57600);       // start talking fast
	dht.setup(DHTPin);         // initialize temp & humidity

	delay(2000);

	initializeRollingMeans(); // seed rolling averages with current values

}

void loop() {

	checkTimers();

	// if has been one second
	if(hasBeen1s == true) {
		getReadings(); // get sensor values
		brightness5s.push(brightnessMean[0]);
		humidity5s.push(humidityMean[0]);
		temp5s.push(tempMean[0]);
	}

	// if has been 5 seconds
	if(hasBeen5s == true) {
		brightnessMean[1] = brightness5s.mean();
		humidityMean[1] = humidity5s.mean();
		tempMean[1] = temp5s.mean();
		printData(1);
	}

	// if has been one minute
	if(hasBeen1m == true) {
		brightnessMean[2] = brightness1m.mean();
		humidityMean[2] = humidity1m.mean();
		tempMean[2] = temp1m.mean();
		printData(2);
	}

	// if has been 10 minutes
	if(hasBeen10m == true) {
		brightnessMean[3] = brightness10m.mean();
		humidityMean[3] = humidity10m.mean();
		tempMean[3] = temp10m.mean();
		printData(3);
	}

	resetHasBeens();
}

// initialize rolling means to current values
void initializeRollingMeans() {
	getReadings(); // get sensor values

	// set 5s rolling average
	for(int i = 0;i<5;i++) {
		brightness5s.push(brightnessMean[0]);
		humidity5s.push(humidityMean[0]);
		temp5s.push(tempMean[0]);
	}

	// set 1m rolling average
	for(int i = 0;i<12;i++) {
		brightness1m.push(brightnessMean[0]);
		humidity1m.push(humidityMean[0]);
		temp1m.push(tempMean[0]);
	}

	// set 10m rolling average
	for(int i = 0;i<10;i++) {
		brightness10m.push(brightnessMean[0]);
		humidity10m.push(humidityMean[0]);
		temp10m.push(tempMean[0]);
	}
}

// check timers
void checkTimers() {
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
}

// get readings from sensors
void getReadings() {
	brightnessMean[0] = analogRead(lightPin);
	humidityMean[0] = dht.getHumidity();
	tempMean[0] = dht.getTemperature();
}

// clear hasBeens
void resetHasBeens() {
	hasBeen1s = false;
	hasBeen5s = false;
	hasBeen1m = false;
	hasBeen10m = false;
}

// print data out at index
// index 0 = past 1s, index 1 = past 5s, index 2 = past 1m, index 3 = past 10m
void printData(int index) {
	// first print random number for checksum
	unsigned int randomCheck = random(0, 65535);
	Serial.print("[");
	Serial.print(randomCheck);           Serial.print(" ");

	// print actual data
	Serial.print(brightnessMean[index]); Serial.print(" ");
	Serial.print(humidityMean[index]);   Serial.print(" ");
	Serial.print(tempMean[index]);       Serial.print(" ");

	// now for a hella simple checksum
	Serial.print(brightnessMean[index] + humidityMean[index] + tempMean[index] + randomCheck);
	Serial.println("]");
}












