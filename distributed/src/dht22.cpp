/*
 *  dht.c:
 *	read temperature and humidity from DHT11 or DHT22 sensor
 */
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dht22.hpp>

#define MAX_TIMINGS	85
// #define DHT_PIN		3	/* GPIO-22 */
int data[5] = { 0, 0, 0, 0, 0 };

dht22 read_dht_data(int DHT_PIN)
{
  dht22 result;
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j			= 0, i;
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;
	/* pull pin down for 18 milliseconds */
	pinMode( DHT_PIN, OUTPUT );
	digitalWrite( DHT_PIN, LOW );
	delay( 18 );
	/* prepare to read the pin */
	pinMode( DHT_PIN, INPUT );
	/* detect change and read data */
	for ( i = 0; i < MAX_TIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( DHT_PIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHT_PIN );
		if ( counter == 255 )
			break;
		/* ignore first 3 transitions */
		if ( (i >= 4) && (i % 2 == 0) )
		{
			/* shove each bit into the storage bytes */
			data[j / 8] <<= 1;
			if ( counter > 16 )
				data[j / 8] |= 1;
			j++;
		}
	}
	/*
	 * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	 * print it out if data is good
	 */
	if ( (j >= 40) &&
	     (data[4] == ( (data[0] + data[1] + data[2] + data[3]) & 0xFF) ) )
	{
		float h = (float)((data[0] << 8) + data[1]) / 10;
		if ( h > 100 )
		{
			h = data[0];	// for DHT11
		}
		float c = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;
		if ( c > 125 )
		{
			c = data[2];	// for DHT11
		}
		if ( data[2] & 0x80 )
		{
			c = -c;
		} 
    result.humidity = h;
    result.temperature = c;
    return result;
	}else  {
    result.humidity = -1;
    result.temperature = -1;
	}
  return result;
}

dht22 readSafeTemperature(int pin, dht22 lastValidResult){
  dht22 currentResult = read_dht_data(pin);
  if(currentResult.humidity == float(-1) && currentResult.temperature == float(-1)){
    return lastValidResult;
  }
  return currentResult;
}