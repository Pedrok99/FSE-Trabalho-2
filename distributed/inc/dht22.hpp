#ifndef __DHT22__
#define __DHT22__

struct dht22
{
  float humidity;
  float temperature;
};

dht22 read_dht_data(int DHT_PIN);
dht22 readSafeTemperature(int pin, dht22 lastValidResult);

#endif