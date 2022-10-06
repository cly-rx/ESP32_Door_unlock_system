#include <motor.h>
#include <main.h>
#include <screen.h>
#include <global.h>
#include<LED.h>

const int silent_time[] = {0, 1, 2, 3, 4, 5, 6, 7, 13, 23}; // scilent hours in a day

bool is_silence = 1; // 0 for not scilent

// check how to open the door, normal or silent mode
void check_time()
{
    is_silence = 0;
    for (int i = 0; i < sizeof(silent_time) / sizeof(int) - 1; i++)
    {
        if (timinfor_task.tm_hour == silent_time[i])
        {
            is_silence = 1;
            break;
        }
    }
}
void motor_init()
{
    ledcSetup(0, 5000, 10); //通道0， 5KHz，10位解析度
    ledcAttachPin(M0, 0);   //通道0的输出引脚

    ledcSetup(1, 5000, 10); //通道1， 5KHz，10位解析度
    ledcAttachPin(M1, 1);   //通道1的输出引脚

    ledcWrite(0, 0);
    ledcWrite(1, 0);
}
void open_door_task(void *parameter)
{
    while (1)
    {
        if (open_door_status)
        {
            check_time();
            if (is_silence) // scilence,slow
            {
                green_LED_breath_status = 1;
                ledcWrite(0, 0);
                ledcWrite(1, SILENT_SPEED);
                vTaskDelay(2000 / portTICK_PERIOD_MS);//delay 
                ledcWrite(0, 300);
                ledcWrite(1, 0);
                vTaskDelay(4000 / portTICK_PERIOD_MS);//delay 
                ledcWrite(0, 0);
                ledcWrite(1, 0);
            }
            else // normal,fast
            {
                yellow_LED_breath_status=1;
                ledcWrite(0, 0);
                ledcWrite(1, NORMAL_SPEED);
                vTaskDelay(1000 / portTICK_PERIOD_MS);//delay 
                ledcWrite(0, NORMAL_SPEED);
                ledcWrite(1, 0);
                vTaskDelay(1000 / portTICK_PERIOD_MS);//delay 
                ledcWrite(0, 0);
                ledcWrite(1, 0);
            }
            open_door_status = 0;
            close_all_LED();
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);//delay
    }
    vTaskDelete(NULL);
}