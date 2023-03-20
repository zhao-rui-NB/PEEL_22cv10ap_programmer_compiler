#ifndef have_global_val_h
    #include "global_val.h"
#endif

#include "program_que.h"
#include "programmer.h" 

byte dect_btn(){
  wdt_reset();
  if(digitalRead(BTN_OK)&&digitalRead(BTN_L)&&digitalRead(BTN_R)&&digitalRead(BTN_D)&&digitalRead(BTN_U)){
    btn_up = 1;
    return 0;
  }
  return_word = 0;
  if(btn_up==1 && millis()-last_btn_time>25){
    if( !digitalRead(BTN_OK)){last_btn_time=millis();return_word=BTN_OK;}
    if( !digitalRead(BTN_L) ){last_btn_time=millis();return_word=BTN_L;}
    if( !digitalRead(BTN_R) ){last_btn_time=millis();return_word=BTN_R;}
    if( !digitalRead(BTN_D) ){last_btn_time=millis();return_word=BTN_D;}
    if( !digitalRead(BTN_U) ){last_btn_time=millis();return_word=BTN_U;}
    btn_up=0;
    if(return_word){
      digitalWrite(BUZZ,1);
      delay(5);
      digitalWrite(BUZZ,0);
    }
    return return_word;
  }
  else if(btn_up==0 && millis()-last_btn_time>400 && millis()-start>80){
    if( !digitalRead(BTN_OK)){start=millis();return_word=BTN_OK;}
    if( !digitalRead(BTN_L) ){start=millis();return_word=BTN_L;}
    if( !digitalRead(BTN_R) ){start=millis();return_word=BTN_R;}
    if( !digitalRead(BTN_D) ){start=millis();return_word=BTN_D;}
    if( !digitalRead(BTN_U) ){start=millis();return_word=BTN_U;}
    if(return_word){
      digitalWrite(BUZZ,1);
      delay(5);
      digitalWrite(BUZZ,0);
    }
    return return_word;
  }
  return 0;
}

void buzz_sound_burn_finish(){
  digitalWrite(BUZZ,1);
  delay(60);
  digitalWrite(BUZZ,0);
  delay(100);
  digitalWrite(BUZZ,1);
  delay(60);
  digitalWrite(BUZZ,0);
}
void buzz_sound_burn_failed(){
  //digitalWrite(BUZZ,1);
  //delay(100);
  //digitalWrite(BUZZ,0);
  //delay(200);
  digitalWrite(BUZZ,1);
  delay(650);
  digitalWrite(BUZZ,0);
}

void print_now_burn_type_name(){
   switch(que_num){
    case 1:u8g2.print(que_1_burn_type[burn_type]);break;
    case 2:u8g2.print(que_2_burn_type[burn_type]);break;
    case 3:u8g2.print(que_3_burn_type[burn_type]);break;
    case 4:u8g2.print(que_4_burn_type[burn_type]);break;
    case 5:u8g2.print(que_5_burn_type[burn_type]);break;
    case 6:u8g2.print(que_6_burn_type[burn_type]);break;
  }
}
void print_page_for_setup(){
  u8g2.setFont(u8g2_font_unifont_t_chinese1);  // use chinese2 for all the glyphs of "你好世界"
  u8g2.setFontDirection(0);
  u8g2.setDrawColor(1);
  
  u8g2.clearBuffer();
  u8g2.setCursor(0, lcd_L1_D);
  u8g2.print("選擇題目:   ");
  u8g2.print(que_num);
  
  if(que_num==4 || que_num==5 ){ // Z37
    u8g2.setCursor(0, lcd_L2_D);
    u8g2.print("姓氏學號: ");
    u8g2.print(char(name_and_number[0]));
    u8g2.print(name_and_number[1]);
    u8g2.print(name_and_number[2]);
    
  }
  else{
    u8g2.setCursor(0, lcd_L2_D);
    u8g2.print("學號: C");
    for(int i=0 ; i<9 ; i++){
      u8g2.print(std_id[i]);
    }
  }
  u8g2.setCursor(0, lcd_L3_D);
  u8g2.print("燒錄模式: ");
  print_now_burn_type_name();
  u8g2.setCursor(16*3, lcd_L4_D);
  u8g2.print("確認");
  //u8g2.sendBuffer();
}
void lcd_page_setup(){
  unsigned long T;
  byte optinos = 0;//0-3
  byte cursor = 0;
  bool in_input = 0;
  print_page_for_setup();
  u8g2.setDrawColor(2);
  u8g2.drawBox(0,lcd_L1_U + 16*optinos, 128,16);
  u8g2.sendBuffer();
  while(1){
    byte key = dect_btn();
    if(key!=0){
      if(key==BTN_D){
        if(optinos==3) optinos=0;
        else optinos++;
      }
      else if(key==BTN_U){
        if(optinos==0) optinos=3;
        else optinos--;
      }
      else if(key==BTN_OK){
        if(optinos==0){  //sel ques
          burn_type=0;
          print_page_for_setup();
          u8g2.setDrawColor(2);
          u8g2.drawBox(0,lcd_L1_U , 16*4,16);
          u8g2.sendBuffer();
          while(1){
            key = dect_btn();
            if(key!=0){
              if(key==BTN_OK){
                break;
              }
              else if(key==BTN_U){
                if(que_num<que_N)
                que_num++;
                print_page_for_setup();
                u8g2.setDrawColor(2);
                u8g2.drawBox(0,lcd_L1_U , 16*4,16);
                u8g2.sendBuffer();
              }
              else if(key==BTN_D){
                if(que_num>1){
                  que_num--;
                  print_page_for_setup();
                  u8g2.setDrawColor(2);
                  u8g2.drawBox(0,lcd_L1_U , 16*4,16);
                  u8g2.sendBuffer();
                }
              }
            }
            if(millis()-T>500){
              T = millis();
              u8g2.setDrawColor(2);
              u8g2.drawBox(16*6,lcd_L1_U , 16*1,16);
              u8g2.sendBuffer();
            }
          }
        }
        else if(optinos==1 && (que_num==4||que_num==5)){//input std id  //add name and end 2 stid 
          byte sel_bit = 0;  //  0-2   (name ten one) , (char , int , int) 
          print_page_for_setup();
          u8g2.setDrawColor(2);
          u8g2.drawBox(0,lcd_L2_U , 16*4,16);
          u8g2.sendBuffer();
          T=millis()-600;
          while(1){
            key = dect_btn();
            if(key!=0){
              if(key==BTN_OK){
                break;
              }
              else if(key==BTN_U){//key up (+)
                if(sel_bit==0){
                  if(name_and_number[sel_bit]=='Z')name_and_number[sel_bit]='A';
                  else name_and_number[sel_bit]++;
                }
                else{
                  if(name_and_number[sel_bit]==9)name_and_number[sel_bit]=0;
                  else name_and_number[sel_bit]++;
                }
                print_page_for_setup();
                u8g2.setDrawColor(2);
                u8g2.drawBox(0,lcd_L2_U , 16*4,16);
                u8g2.sendBuffer();
              }
              else if(key==BTN_D){
                if(sel_bit==0){
                  if(name_and_number[sel_bit]=='A')name_and_number[sel_bit]='Z';
                  else name_and_number[sel_bit]--;
                }
                else{
                  if(name_and_number[sel_bit]==0)name_and_number[sel_bit]=9;
                  else name_and_number[sel_bit]--;
                }
                print_page_for_setup();
                u8g2.setDrawColor(2);
                u8g2.drawBox(0,lcd_L2_U , 16*4,16);
                u8g2.sendBuffer();
              }
              else if(key==BTN_R){
                if(sel_bit==2)sel_bit = 0;
                else sel_bit++;
                print_page_for_setup();
                u8g2.setDrawColor(2);
                u8g2.drawBox(0,lcd_L2_U , 16*4,16);
                u8g2.drawBox( (128-24)-8*(3-sel_bit) ,lcd_L2_U ,8,16);
                u8g2.sendBuffer();
                T = millis()+300;
              }
              else if(key==BTN_L){
                if(sel_bit==0)sel_bit=2;
                else sel_bit--;
                print_page_for_setup();
                u8g2.setDrawColor(2);
                u8g2.drawBox(0,lcd_L2_U , 16*4,16);
                u8g2.drawBox( (128-24)-8*(3-sel_bit) ,lcd_L2_U ,8,16);
                u8g2.sendBuffer();
                T = millis()+300;
              }
            }
            
            if(millis()-T>700 && millis()>=T){
              T = millis();
              u8g2.setDrawColor(2);
              u8g2.drawBox( (128-24)-8*(3-sel_bit) ,lcd_L2_U ,8,16);
              u8g2.sendBuffer();
            }
            
            
            
          }
        }
        else if(optinos==1){//input std id  
          byte std_id_bit=8;
          print_page_for_setup();
          u8g2.setDrawColor(2);
          u8g2.drawBox(0,lcd_L2_U , 16*2,16);
          u8g2.sendBuffer();
          T=millis()-600;
          while(1){
            key = dect_btn();
            if(key!=0){
              if(key==BTN_OK){
                break;
              }
              else if(key==BTN_U){
                if(std_id[std_id_bit]==9)std_id[std_id_bit]=0;
                else std_id[std_id_bit]++;
                print_page_for_setup();
                u8g2.setDrawColor(2);
                u8g2.drawBox(0,lcd_L2_U , 16*2,16);
                u8g2.sendBuffer();
              }
              else if(key==BTN_D){
                if(std_id[std_id_bit]==0)std_id[std_id_bit]=9;
                else std_id[std_id_bit]--;
                print_page_for_setup();
                u8g2.setDrawColor(2);
                u8g2.drawBox(0,lcd_L2_U , 16*2,16);
                u8g2.sendBuffer();
              }
              else if(key==BTN_R){
                if(std_id_bit==8)std_id_bit = 0;
                else std_id_bit++;
                print_page_for_setup();
                u8g2.setDrawColor(2);
                u8g2.drawBox(0,lcd_L2_U , 16*2,16);
                u8g2.drawBox( (128-8)-8*(8-std_id_bit) ,lcd_L2_U ,8,16);
                u8g2.sendBuffer();
                T = millis()+300;
              }
              else if(key==BTN_L){
                if(std_id_bit==0)std_id_bit=8;
                else std_id_bit--;
                print_page_for_setup();
                u8g2.setDrawColor(2);
                u8g2.drawBox(0,lcd_L2_U , 16*2,16);
                u8g2.drawBox( (128-8)-8*(8-std_id_bit) ,lcd_L2_U ,8,16);
                u8g2.sendBuffer();
                T = millis()+300;
              }
            }
            
            if(millis()-T>700 && millis()>=T){
              T = millis();
              u8g2.setDrawColor(2);
              u8g2.drawBox( (128-8)-8*(8-std_id_bit) ,lcd_L2_U ,8,16);
              u8g2.sendBuffer();
            }
            
            
            
          }
        }
        else if(optinos==2){//sel flash mode 
          byte mode_N=0;
          switch(que_num){
            case 1:mode_N=que_1_burn_type_N; break;
            case 2:mode_N=que_2_burn_type_N; break;
            case 3:mode_N=que_3_burn_type_N; break;
            case 4:mode_N=que_4_burn_type_N; break;
            case 5:mode_N=que_5_burn_type_N; break;
          }
          print_page_for_setup();
          u8g2.setDrawColor(2);
          u8g2.drawBox(0,lcd_L3_U , 16*4,16);
          u8g2.sendBuffer();
          while(1){
            key = dect_btn();
            if(key!=0){
              if(key==BTN_OK){
                break;
              }
              else if(key==BTN_U){
                if(burn_type<mode_N-1){
                  burn_type++;
                  print_page_for_setup();
                  u8g2.setDrawColor(2);
                  u8g2.drawBox(0,lcd_L3_U , 16*4,16);
                  u8g2.sendBuffer();
                }
              }
              else if(key==BTN_D){
                if(burn_type>0){
                  burn_type--;
                  print_page_for_setup();
                  u8g2.setDrawColor(2);
                  u8g2.drawBox(0,lcd_L3_U , 16*4,16);
                  u8g2.sendBuffer();
                }
              }
            }
            if(millis()-T>500){
              T = millis();
              u8g2.setDrawColor(2);
              u8g2.drawBox(16*5,lcd_L3_U , 16*3,16);
              u8g2.sendBuffer();
            }
          }  
        }
        else if(optinos==3){//ok go to flash 
          return;
        }
      }
      print_page_for_setup();
      u8g2.setDrawColor(2);
      if(optinos==3)u8g2.drawBox(16*3,lcd_L1_U + 16*optinos, 16*2,16);
      else u8g2.drawBox(0,lcd_L1_U + 16*optinos, 128,16);
      u8g2.sendBuffer();
    }//if key


//BTN_OK
//BTN_L 
//BTN_R 
 
 
  }
}
bool lcd_page_put_ic_comfirm(char *str_for_auto){
  
  bool have_new_buffer = 1;
  byte frame_counter = 0;
  unsigned long T = 0;
  bool burn_Y_N = 1;
  while(1){
    byte key = dect_btn();
    if(key!=0){
      if(key==BTN_OK){
        have_new_buffer=0;
        if(burn_Y_N){
          u8g2.clearBuffer();
          u8g2.setCursor(16*2, lcd_L1_D);
          u8g2.print("確定燒錄");
          u8g2.sendBuffer();
          delay(750);
          return 1; 
        }
        else{
          u8g2.clearBuffer();
          u8g2.setCursor(16*2, lcd_L1_D);
          u8g2.print("取消燒錄");
          u8g2.sendBuffer();
          delay(750);
          return 0;
        }
      }
      else if(key==BTN_R){//to ok
        if(burn_Y_N==0){
          burn_Y_N=1;
          have_new_buffer=1;
        }
      }
      else if(key==BTN_L){
        if(burn_Y_N==1){
          burn_Y_N=0;
          have_new_buffer=1;
        }
      }
    }
    if(millis()-T>400){
      T=millis();
      if(frame_counter<10){
        frame_counter++;
      }
      else{
        frame_counter=0;
      }
      have_new_buffer = 1;
    }
    if(have_new_buffer){
      have_new_buffer = 0;
      u8g2.clearBuffer();
      u8g2.setCursor(16*2, lcd_L1_D);
      u8g2.print("缺口向上放置IC");
      u8g2.setCursor(16*2, lcd_L2_D);
      u8g2.print("燒錄:");
      u8g2.setCursor(16*5, lcd_L2_D);
      print_now_burn_type_name();
      if(str_for_auto!=NULL){
        u8g2.setCursor(16*2, lcd_L3_D);
        u8g2.print(str_for_auto);
      }
      u8g2.setCursor(16*2, lcd_L4_D);
      u8g2.print("取消");
      u8g2.setCursor(16*6, lcd_L4_D);
      u8g2.print("開始");
      u8g2.setDrawColor(2);
      if(burn_Y_N) u8g2.drawBox(16*6,lcd_L4_U , 16*2,16);
      else u8g2.drawBox(16*2,lcd_L4_U , 16*2,16);
      switch(frame_counter){
        case 0: u8g2.drawXBMP( 0, 0, 24, 64, image_data_F1);break;
        case 1: u8g2.drawXBMP( 0, 0, 24, 64, image_data_F2);break;
        case 2: u8g2.drawXBMP( 0, 0, 24, 64, image_data_F3);break;
        case 3: u8g2.drawXBMP( 0, 0, 24, 64, image_data_F4);break;
        case 4: u8g2.drawXBMP( 0, 0, 24, 64, image_data_F5);break;
        default: u8g2.drawXBMP( 0, 0, 24, 64, image_data_Final);
      }
      u8g2.sendBuffer();
    }
  }

}
void print_ic_pin_def(bool have_change){
  u8g2.clearBuffer();
  u8g2.setDrawColor(1);
  //for(int s=1 ; s<=7 ; s++){
  //  //u8g2.setCursor(16*s+4, lcd_L1_D);
  //  //u8g2.print(char('a'+s-1));
  //  u8g2.setCursor(16*s, lcd_L2_D);
  //  u8g2.print(final_ou_pin_order[ 6 - (s-1) ]);
  //}
  for(int i=0 ; i<10 ; i++){
    if(i<7){
      u8g2.setCursor(16+16*i, lcd_L1_D);
      u8g2.print(final_ou_pin_order[i]);
    }
    else{
      u8g2.setCursor(16+16*(i-7), lcd_L2_D);
      u8g2.print(final_ou_pin_order[i]);
    }
  }
  u8g2.setDrawColor(2);
  u8g2.drawBox(16*1,lcd_L1_U , 16,32);
  u8g2.drawBox(16*3,lcd_L1_U , 16,32);
  u8g2.drawBox(16*5,lcd_L1_U , 16,32);
  u8g2.drawBox(16*7,lcd_L1_U , 16,32);
  
  u8g2.setDrawColor(1);
  if(have_change){
    u8g2.setCursor(0, lcd_L1_D);
    u8g2.print("腳");
    u8g2.setCursor(0, lcd_L2_D);
    u8g2.print("位");
    u8g2.setCursor(0, lcd_L3_D);
    u8g2.print("變");
    u8g2.setCursor(0, lcd_L4_D);
    u8g2.print("更");
    u8g2.setDrawColor(2);
    u8g2.drawBox(0,lcd_L1_U , 16,64);
  }
  else{
    u8g2.setCursor(0, lcd_L1_D);
    u8g2.print("腳");
    u8g2.setCursor(0, lcd_L2_D);
    u8g2.print("位");
    u8g2.setCursor(0, lcd_L3_D);
    u8g2.print("不");
    u8g2.setCursor(0, lcd_L4_D);
    u8g2.print("變");
  }
  
}

int compile(){
  wdt_reset();
  switch(que_num){
    case 1:return auto_solve_que1(std_id , burn_type);
    case 2:return auto_solve_que2(std_id , burn_type);
    case 3:return auto_solve_que3(std_id , burn_type);
    case 4:return auto_solve_que4(std_id , burn_type);
    case 5:return auto_solve_que5(std_id , burn_type);
    case 6:return auto_solve_que6(std_id , burn_type);
    default:return 0; 
  }
  return 1;}
void erase()  { wdt_reset();PEEL_erase();                  }
void program(){ wdt_reset();PEEL_program(ALL_MC_cfg);      }
bool verify() { wdt_reset();return PEEL_verify(ALL_MC_cfg);}

void print_inf_for_auto_burn(char *str){
  u8g2.setDrawColor(0);
  u8g2.drawBox(16*1 , lcd_L3_U , 16*7 , 32);
  u8g2.setDrawColor(1);
  u8g2.setCursor(16*2, lcd_L3_D);
  u8g2.print(str);//10
  //u8g2.sendBuffer();
}
void print_and_term_for_auto_burn(){
  u8g2.clearBuffer();
  u8g2.setDrawColor(1);
  //for(int s=1 ; s<=7 ; s++){
  //  u8g2.setCursor(16*s+4, lcd_L1_D);
  //  u8g2.print(char('a'+s-1));
  //  u8g2.setCursor(16*s, lcd_L2_D);
  //  //u8g2.print(and_term_N[s-1]);/////cnt_ou_orang_use_and_term
  //  u8g2.print(cnt_ou_orang_use_and_term[s-1]);/////cnt_ou_orang_use_and_term
  //  //and_term_N
  //}
  for(int i=0 ; i<10 ; i++){
    if(i<5){
      u8g2.setCursor(16+16*i, lcd_L1_D);
    }
    else{
      u8g2.setCursor(16+16*(i-5), lcd_L2_D);
    }
    u8g2.print(cnt_ou_orang_use_and_term[i]);
  }
  u8g2.setDrawColor(2);
  u8g2.drawBox(16*1,lcd_L1_U , 16,32);
  u8g2.drawBox(16*3,lcd_L1_U , 16,32);
  u8g2.drawBox(16*5,lcd_L1_U , 16,32);
  u8g2.drawBox(16*7,lcd_L1_U , 16,32);
  
  u8g2.setDrawColor(1);
  u8g2.setCursor(0, lcd_L1_D);
  u8g2.print("乘");
  u8g2.setCursor(0, lcd_L2_D);
  u8g2.print("積");
  u8g2.setCursor(0, lcd_L3_D);
  u8g2.print("項");
  u8g2.setCursor(0, lcd_L4_D);
  u8g2.print("數");
  //u8g2.sendBuffer();
}
void draw_proc_bar(int ps){
  u8g2.setDrawColor(1);
  u8g2.drawBox( 20 , 16*3+2 , 100+2+2 , 12);
  u8g2.setDrawColor(2);
  u8g2.drawBox(22+ps , 16*3+4 , 100-ps , 8);
}
void lcd_page_auto_burn(){
  byte burn_times = 1;   //compile  //eraser  //program  //verify
  u8g2.clearBuffer();
  u8g2.setDrawColor(1);
  u8g2.setCursor(16*1, lcd_L3_D);
  u8g2.print("編譯中...");
  draw_proc_bar(10);
  u8g2.sendBuffer();
  int res = compile();
  print_and_term_for_auto_burn();
  draw_proc_bar(20);
  u8g2.sendBuffer();
  delay(1000);
  if(res>0){
    u8g2.clearBuffer();
    if(que_num==2 && burn_type==1){}
    else if(que_num==3 && burn_type==4){}
    else{//if  change que must update
      print_ic_pin_def(res-1);
    }
    while(digitalRead(BTN_OK)==0){}
  }
  else{//0
    u8g2.setCursor(16*2, lcd_L3_D);
    u8g2.print("編譯失敗");
    u8g2.sendBuffer();
    buzz_sound_burn_failed();
    delay(2000);
    while(digitalRead(BTN_OK)==0){}
    return;
  }
  while(1){
    print_inf_for_auto_burn("erase...  ");
    draw_proc_bar(40);
    u8g2.sendBuffer();
    erase();
    
    print_inf_for_auto_burn("program...");
    draw_proc_bar(60);
    u8g2.sendBuffer();
    program();

    print_inf_for_auto_burn("verify...");
    draw_proc_bar(90);
    u8g2.sendBuffer();
    res = verify();
    draw_proc_bar(95);
    u8g2.sendBuffer();
    if(res){
      print_inf_for_auto_burn("燒錄完成  ");
      u8g2.setCursor(16*3, lcd_L4_D);
      u8g2.print("任意鍵結束");
      u8g2.setDrawColor(2);
      u8g2.drawBox(16*3 , lcd_L4_U , 16*5 , 16);
      u8g2.sendBuffer();
      buzz_sound_burn_finish();
      while(dect_btn()==0){}
      return ;
    }
    else{
      buzz_sound_burn_failed();
      bool re_burn = 1;
      bool new_F = 1;
      while(1){
        byte key = dect_btn();
        if(key==BTN_OK){
          break;
        }
        else if(key==BTN_R){
          if(re_burn==0){
            re_burn=1;
            new_F=1;
          }
        }
        else if(key==BTN_L){
          if(re_burn==1){
            re_burn=0;
            new_F=1;
          }
        }
        if(new_F){
          new_F = 0;
          u8g2.setDrawColor(0);
          u8g2.drawBox(16*1 , lcd_L3_U , 16*7 , 32);
          u8g2.setDrawColor(1);
          u8g2.setCursor(16*2, lcd_L3_D);
          u8g2.print("燒錄失敗");
          u8g2.setCursor(16*2, lcd_L4_D);
          u8g2.print("取消");
          u8g2.setCursor(16*6, lcd_L4_D);
          u8g2.print("重燒");
          u8g2.setDrawColor(2);
          if(re_burn)u8g2.drawBox(16*6 , lcd_L4_U , 16*2 , 16);
          else u8g2.drawBox(16*2 , lcd_L4_U , 16*2 , 16);
          u8g2.sendBuffer();
        }
      }
      if(!re_burn){
        return;
      }
    }  
  }
}












