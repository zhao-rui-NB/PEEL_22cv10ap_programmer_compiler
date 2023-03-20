#define printJED

#include "bool_solver.h"

void print_byte_bin(byte D){
    for(int i=7 ; i>=0 ; i--){
        Serial.print(bool(D&(1<<i)));
    }
}
void print_jed(){
    int L = 0;
    for(int i=0 ; i<132 ; i++){
        switch(L){
            case 0    : Serial.println(); Serial.println("Clear");break;
            case 44   : Serial.println(); Serial.println("output pin 23 (M0)");break;
            case 440  : Serial.println(); Serial.println("output pin 22 (M1)");break;
            case 924  : Serial.println(); Serial.println("output pin 21 (M2)");break;
            case 1496 : Serial.println(); Serial.println("output pin 20 (M3)");break;
            case 2156 : Serial.println(); Serial.println("output pin 19 (M4)");break;
            case 2904 : Serial.println(); Serial.println("output pin 18 (M5)");break;
            case 3652 : Serial.println(); Serial.println("output pin 17 (M6)");break;
            case 4312 : Serial.println(); Serial.println("output pin 16 (M7)");break;
            case 4884 : Serial.println(); Serial.println("output pin 15 (M8)");break;
            case 5368 : Serial.println(); Serial.println("output pin 14 (M9)");break;
            case 5764 : Serial.println(); Serial.println("preaet");break;
            case 5808 : Serial.println(); Serial.println("macrocell");break;
        }
        Serial.print("L");
        Serial.print(L);
        Serial.print("\t");
        
        for(int j=0 ; j<6 ; j++){
            //Serial.print(JED[i][j]);
            print_byte_bin(JED[i][j]);
            Serial.print(" ");
        }
        Serial.println();
        L+=44;
    }
}
void jed_array_init(){
    for(int i=0 ; i<132 ; i++){
        for(int j=0 ; j<6 ; j++){
            JED[i][j] = 0xff;
        }
    }
}
int get_pin_node_number(int pin){
    switch(pin){
        case 1  : return PIN_1;
        case 2  : return PIN_2;
        case 3  : return PIN_3;
        case 4  : return PIN_4;
        case 5  : return PIN_5;
        case 6  : return PIN_6;
        case 7  : return PIN_7;
        case 8  : return PIN_8;
        case 9  : return PIN_9;
        case 10 : return PIN_10;
        case 11 : return PIN_11;
        case 13 : return PIN_13;
        case 14 : return FB_14;
        case 15 : return FB_15;
        case 16 : return FB_16;
        case 17 : return FB_17;
        case 18 : return FB_18;
        case 19 : return FB_19;
        case 20 : return FB_20;
        case 21 : return FB_21;
        case 22 : return FB_22;
        case 23 : return FB_23;
    }    
}
int get_term_line_number(int pin  , int pos){
    switch(pin){
        case 23 : return pgm_read_byte(AND_for_MC23+pos);
        case 22 : return pgm_read_byte(AND_for_MC22+pos);
        case 21 : return pgm_read_byte(AND_for_MC21+pos);
        case 20 : return pgm_read_byte(AND_for_MC20+pos);
        case 19 : return pgm_read_byte(AND_for_MC19+pos);
        case 18 : return pgm_read_byte(AND_for_MC18+pos);
        case 17 : return pgm_read_byte(AND_for_MC17+pos);
        case 16 : return pgm_read_byte(AND_for_MC16+pos);
        case 15 : return pgm_read_byte(AND_for_MC15+pos);
        case 14 : return pgm_read_byte(AND_for_MC14+pos);
    }
    return NULL;
}
int hm_one_in_true_table(int ou_pos , unsigned int true_table[] , int table_size){
    int cnt = 0 ; 
    for(int i=0 ; i<table_size ; i++){
        if( (1<<ou_pos)&true_table[i] ){
            cnt++;
        }
    }
    return cnt;
}
void put_minterm_to_new_array(int ou_pos ,unsigned int true_table[] , int table_size , unsigned long min_array[]){
    unsigned long cnt = 0 ; 
    for(unsigned long i=0 ; i<table_size ; i++){
        if( (1UL<<ou_pos)&true_table[i] ){
            min_array[cnt] = i;
            cnt++;
        }
    }
}
void write_term(int trem , int pin_name , bool data){
    if(data){
        JED[trem][pin_name/8] |= (1<<(7-pin_name%8));
    }
    else{
        JED[trem][pin_name/8] &= ~(1<<(7-pin_name%8));
    }
    JED[trem][5] &= 0xFE;
}
void disable_not_use_term(){
    for(int t=0 ; t<132 ; t++){
        bool dont_do = 0;
        for(int i=0 ; i<10 ; i++){
            if(t==pgm_read_byte(EN_and_line+i)){
               dont_do=1;
               break;
            }
        }
        if(!dont_do){
            if(JED[t][5]&1){
                JED[t][0]&=0b1111;
            }
        }
    }
}
void count_hm_must_use_and_term_for_each_pin(byte N_in, byte in_pin[], byte N_ou, byte ou_pin[],int table_size,unsigned int comb_data[],int dont_care_size,unsigned long dont_care_data[]){
//global_N_ou = N_ou;
    for(int i=0 ; i<N_ou ; i++){//幾個輸出畫簡幾次
//global_ou_pin[i] = ou_pin[i];
        int n = hm_one_in_true_table(i , comb_data , table_size);
        unsigned long *min_arr = new unsigned long[n];
        put_minterm_to_new_array(i, comb_data , table_size , min_arr);
        
        node *resault_head  = main_MQ_bool_solver(min_arr , n , dont_care_data , dont_care_size);
        table table1;
        table1.node_head = resault_head;
        //print_table_f(&table1);
        int node_N_counter=0;
        node *cur_nod;
        cur_nod = resault_head;
        while(cur_nod!=NULL){
            node_N_counter++;
            cur_nod = cur_nod->next_node;
        }
        delete_all_node(&resault_head);
        delete [] min_arr;
        cnt_ou_orang_use_and_term[i] = node_N_counter;
    }
    Serial.print("use term : ");
    for(int i=0; i<N_ou ; i++){
        Serial.print(cnt_ou_orang_use_and_term[i]);
        Serial.print(" ");
    }
    Serial.print("\n\n");
    
}
int convert_to_JED(byte N_in, byte in_pin[], byte N_ou, byte ou_pin[],int table_size,unsigned int comb_data[],int dont_care_size,unsigned long dont_care_data[]){
    for(int i=0 ; i<N_ou ; i++){//幾個輸出畫簡幾次   //dont_care_data is already lD min term array
        int n = hm_one_in_true_table(i , comb_data , table_size);
        //int D = hm_one_in_true_table(i , dont_care_data , dont_care_size);
        unsigned long *min_arr = new unsigned long[n];
        //unsigned long *don_arr = new unsigned long[D];;
        put_minterm_to_new_array(i, comb_data , table_size , min_arr);
        //put_minterm_to_new_array(i, comb_data , table_size , min_arr);
    
        node *resault_head  = main_MQ_bool_solver(min_arr , n , dont_care_data , dont_care_size);
        table table1;
        table1.node_head = resault_head;
//print_table_f(&table1);
        int node_N_counter=0;
        node *cur_nod;
        cur_nod = resault_head;
        while(cur_nod!=NULL){
            node_N_counter++;
            cur_nod = cur_nod->next_node;
        }
        if(node_N_counter > pgm_read_byte(N_AND_term+(ou_pin[i]-14) )){
            delete_all_node(&resault_head);
            delete [] min_arr;
            //delete [] don_arr;
            return i*(-1);
        }
        cur_nod = resault_head;
        node_N_counter = 0;
        while(cur_nod!=NULL){
            int jed_line_num = get_term_line_number(ou_pin[i] , node_N_counter );
            for(int p=0 ; p<N_in ; p++){
                if( ~(cur_nod->dash_mask) & (1UL<<p) ){
                    if(cur_nod->func_bin & (1UL<<p)){
                        write_term(jed_line_num , get_pin_node_number(in_pin[p])  , 0 );
                    }
                    else{
                        write_term(jed_line_num , get_pin_node_number(in_pin[p])+1 , 0 );
                    }
                }
            }
            node_N_counter++;
            cur_nod = cur_nod->next_node;
        }
        delete_all_node(&resault_head);
        delete [] min_arr;
        //delete [] don_arr;
    }//for
    return 0;
}
void swap_byte(byte* xp, byte* yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int assign_pin(byte N_ou, byte ou_pin[],byte cnt_ou_orang_use_and_term[]){//腳位依提供的乘積項合理分配
    bool orang_order_is_good = 1;//原本照真質表輸出順序就很好
    byte pin_sort_by_and[10];//it is pin number {23,22,21,20}//macro cell 提供可使用的and數量 把少的腳邊號排前面
    byte sort_cnt_ou_orang_use_and_term_index[10];  //真值表裡每個輸出需要用的AND排序 裡面值為索引(第幾個真值表裡的輸出)[3,2,0,1]
    //byte best_pos;
    for(int i=0 ; i<10 ; i++){//預先清除輸出結果 之後沒改代表真值表順序就可以了
        final_ou_pin_order[i] = 0;
    }
    for(int i=0 ; i<N_ou ; i++){
        if(  pgm_read_byte(N_AND_term+(ou_pin[i]-14) ) < cnt_ou_orang_use_and_term[i] ){//測試每一個輸出是否AND夠用
            orang_order_is_good = 0;
        }
    }
    if(orang_order_is_good==1){
        for(int i=0 ; i<N_ou ; i++)final_ou_pin_order[i] = ou_pin[i];
        return 1;
    }
    else{//不夠用
        for(int i=0 ; i<N_ou ; i++){
            pin_sort_by_and[i] = ou_pin[i];//先複製一份真值表的腳位
            sort_cnt_ou_orang_use_and_term_index[i] = i;//先把索引放好0-N
        }
        for(int w=0 ; w<N_ou-1 ; w++){//排序 真值表出現的可用腳
            byte min_index = w;
            for(int i=w ; i<N_ou ; i++){//N_AND_term[腳位-14]為查找MC 提供的AND數
                if(pgm_read_byte(N_AND_term+(pin_sort_by_and[i]-14)) < pgm_read_byte(N_AND_term+(pin_sort_by_and[min_index]-14) ) ){
                    min_index = i;
                }
            }
            swap_byte(&pin_sort_by_and[min_index], & pin_sort_by_and[w]);
        }
        for(int w=0 ; w<N_ou-1 ; w++){//排序 按照真值表輸出所要用的AND 但排的是索引 把用最少的輸出索引放在前面
            byte min_index = w;
            for(int i=w ; i<N_ou ; i++){//cnt_ou_orang_use_and_term[輸出編號]為查找需要的AND數量
                if(cnt_ou_orang_use_and_term[sort_cnt_ou_orang_use_and_term_index[i]] < cnt_ou_orang_use_and_term[sort_cnt_ou_orang_use_and_term_index[min_index]]){
                    min_index = i;
                }
            }
            swap_byte(&sort_cnt_ou_orang_use_and_term_index[min_index], &sort_cnt_ou_orang_use_and_term_index[w]);
            

        }
        for(int i=0 ; i<N_ou ;i++){//拿出AND最少MC腳 放入 的最前面輸出編號(用最少)
            final_ou_pin_order[sort_cnt_ou_orang_use_and_term_index[i]] = pin_sort_by_and[i];
        }
    }
    orang_order_is_good = 1;
    for(int i=0 ; i<N_ou ; i++){
        if(  pgm_read_byte(N_AND_term+(final_ou_pin_order[i]-14) ) < cnt_ou_orang_use_and_term[i] ){
            orang_order_is_good = 0;
        }
    }

    if(orang_order_is_good){  return 2;}
    else { return 0;}
}


/*
void setup(){
    Serial.begin(115200);
}
void loop(){
    Serial.println("COM1    /////////////////////////////////////");
    auto_solve_que3(std_id,1);
  
    Serial.println("COM2    /////////////////////////////////////");
    auto_solve_que3(std_id,2); 
  
    Serial.println("COM3    /////////////////////////////////////");
    auto_solve_que3(std_id,3); 
  
    Serial.println("counter    /////////////////////////////////////");
    auto_solve_que3(std_id,4); 

    while(1){}   ;
}
*/
