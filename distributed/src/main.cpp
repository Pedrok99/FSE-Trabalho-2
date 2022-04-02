#include <fstream>
#include <json.hpp>
#include <gpio.hpp>
#include <wiringPi.h>
#include <utils.hpp>
#include <thread>
#include <unistd.h>
#include <dht22.hpp>
#include <socket_tcp.hpp>

using namespace std;

int is_running = true;
volatile int number_on_floor = 0;

void dec(){number_on_floor--;}
void inc(){number_on_floor++;}

void init_people_counter(int increment_pin, int decrement_pin){
  people_counter(increment_pin, decrement_pin, &inc, &dec);
}
int main(){
  dht22 dhtResult;
  dhtResult.humidity = 0;
  dhtResult.temperature = 0;
  
  vector<component> outputs;
  outputs = loadOutputAsArr();
  // wiringPiSetup();

  // init_people_counter(getWPiMappedPin(13), getWPiMappedPin(19));
  char *msg = "alow";
  string msg2 = "alow";
  cout << msg2.length();
  int socket = initSocket("localhost", 10057);
  while (is_running)
  {
    sendMsg(socket, (char*)msg2.c_str(), 4);
    // dhtResult = readSafeTemperature(getWPiMappedPin(20), dhtResult);
    // cout << 
    // "Pessoas -> " << number_on_floor  
    // << " - Temperature -> " << dhtResult.temperature
    // << " - Humidity -> " << dhtResult.humidity << endl;
    
    usleep(1000000);
  }

  return 0;
}