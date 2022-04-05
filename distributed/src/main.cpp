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

void createAndSendPackages(std::string floorName, std::vector<component> inputComponents, std::vector<component> outputComponents, int dhtPin, int sock){
  int leftShift = 2;
  dht22 dhtData;
  // separators
  string keyValueSeparator = ":", endSeparator = ";", blockSeparator = "?", s_end = "\0";
  // package strings
  string package, readData, people_counter, umi_temp, inputReading, outputReading, formattedFloorName;


  while (1)
  {
    people_counter = "Pessoas no andar" + keyValueSeparator + to_string(abs(people_on_floor)) + endSeparator;
    dhtData = readSafeTemperature(dhtPin, dhtData);
    umi_temp = "Temperatura" + keyValueSeparator + to_string(dhtData.temperature) + endSeparator + 
               "Umidade"+ keyValueSeparator + to_string(dhtData.humidity) + endSeparator;

    inputReading = returnAllReadAsString(inputComponents, keyValueSeparator, endSeparator, leftShift);
    outputReading = returnAllReadAsString(outputComponents, keyValueSeparator, endSeparator, 0);
    
    formattedFloorName = "Andar" + keyValueSeparator + floorName + endSeparator;
    // nome?out?in+count?temp
    package = formattedFloorName + blockSeparator + 
              outputReading + blockSeparator +
              inputReading +  people_counter + blockSeparator + 
              umi_temp + s_end;
    cout << "Sending package... " << endl;
    sendMsg(sock, (char*)package.c_str(), package.size());
    cout << "Package size: " << package.size() << endl;
    package.clear();
    usleep(1000000);
  }
  
}

int waitConnection(string ip, int port){
  int svSocket;
  do{
    cout << "Tentando estabelecer conexão..." << endl;
    svSocket = initSocket(ip, port);
    usleep(3000000);
  } while (svSocket == -1);
  return svSocket;
}

void handleEventRequest(int sock){
  while (true)
  {
    string recievedString, delimiter="=", target, value;

    recievedString = getMsg(sock);

    target= recievedString.substr(0, recievedString.find(delimiter)); 
    value = recievedString.erase(0, recievedString.find(delimiter) + delimiter.length());
    cout << "Chave: " << target << endl;
    cout << "Valor: " << value << endl;

    setPinValue(stoi(target), stoi(value));
  }

}

int main(int argc, char *argv[]){
  
  if(argc < 2){
    cout << "\nUm arquivo de configuração deve ser enviado via linha de comando. Saindo...\n" << endl;
    exit(0);
  }
  cout << "\nUsando arquivo de configuração: " << argv[1] << "\n\n";

  JsonFloor floorInfo(argv[1]);

  int svSocket = waitConnection(floorInfo.getCentralIp(), floorInfo.getCentralPort());

  vector<component> counterSensors = floorInfo.getPeopleCounterSensors();

  wiringPiSetup();

  std::thread recieve (handleEventRequest, svSocket);   

  init_people_counter(counterSensors[0].wpi_gpio, counterSensors[1].wpi_gpio);
  cout << floorInfo.getTemperatureSensorComponent().wpi_gpio;
  createAndSendPackages(floorInfo.getFloorName(), floorInfo.getInputsComponents(), floorInfo.getOutputsComponents(), floorInfo.getTemperatureSensorComponent().wpi_gpio, svSocket);
  recieve.join();
  return 0;
}