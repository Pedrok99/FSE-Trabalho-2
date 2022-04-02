#include <floor_utils.hpp>
#include <utils.hpp>

vector<component> loadResource(string targetResource, bool debug){
  vector <component> tempArr;
  component tempComponent;
  nlohmann::json jsonCfg;

  ifstream jsonBuffer("groundCfg.json", ifstream::binary);
  jsonBuffer >> jsonCfg;
  for (auto& element : jsonCfg[targetResource]) {
    tempComponent.type = element["type"];
    tempComponent.tag = element["tag"];
    tempComponent.wpi_gpio = getWPiMappedPin(element["gpio"]);
    tempArr.push_back(tempComponent);
  }
  // debug
  if(debug){
    for (auto prop = tempArr.begin(); prop != tempArr.end(); ++prop){
      cout << prop->type << " ";
      cout << prop->tag << " ";
      cout << prop->wpi_gpio << "\n\n";
   }
  }
  
  return tempArr;
}

JsonFloor::JsonFloor(std::string jsonFileName){
  vector <component> tempArr;
  component tempComponent;

  try
  {
    ifstream jsonBuffer(jsonFileName, ifstream::binary);
    jsonBuffer >> loadedJson;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  for (auto& element : loadedJson["outputs"]) {
    tempComponent.type = element["type"];
    tempComponent.tag = element["tag"];
    tempComponent.wpi_gpio = getWPiMappedPin(element["gpio"]);
    tempArr.push_back(tempComponent);
  }
  // debug
  
    for (auto prop = tempArr.begin(); prop != tempArr.end(); ++prop){
      cout << prop->type << " ";
      cout << prop->tag << " ";
      cout << prop->wpi_gpio << "\n\n";
   }
  
  outputsComponents = tempArr;

};

std::vector<component> JsonFloor::getOutputsComponents(){
  return outputsComponents;
}

std::vector<component> JsonFloor::getInputsComponents(){
  return inputsComponents;
}

JsonFloor::~JsonFloor(){
  cout<< "Adeus :(" << endl;
}