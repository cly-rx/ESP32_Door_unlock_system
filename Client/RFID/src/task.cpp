#include<task.h>
#include<WIFI_p.h>
#include<screen.h>
#include<time_p.h>
#include<LED.h>
#include<global.h>
#include <RFID.h>

void task_create()
{
    xTaskCreatePinnedToCore(
                wifi_p_task,          /*任务函数*/
                "wifi_p_task",        /*带任务名称的字符串*/
                10000,            /*堆栈大小，单位为字节*/
                NULL,             /*作为任务输入传递的参数*/
                1,                /*任务的优先级*/
                NULL,               /*任务句柄*/
                1);            
    while(!wifi_status){}
    xTaskCreatePinnedToCore(
                screen_task,          /*任务函数*/
                "screen_task",        /*带任务名称的字符串*/
                10000,            /*堆栈大小，单位为字节*/
                NULL,             /*作为任务输入传递的参数*/
                1,                /*任务的优先级*/
                (TaskHandle_t*  )screen_task_handler,/*任务句柄*/
                1);            
    xTaskCreatePinnedToCore(
                LED_breath_task,          /*任务函数*/
                "LED_breath_task",        /*带任务名称的字符串*/
                10000,            /*堆栈大小，单位为字节*/
                NULL,             /*作为任务输入传递的参数*/
                1,                /*任务的优先级*/
                NULL,/*任务句柄*/
                1);            
    // xTaskCreate(
    //             RFID_task,          /*任务函数*/
    //             "RFID_task",        /*带任务名称的字符串*/
    //             10000,            /*堆栈大小，单位为字节*/
    //             NULL,             /*作为任务输入传递的参数*/
    //             1,                /*任务的优先级*/
    //             NULL);            /*任务句柄*/
    xTaskCreatePinnedToCore(
                time_task,          /*任务函数*/
                "time_task",        /*带任务名称的字符串*/
                10000,            /*堆栈大小，单位为字节*/
                NULL,             /*作为任务输入传递的参数*/
                1,                /*任务的优先级*/
                NULL,
                1);            /*任务句柄*/
    //vTaskStartScheduler(); //启动任务调度
}
