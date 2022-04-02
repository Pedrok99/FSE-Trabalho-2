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

using namespace std;

volatile int is_running = true;
volatile int people_on_floor = 0;

void dec(){people_on_floor--;}
void inc(){people_on_floor++;}
void init_people_counter(int increment_pin, int decrement_pin){
  people_counter(increment_pin, decrement_pin, &inc, &dec);
}

int main(){
  dht22 dhtResult;
  dhtResult.humidity = 0;
  dhtResult.temperature = 0;
  
  vector<component> outputs;
  outputs = loadResource("outputs", true);
  cout << "Pela classe"<< "\n\n\n";

  JsonFloor testando("groundCfg.json"); 
  testando.getOutputsComponents();
  // wiringPiSetup();
  // init_people_counter(getWPiMappedPin(13), getWPiMappedPin(19));

  // socket --
  // char *msg = "alow";
  // string msg2 = "alow";
  // cout << msg2.length();
  // int socket = initSocket("localhost", 10057);
  // sendMsg(socket, (char*)msg2.c_str(), 4);
  // socket end

  while (is_running)
  {
    // dhtResult = readSafeTemperature(getWPiMappedPin(20), dhtResult);
    // cout << 
    // "Pessoas -> " << number_on_floor  
    // << " - Temperature -> " << dhtResult.temperature
    // << " - Humidity -> " << dhtResult.humidity << endl;
    
    usleep(1000000);
  }

  return 0;
}