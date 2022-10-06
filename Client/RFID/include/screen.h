#include<Arduino.h>
void screen_init();
void add_log(String new_log);
void show_new_log(String new_log);//add a line of log 
void page_log();
void page_1();//show time 
void page_2();//show temperature & humidity inside
void page_3();//show temperature & humidity outside
void black_screen();
void screen_task(void *parameter);