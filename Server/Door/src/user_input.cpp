#include<user_input.h>
#include<main.h>
#include<global.h>
#include<LED.h>

void user_input_init()
{
    pinMode(USER_KEY, INPUT_PULLUP); 
    pinMode(GPIO0,INPUT_PULLUP);
}

void user_input_scan()
{
   if(digitalRead(USER_KEY)==LOW)
    {
        vTaskDelay(30 / portTICK_PERIOD_MS);//delay 30ms
        if(digitalRead(USER_KEY)==LOW)
        {
            open_red_LED(1023);
            while(digitalRead(USER_KEY)==LOW){}
            open_door_status=1;
        }
       
    }

    if((touchRead(TOUCH))<60)
    {
        screen_refresh=1;
        screen_change=1;
        touched=1;
        vTaskDelay(300 / portTICK_PERIOD_MS);//delay 
        while((touchRead(TOUCH))<60){}
    }

    if(digitalRead(GPIO0)==LOW)
    {
        screen_refresh=1;
        log_page=1;
        vTaskDelay(300 / portTICK_PERIOD_MS);//delay 
    }
}