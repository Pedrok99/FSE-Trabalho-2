#ifndef __DHT22__
#define __DHT22__

struct dht22
{
  float humidity = 0;
  float temperature = 0;
};

dht22 read_dht_data(int DHT_PIN);
dht22 readSafeTemperature(int pin, dht22 lastValidResult);

#endif