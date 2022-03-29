#ifndef __UTILS__
#define __UTILS__

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <wiringPi.h>

using namespace std;
struct component
{
  string type;
  string tag;
  int wpi_gpio;
};

vector<component> loadOutputAsArr();

int getWPiMappedPin(int gpioPin);
void people_counter(int increment_pin, int decrement_pin, void (*increment_function)(), void (*decrement_function)());
#endif