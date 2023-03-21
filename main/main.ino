#include <avr/wdt.h>
#include "global_val.h"
#include "lcd_menu.h"

/*
main.ino <== global_val.h
|=>lcd_menu.h
|  |=>program_que.h
|     |=>JED_generator.h
|     |  |=>bool_solver.h
*/

void setup(){
    delay(1000);
    Serial.begin(115200);
    u8g2.begin();
    u8g2.enableUTF8Print();		
    digitalWrite(BTN_L  , 1);
    digitalWrite(BTN_R  , 1);
    digitalWrite(BTN_D  , 1);
    digitalWrite(BTN_OK , 1);
    digitalWrite(BTN_U  , 1);
    pinMode(BUZZ   , 1);
    
    //wdt_enable(WDTO_8S);
}
void loop(){
    lcd_page_setup();//setting menu , que,mode,ok,stid,name
    if(que_num==3 && burn_type==0){  //que 3 student must flash 3 ic , add auto mode
        for(int i=0;i<9;i++)Serial.print(std_id[i]);Serial.println();
        for(int N=1 ; N<=3 ; N++){
            Serial.print("  ");
            burn_type = N;
            bool comfirm = lcd_page_put_ic_comfirm("(auto mode)");
            if(comfirm)//compile eraser program verify
                lcd_page_auto_burn();
            else
                break;
        }
        burn_type=0;
    }
    else{//burn only once
        bool comfirm = lcd_page_put_ic_comfirm(NULL);
        if(comfirm){//compile eraser program verify
            lcd_page_auto_burn();
        }
    }
}