#ifndef __GPIO__
#define __GPIO__

#include <iostream>
#include <wiringPi.h>
#include <floor_utils.hpp>

using namespace std;

void initWiringpi();
string readPinAsStr(int pin);
void setPinValue(int pin, int value);
string returnAllReadAsString(vector<component> sensors, string keyValueSeparator, string endSeparator, int leftShift);

#endif