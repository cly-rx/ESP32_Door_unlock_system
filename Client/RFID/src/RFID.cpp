#include <RFID.h>
#include <LED.h>
#include<WIFI_p.h>
#include <global.h>
#include <screen.h>
#include <ID_card.h>

MFRC522 rfid(SS_PIN, RST_PIN);
String Card_ID_getted;
void RFID_init()
{
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
}
void RFID_task() 
{
    if (rfid.PICC_IsNewCardPresent()) // new tag is available
    {
      if (rfid.PICC_ReadCardSerial()) // NUID has been readed
      {
        MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
        Card_ID_getted="";
        for (int i = 0; i < rfid.uid.size; i++) // print UID in Serial Monitor in the hex format
        {
          //Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Card_ID_getted+=(String(rfid.uid.uidByte[i])+":");
        }
        //show_new_log(Card_ID_getted);// show ID that readed
        show_new_log("Read successfully");
        if(check_card(Card_ID_getted))
        {
          open_door_status=1;
          screen_refresh=1;
          screen_change=1;
        }
        else
        {
          red_LED_breath_status=1;
        }

        rfid.PICC_HaltA(); // halt PICC
        rfid.PCD_StopCrypto1(); // stop encryption on PCD
      }
  }
}
