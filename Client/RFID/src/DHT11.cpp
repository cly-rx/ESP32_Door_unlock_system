#include<DHT11.h>
#include<main.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include<screen.h>

DHT_Unified dht(DHT_DATA1, DHT11);

uint32_t delayMS;

void DHT_init() 
{
    dht.begin();
    sensor_t sensor;
    show_new_log("Etemp:"+(String)get_temperature()+"'C"+"Ehumi:"+(String)get_humidity()+"%");
}

//return centigrade
float get_temperature()
{
    delay(delayMS);// Delay between measurements.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) 
    {
        return 90;//error
    }
    else 
    {
        return event.temperature;
    }
}

//return percentage of the humidity
float get_humidity()
{
    delay(delayMS);// Delay between measurements.
    sensors_event_t event;
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) 
    {
        return 110;//error
    }
    else 
    {
        return event.relative_humidity;
    }
}