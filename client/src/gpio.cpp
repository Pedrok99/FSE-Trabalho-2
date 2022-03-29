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
  delay(200);
  return pinState;
}
