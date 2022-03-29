#include <fstream>
#include <json.hpp>
#include <gpio.hpp>
#include <wiringPi.h>
#include <utils.hpp>
#include <thread>
#include <unistd.h>

using namespace std;

int is_running = true;
volatile int number_on_floor = 0;

void dec(){number_on_floor--;}
void inc(){number_on_floor++;}
// void dec(){cout<<"decrementei";}
// void inc(){cout<<"incrementei";}
void init_people_counter(int increment_pin, int decrement_pin){
  people_counter(increment_pin, decrement_pin, &inc, &dec);
}
int main(){

  vector<component> outputs;
  outputs = loadOutputAsArr();
  wiringPiSetup();

  // for(auto elem : outputs){
  //   pinMode(elem.wpi_gpio, OUTPUT);
  //   digitalWrite(elem.wpi_gpio, LOW);
  // }
  thread people_observer(init_people_counter, getWPiMappedPin(13), getWPiMappedPin(19));

  while (is_running)
  {
    cout << "Pessoas:" << number_on_floor << endl;
    usleep(1000000);
  }
  
  people_observer.join();

  return 0;
}