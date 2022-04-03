#ifndef __FLOOR_UTILS__
#define __FLOOR_UTILS__

#include <vector>
#include <string>
#include <fstream>
#include <json.hpp>
#include <iostream>


using namespace std;
struct component
{
  string type;
  string tag;
  int gpio;
  int wpi_gpio;
};

class JsonFloor{
  private:
    nlohmann::json loadedJson;
    std::string floorName;
    std::vector<component> outputsComponents;
    std::vector<component> inputsComponents;
    component temperatureSensor;
    std::vector<component> loadResource(std::string targetKey);

  public:
    JsonFloor(std::string jsonFileName);
    std::vector<component> getOutputsComponents();
    std::vector<component> getInputsComponents();
    std::vector<component> getPeopleCounterSensors();
    component getTemperatureSensorComponent();
    std::string getFloorName();
    std::string getCentralIp();
    int getCentralPort();
    void debug();
    ~JsonFloor();
};

#endif