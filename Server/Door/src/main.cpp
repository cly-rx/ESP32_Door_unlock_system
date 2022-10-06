#include <main.h>
#include<WIFI_p.h>
#include<motor.h>
#include<screen.h>
#include<DHT11.h>
#include<task.h>
#include<time_p.h>
#include<user_input.h>
#include<LED.h>
#include<global.h>
#include "esp_system.h"

const int wdtTimeout = 10000;  //触发看门狗的时间（以毫秒为单位）


void watch_dog_init();

void IRAM_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

void setup()
{
    watch_dog_init();
    LED_init();
    screen_init();
    motor_init();
    wifi_p_init();
    DHT_init();
    task_create();
    user_input_init();
    pinMode(RING_PIN,OUTPUT);
}

void loop()
{
    user_input_scan();
}


void watch_dog_init()
{
  timer = timerBegin(0, 80, true);                //初始化定时器 定时器编号0，分频数 80，是否是累加模式：true
  timerAttachInterrupt(timer, &resetModule, true);  //附加回调
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //设置定时器
  timerAlarmEnable(timer);                          //开启中断
}