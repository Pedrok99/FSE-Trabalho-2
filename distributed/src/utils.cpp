#include <utils.hpp>

void people_counter(int increment_pin, int decrement_pin, void (*increment_function)(), void (*decrement_function)()){
  wiringPiISR (increment_pin, INT_EDGE_RISING, increment_function);
  wiringPiISR (decrement_pin, INT_EDGE_RISING, decrement_function);
}

int getWPiMappedPin(int gpioPin){
  switch (gpioPin)
  {
    case 2:
      return 8;
    case 3:
      return 9;
    case 4:
      return 7;
    case 17:
      return 0;
    case 27:
      return 2;
    case 22:
      return 3;
    case 10:
      return 12;
    case 9:
      return 13;
    case 11:
      return 14;
    case 0:
      return 30;
    case 5:
      return 21;
    case 6:
      return 22;
    case 13:
      return 23;
    case 19:
      return 24;
    case 26:
      return 25;
    case 14:
      return 15;
    case 15:
      return 16;
    case 18:
      return 1;
    case 23:
      return 4;
    case 24:
      return 5;
    case 25:
      return 6;
    case 8:
      return 10;
    case 7:
      return 11;
    case 1:
      return 31;
    case 12:
      return 26;
    case 16:
      return 27;
    case 20:
      return 28;
    case 21:
      return 29;
  default:
    return -1;
  }
}
