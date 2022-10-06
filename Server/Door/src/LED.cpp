#include <LED.h>
#include <main.h>
#include <global.h>

void LED_init()
{
     ledcSetup(2, 5000, 10);      //通道2， 5KHz，10位解析度
     ledcAttachPin(GREEN_LED, 2); //通道2的输出引脚

     ledcSetup(3, 5000, 10);    //通道3， 5KHz，10位解析
     ledcAttachPin(RED_LED, 3); //通道3的输出引脚

     ledcWrite(2, 0);
     ledcWrite(3, 0);
}

// brightness:0-1023
void open_red_LED(int brightness)
{
     ledcWrite(2, 0);
     ledcWrite(3, brightness);
}

// brightness:0-1023
void open_green_LED(int brightness)
{
     ledcWrite(3, 0);
     ledcWrite(2, brightness);
}

// brightness:0-1023
void open_yellow_LED(int brightness)
{
     ledcWrite(2, brightness);
     ledcWrite(3, brightness);
}

void close_all_LED()
{
     ledcWrite(2, 40);
     ledcWrite(3, 20);
}

void LED_breath_task(void *parameter)
{
     while (1)
     {
          if (red_LED_breath_status)
          {
               close_all_LED();
               for (int i = 0; i < 1010; i+=3)
               {
                    ledcWrite(3, i);
                    vTaskDelay(2 / portTICK_PERIOD_MS);//delay
               }
               ledcWrite(3, 1023);
               vTaskDelay(10 / portTICK_PERIOD_MS);//delay
               for (int i = 1023; i > 10; i-=3)
               {
                    ledcWrite(3, i);
                    vTaskDelay(2 / portTICK_PERIOD_MS);//delay
               }
               close_all_LED();
               red_LED_breath_status = 0;
          }
          if (green_LED_breath_status)
          {
               close_all_LED();
               
               for (int i = 0; i < 1010; i+=3)
               {
                    ledcWrite(2, i);
                    vTaskDelay(2 / portTICK_PERIOD_MS);//delay
               }
               ledcWrite(2, 1023);
               vTaskDelay(10 / portTICK_PERIOD_MS);//delay
               for (int i = 1023; i > 10; i-=3)
               {
                    ledcWrite(2, i);
                    vTaskDelay(2 / portTICK_PERIOD_MS);//delay
               }
               green_LED_breath_status = 0;
               close_all_LED();
          }
          if (yellow_LED_breath_status)
          {
               close_all_LED();
               
               for (int i = 0; i < 1010; i+=2)
               {
                    ledcWrite(3, i);
                    ledcWrite(2, i);
                    vTaskDelay(2 / portTICK_PERIOD_MS);//delay
               }
               ledcWrite(3, 1023);
               ledcWrite(2, 1023);
               vTaskDelay(10 / portTICK_PERIOD_MS);//delay
               for (int i = 1023; i > 10; i-=2)
               {
                    ledcWrite(3, i);
                    ledcWrite(2, i);
                    vTaskDelay(2 / portTICK_PERIOD_MS);//delay
               }
               yellow_LED_breath_status = 0;
               close_all_LED();
          }
          vTaskDelay(100 / portTICK_PERIOD_MS);//delay
     }
     vTaskDelete(NULL);
}