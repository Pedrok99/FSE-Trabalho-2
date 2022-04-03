#include <gpio.hpp>

void initWiringpi(){
  int initState;
  do{
    std::cout<<"Initializing wiringPi" << std::endl;
    initState = wiringPiSetup();    
    delay(1000);
  }while(initState == -1);
}

string readPinAsStr(int pin){
  int pinState = digitalRead(pin);
  return to_string(pinState);
}

void setPinValue(int pin, int value){
  pinMode (pin, OUTPUT) ;
  digitalWrite(pin, value);
}

string returnAllReadAsString(vector<component> sensors, string keyValueSeparator, string endSeparator, int leftShift){
  string readData, aux;
  for (auto prop = sensors.begin(); prop != sensors.end()-leftShift; ++prop){
    aux = prop->tag + keyValueSeparator + readPinAsStr(prop->wpi_gpio) + endSeparator;
    readData += aux;
  }
  return readData;
}