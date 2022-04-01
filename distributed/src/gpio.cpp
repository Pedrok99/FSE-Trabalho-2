#include <iostream>
#include <wiringPi.h>

void initWiringpi(){
  int initState;
  do{
    std::cout<<"Initializing wiringPi" << std::endl;
    initState = wiringPiSetup();    
    delay(1000);
  }while(initState == -1);
}

int getPinData(int pin){
  int pinState = digitalRead(pin);
  return pinState;
}

void setPinValue(int pin, int value){
  digitalWrite(pin, value);
}