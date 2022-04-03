#include <floor_utils.hpp>
#include <utils.hpp>

JsonFloor::JsonFloor(std::string jsonFileName){

  try{
    ifstream jsonBuffer(jsonFileName, ifstream::binary);
    jsonBuffer >> loadedJson;
  }catch(const std::exception& e){
    std::cerr << e.what() << '\n';
  }

  inputsComponents = loadResource("inputs");

  outputsComponents = loadResource("outputs");

  floorName = loadedJson["nome"];

  temperatureSensor = loadResource("sensor_temperatura")[0];

};

std::vector<component> JsonFloor::getOutputsComponents(){
  return outputsComponents;
}

std::vector<component> JsonFloor::getInputsComponents(){
  return inputsComponents;
}

component JsonFloor::getTemperatureSensorComponent(){
  return temperatureSensor;
}

std::vector<component> JsonFloor::loadResource(std::string targetKey){
  vector <component> auxVector;
  component auxComponent;

  for (auto& element : loadedJson[targetKey]) {
    auxComponent.type = element["type"];
    auxComponent.tag = element["tag"];
    auxComponent.gpio = element["gpio"];
    auxComponent.wpi_gpio = getWPiMappedPin(element["gpio"]);
    auxVector.push_back(auxComponent);
  }
  return auxVector;
}

std::string JsonFloor::getFloorName(){
  return floorName;
}

std::string JsonFloor::getCentralIp(){
  return loadedJson["ip_servidor_central"];
}

int JsonFloor::getCentralPort(){
  return (int)loadedJson["porta_servidor_central"];
}


std::vector<component> JsonFloor::getPeopleCounterSensors(){
  std::vector<component> sensors;

  for (auto& element : inputsComponents) {
    if(element.type == "contagem"){
      sensors.push_back(element);
    }
  }

  for (auto& element : sensors) {
    cout << "Sensor encontrado! -> " << element.tag << endl;
  }
  
  return sensors;

}

void JsonFloor::debug(){
  cout <<  "=========================================" << endl;
  // debug outputs --------------------------------------------------------------------------------
  cout << "[DEBUG] Loaded Output Components:"<< "\n\n";
  for (auto prop = outputsComponents.begin(); prop != outputsComponents.end(); ++prop){
    cout << prop->type << " ";
    cout << prop->tag << " ";
    cout << prop->gpio << " ";
    cout << prop->wpi_gpio << "\n\n";
  }
  // end debug ------------------------------------------------------------------------------------
  cout <<  "=========================================" << endl;

  // debug inputs ---------------------------------------------------------------------------------
  cout << "[DEBUG] Loaded Input Components:"<< "\n\n";
  for (auto prop = inputsComponents.begin(); prop != inputsComponents.end(); ++prop){
    cout << prop->type << " ";
    cout << prop->tag << " ";
    cout << prop->gpio << " ";
    cout << prop->wpi_gpio << "\n\n";
  }
  // end debug ------------------------------------------------------------------------------------
  cout <<  "=========================================" << endl;
}

JsonFloor::~JsonFloor(){
  cout<< "Adeus :(" << endl;
}