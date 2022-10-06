#include <WIFI_p.h>
#include <motor.h>
#include<DHT11.h>
#include<LED.h>
#include<global.h>
#include<screen.h>
#include <main.h>

const char *ssid = "Mac Book";
const char *password = "321321hyx";
WiFiServer server; //声明服务器对象

void wifi_p_init()
{
    open_red_LED(1023);
    show_new_log("WIFI init...");
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); //关闭STA模式下wifi休眠，提高响应速度
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        //WiFi.begin(ssid, password);
        //delay(1000);
    }
    server.begin(22333); //服务器启动监听端口号22333
    show_new_log("Success!");
    show_new_log("IP:"+WiFi.localIP().toString());
    show_new_log("RSSI:"+(String)WiFi.RSSI()+"dbm");
    open_yellow_LED(1023);
    wifi_status=1;
}

String wifi_p_read()
{
    WiFiClient client = server.available(); //尝试建立客户对象
    if (client)                             //如果当前客户可用
    {
        String readBuff = "";
        while (client.connected()) //如果客户端处于连接状态
        {
            if (client.available()) //如果有可读数据
            {
                //green_LED_breath_status=1;
                char c = client.read(); //读取一个字节，也可以用readLine()等其他方法
                if (c == '_') 
                {
                    timerWrite(timer, 0); //重置定时器（饲料看门狗）
                    break;                                 //跳出循环
                }
                readBuff += c;
            }
        }
        // dealing with data here
        return readBuff;
        client.stop(); //结束当前连接:
    }
    else
    {
        client.stop();
        return "no_client";
        //client.stop(); //结束当前连接:
    }
}
bool wifi_p_send(String send_data)
{
    WiFiClient client = server.available(); //尝试建立客户对象
    if (client)                             //如果当前客户可用
    {
        client.print(send_data); //向客户端发送
        client.stop();           //结束当前连接:
        return 0;
    }
    return 1;
}
void wifi_p_task(void *parameter)
{
    while (1)
    {
        String rec_data = wifi_p_read();
        if (rec_data != "no_client")//decode and process commands form web
        {
            
            if (rec_data == "open")//open door
            {
                open_door_status=1;
                show_new_log(rec_data+"  "+(String)timinfor_task.tm_hour+":"+(String)timinfor_task.tm_min);
                vTaskDelay(100 / portTICK_PERIOD_MS);//delay
            }
            if(rec_data=="Temp")
            {
                wifi_p_send(String(temperatureRead()));
            }
            if(rec_data=="humidity")
            {
                wifi_p_send(String(get_humidity()));
            }
            if(rec_data=="ring")
            {
                digitalWrite(RING_PIN,LOW);
                vTaskDelay(100 / portTICK_PERIOD_MS);//delay
                digitalWrite(RING_PIN,HIGH);
                vTaskDelay(100 / portTICK_PERIOD_MS);//delay
            }
        }
    }
    vTaskDelete(NULL);
}