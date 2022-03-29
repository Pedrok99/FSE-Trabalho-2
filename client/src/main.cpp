#include <fstream>
#include <json.hpp>
#include <gpio.hpp>
#include <wiringPi.h>
#include <utils.hpp>

using namespace std;

int main(){

  vector<component> outputs;
  outputs = loadOutputAsArr();
  wiringPiSetup();

  for(auto elem : outputs){
    pinMode(elem.wpi_gpio, OUTPUT);
    digitalWrite(elem.wpi_gpio, LOW);
  }
  // wiringPiSetup();
  // for (auto prop = outputs.begin(); prop != outputs.end(); ++prop){
  //   pinMode(prop->wpi_gpio, OUTPUT);
  //   digitalWrite(prop->wpi_gpio, LOW);
  // }

  return 0;
}