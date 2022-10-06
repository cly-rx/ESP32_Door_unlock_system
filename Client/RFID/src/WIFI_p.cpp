#include <WIFI_p.h>
#include<DHT11.h>
#include<LED.h>
#include<global.h>
#include<screen.h>

const char *ssid = "Mac Book";
const char *password = "321321hyx";
const IPAddress serverIP(192,168,1,107); //目标地址
uint16_t serverPort = 22333;         //目标服务器端口号
bool WIFI_broken_status=0;//0:normal  1:broken with red LED lighting up

WiFiClient client;   //声明一个客户端对象，用于与服务器进行连接

void wifi_p_init()
{
    open_red_LED(1023);
    show_new_log("WIFI init...");
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); //关闭STA模式下wifi休眠，提高响应速度
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid, password);
        delay(3000);
    }
    show_new_log("IP:"+WiFi.localIP().toString());
    show_new_log("RSSI:"+(String)WiFi.RSSI()+"dbm");
    show_new_log("Connecting to Server");
    while (!client.connect(serverIP, serverPort))  //尝试访问目标地址
    {

    }
    open_yellow_LED(1023);
    wifi_status=1;
}
void wifi_p_task(void *parameter)
{
    while (1)
    {
        while (client.connected()) //如果处于连接状态
        {
            if(WIFI_broken_status==1)
            {
                WIFI_broken_status=0;
                close_all_LED();
            }
            if(open_door_status==1)
            {
                client.write("open_"); //send to server
                open_door_status=0;
                yellow_LED_breath_status=1;
            }

            if(WatchDog_sender==1)
            {
                client.write("feed_"); //send to server for feeding the remote WatchDog
                WatchDog_sender=0;
                green_LED_breath_status=1;
            }
            if(Ring_state==1)
            {
                client.write("ring_");//send message to server
                Ring_state=0;   
            }
        }
        client.connect(serverIP, serverPort);
        open_red_LED(1023);
        vTaskDelay(1000 / portTICK_PERIOD_MS);//delay
        WIFI_broken_status=1;
    }
    vTaskDelete(NULL);
}



//client.write(line.c_str());//c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同  
//String line = client.readStringUntil('\n'); //读取数据到换行符