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
  int wpi_gpio;
};

class JsonFloor{
  private:
    nlohmann::json loadedJson;
    std::vector<component> outputsComponents;
    std::vector<component> inputsComponents;
    component dht22Component;

  public:
    JsonFloor(std::string jsonFileName);
    std::vector<component> getOutputsComponents();
    std::vector<component> getInputsComponents();
    component getDht22Component();
    ~JsonFloor();
};

vector<component> loadResource(string targetResource, bool debug = false); 
string getFloorName();

#endif