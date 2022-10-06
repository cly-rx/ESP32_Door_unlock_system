#include <ID_card.h>

String ID_card[]={
    "227:110:180:195:",
    "35:139:242:29:",
    "99:37:244:29:",
    "99:49:120:28:",
    "195:134:248:29:",
    "67:228:198:158:",//cly
    "113:208:136:8:",//Harry Potter's 
    "245:23:215:15:"//tky 一卡通
};

bool check_card(String ID_input)
{
    for (int i = 0; i < sizeof(ID_card) / sizeof(ID_card[0]); i++)
    {
        if(ID_card[i]==ID_input)
        {
            return true;
        }
    }
    return false;
}