#ifndef __UTILS__
#define __UTILS__

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <json.hpp>

using namespace std;
struct component
{
  string type;
  string tag;
  int wpi_gpio;
};

vector<component> loadOutputAsArr();

int getWPiMappedPin(int gpioPin);

#endif