#ifndef __UTILS__
#define __UTILS__

#include <wiringPi.h>

using namespace std;

int getWPiMappedPin(int gpioPin);
void people_counter(int increment_pin, int decrement_pin, void (*increment_function)(), void (*decrement_function)());
#endif