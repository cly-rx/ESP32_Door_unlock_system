#include <time_p.h>
#include <main.h>
#include <time.h>
#include<LED.h>
#include<global.h>
#include<screen.h>

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;

time_t screen_close_time;
time_t current_time;

void time_task(void *parameter)
{
    while(!wifi_status)
    {
    }
    open_green_LED(1023);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); // Get time from web
    while (!getLocalTime(&timinfor_task))
    {
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);// Get time from web
        vTaskDelay(3000 / portTICK_PERIOD_MS);//delay
    }
    time_satus=1;
    close_all_LED();
    screen_refresh=1;
    show_new_log("time got:"+(String)timinfor_task.tm_hour+":"+(String)timinfor_task.tm_min);

    while (1)//             time loop service starts form here
    {
        getLocalTime(&timinfor_task);
        if(screen_refresh)//screen timer
        {
            screen_refresh=0;
            screen_state=1;
            time(&screen_close_time);
            screen_close_time+=5;
        }
        time(&current_time);
        if(screen_close_time<=current_time)
        {
            screen_state=0;
        }




        if(timinfor_task.tm_min==0&&timinfor_task.tm_sec==0)//show_time_on_screen per hour
        {
            screen_refresh=1;
            screen_change=1;
            vTaskDelay(1000 / portTICK_PERIOD_MS);//delay 1s
        }

        if(is_this_time(23,00))//sleep_time
        {
            
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);//delay 100ms
    }
    vTaskDelete(NULL);
}




bool is_this_time(int hour,int minute)
{
    return(hour==timinfor_task.tm_hour&&minute==timinfor_task.tm_min);
}