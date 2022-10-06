/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-rfid-nfc
 */
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include<screen.h>
#include<main.h>

#define SS_PIN  16  // ESP32 pin GIOP5 
#define RST_PIN 17 // ESP32 pin GIOP27 


void RFID_task();
void RFID_init();
