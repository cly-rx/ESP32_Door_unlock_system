#ifndef GLOBAL_H
#define GLOBAL_H
    extern bool wifi_status;//0:not connected  1:connected
    extern bool time_satus;//0:haven't got time  1:already got time
    extern bool red_LED_breath_status;//0:stop breath  1:start breath
    extern bool green_LED_breath_status;//0:stop breath  1:start breath
    extern bool yellow_LED_breath_status;//0:stop breath  1:start breath
    extern bool open_door_status;//when change to 1, the Wifi task will reset this and open the door
    extern bool touched; //when touched, this variable will be set as 1, remener reset it after processing
    extern bool pressed_key;//when pressed the key, this variable will be set as 1, remener reset it after processing
    extern bool screen_state;//0: close screen 1:open screen
    extern bool WIFI_watch_dog_state;//0: connected 1:dissconnected, restart is needed
    extern bool screen_refresh;//the value will be set when screen be refresed, the value will be reset by time task 
    extern bool screen_change;//as same as screen_refresh, but send massage to screen_task
    extern struct tm timinfor_task;//time
    extern bool log_page;// show the log page
    extern bool WatchDog_sender;// 1:send Watchdog signal
    extern TaskHandle_t screen_task_handler;
    extern bool Ring_state;//1:send message to remote server for ring, this will be reset by WIFI_task
#endif