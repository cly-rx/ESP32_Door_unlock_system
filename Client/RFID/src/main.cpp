#include <main.h>
#include<WIFI_p.h>
#include<screen.h>
#include<DHT11.h>
#include<task.h>
#include<time_p.h>
#include<user_input.h>
#include<LED.h>
#include<global.h>
#include <RFID.h>

void setup()
{
    LED_init();
    screen_init();
    RFID_init();
    wifi_p_init();
    DHT_init();
    task_create();
    user_input_init();
}

void loop()
{
    user_input_scan();
    RFID_task();
}