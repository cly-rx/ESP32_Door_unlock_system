#include <screen.h>
#include <U8g2lib.h>
#include <global.h>
#include<DHT11.h>

#define MAX_PAGE 3

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
String log_history[8] = {
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};
int page_num = 1; // page number on screen

void add_log(String new_log)
{
    u8g2.clear();
    for (int i = 0; i < 7; i++)
    {
        log_history[i] = "                         ";
        log_history[i] = log_history[i + 1];
    }
    log_history[7] = "                         ";
    log_history[7] = new_log;
}
void show_new_log(String new_log_show)
{
    add_log(new_log_show);
    page_log();
}
void screen_init()
{
    u8g2.setBusClock(400000);
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setFont(u8g2_font_5x8_mf);
    show_new_log("CPU temp:"+(String)temperatureRead()+"'C");
}
void page_log() // show system status
{
    screen_refresh = 1;

    u8g2.setFont(u8g2_font_5x8_mf);
    for (int i = 0; i < 8; i++)
    {
        u8g2.setCursor(0, i * 8);
        u8g2.print(log_history[i]);
    }
    u8g2.sendBuffer();
}

void page_1() // show time
{
    u8g2.setFont(u8g2_font_fub35_tr);
    vTaskPrioritySet(screen_task_handler,2);
    for (int i = 124; i > 44; i = i - 10)
    {
        u8g2.setCursor(5, i);
        u8g2.clearBuffer();
        u8g2.print("Time");
        u8g2.sendBuffer();
    }
    vTaskPrioritySet(screen_task_handler,1);
    vTaskDelay(500 / portTICK_PERIOD_MS);//delay 500ms
    u8g2.clearBuffer();
    if(timinfor_task.tm_hour<10){
        u8g2.setCursor(15, 50);
    }
    else{
        u8g2.setCursor(0, 50);
    }
    vTaskPrioritySet(screen_task_handler,2);
    if (timinfor_task.tm_min<10){
        u8g2.print((String)timinfor_task.tm_hour + ":0" + (String)timinfor_task.tm_min);
    }
    else{
        u8g2.print((String)timinfor_task.tm_hour + ":" + (String)timinfor_task.tm_min);
    }
    u8g2.sendBuffer();
    vTaskPrioritySet(screen_task_handler,1);
}
void page_2() // show temperature & humidity inside
{
    u8g2.setFont(u8g2_font_fub35_tr);
    vTaskPrioritySet(screen_task_handler,2);
    for (int i = 124; i > 44; i = i - 10)
    {
        u8g2.setCursor(0, i);
        u8g2.clearBuffer();
        u8g2.print("Temp");
        u8g2.sendBuffer();
    }
    vTaskPrioritySet(screen_task_handler,1);
    vTaskDelay(500 / portTICK_PERIOD_MS);//delay 500ms
    vTaskPrioritySet(screen_task_handler,2);
    u8g2.clearBuffer();
    u8g2.setCursor(0, 50);
    u8g2.print((String)get_temperature()+"'C");
    u8g2.sendBuffer();
    vTaskPrioritySet(screen_task_handler,1);
}
void page_3() // show temperature & humidity outside
{

    u8g2.setFont(u8g2_font_fub35_tr);
    vTaskPrioritySet(screen_task_handler,2);
    for (int i = 124; i > 44; i = i - 10)
    {
        u8g2.setCursor(5, i);
        u8g2.clearBuffer();
        u8g2.print("CPU");
        u8g2.sendBuffer();
    }
    vTaskPrioritySet(screen_task_handler,1);
    vTaskDelay(500 / portTICK_PERIOD_MS);//delay 500ms
    vTaskPrioritySet(screen_task_handler,2);
    u8g2.clearBuffer();
    u8g2.setCursor(0, 50);
    u8g2.print((String)temperatureRead()+"'C");
    u8g2.sendBuffer();
    vTaskPrioritySet(screen_task_handler,1);
}
void black_screen()
{
    u8g2.clear();
    u8g2.sendBuffer();
}
void screen_task(void *parameter)
{
    while (1)
    {
        if (screen_state)
        {
            if (screen_change)
            {

                screen_change = 0;
                page_num++;
                u8g2.clear();
                if (page_num == MAX_PAGE + 1)
                {
                    page_num = 1;
                }
                switch (page_num)
                {
                case 1:
                    page_1();
                    break;
                case 2:
                    page_2();
                    break;
                case 3:
                    page_3();
                    break;
                default:
                    break;
                }
            }
            if(log_page)
            {
                u8g2.clear();
                log_page=0;
                page_log();
            }
        }
        else
        {
            black_screen();
            page_num = 0;
        }
    }
    vTaskDelete(NULL);
}