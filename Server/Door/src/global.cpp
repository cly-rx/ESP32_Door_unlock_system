#include<Arduino.h>

bool wifi_status=0;//0:not connected  1:connected
bool time_satus=0;//0:haven't got time  1:already got time
bool red_LED_breath_status=0;//0:stop breath  1:start breath
bool green_LED_breath_status=0;//0:stop breath  1:start breath
bool yellow_LED_breath_status=0;//0:stop breath  1:start breath
bool open_door_status=0;//when change to 1, the motor task will reset this and open the door
bool touched=0; //when touched, this variable will be set as 1, remener reset it after processing
bool pressed_key=0;//when pressed the key, this variable will be set as 1, remener reset it after processing
bool screen_state=0;//0: close screen 1:open screen
bool screen_refresh;//the value will be set when screen be refresed, the value will be reset by time task 
bool screen_change=0;//as same as screen_refresh, but send massage to screen_task
struct tm timinfor_task;//time
bool log_page=0;// show the log page
hw_timer_t *timer = NULL;

TaskHandle_t screen_task_handler;