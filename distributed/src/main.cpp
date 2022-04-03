#include <fstream>
#include <json.hpp>
#include <gpio.hpp>
#include <wiringPi.h>
#include <utils.hpp>
#include <thread>
#include <unistd.h>
#include <dht22.hpp>
#include <socket_tcp.hpp>
#include <floor_utils.hpp>

#define PACKAGE_MAX_SIZE 1024

using namespace std;

volatile int is_running = true;
volatile int people_on_floor = 0;

void dec(){people_on_floor--;}
void inc(){people_on_floor++;}
void init_people_counter(int increment_pin, int decrement_pin){
  people_counter(increment_pin, decrement_pin, &inc, &dec);
}

void createAndSendPackage(std::string floorName, std::vector<component> componentVector, int dhtPin, int sock){
  int leftShift = 2;
  dht22 dhtData;
  char separator = ';', s_end = '\0';
  string package, readData, people_counter, umi_temp;

  floorName =  "andar:" + floorName + separator;

  while (1)
  {
    people_counter = "people_counter:" + to_string(abs(people_on_floor)) + separator;
    dhtData = readSafeTemperature(dhtPin, dhtData);
    umi_temp = "temperatura:"+to_string(dhtData.temperature)+ separator +"umidade:" + to_string(dhtData.humidity)+ separator;

    for (auto prop = componentVector.begin(); prop != componentVector.end()-leftShift; ++prop){
      readData = prop->tag + ":" + to_string(digitalRead(prop->wpi_gpio)) + separator;
      package = package + readData;
    }

    package = floorName + package + people_counter + umi_temp + s_end;
    cout << "Package to send : " << package << endl;
    cout << "Package size: " << package.size() << endl;
    
    sendMsg(sock, (char*)package.c_str(), PACKAGE_MAX_SIZE);

    package.clear();
    usleep(1000000);
  }
  
}

int main(int argc, char *argv[]){
  
  if(argc < 2){
    cout << "\nUm arquivo de configuração deve ser enviado via linha de comando. Saindo...\n" << endl;
    return 0; 
  }
  cout << "\nArquivo de configuração: " << argv[1] << "\n\n";

  JsonFloor floorInfo(argv[1]); 
  floorInfo.getOutputsComponents();
  cout << floorInfo.getCentralIp() << ":" << floorInfo.getCentralPort() << endl;
  floorInfo.debug();
  
  // int socket = initSocket("192.168.0.53", 10057);


  // wiringPiSetup();

  // init_people_counter(getWPiMappedPin(13), getWPiMappedPin(19));
  // createAndSendPackage(
  //   floorInfo.getFloorName(),
  //   floorInfo.getInputsComponents(),
  //   floorInfo.getTemperatureSensorComponent().wpi_gpio,
  //   socket
  // );

  // socket --
  // char *msg = "alow";
  // string msg2 = "alow";
  // cout << msg2.length();
  // int socket = initSocket("localhost", 10057);
  // sendMsg(socket, (char*)msg2.c_str(), 4);
  // socket end

  return 0;
}