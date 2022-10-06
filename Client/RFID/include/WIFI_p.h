#include <WiFi.h>

void wifi_p_init();
String wifi_p_read();
bool wifi_p_send(String send_data);
void wifi_p_task(void *parameter);