#ifndef have_global_val_h
    #include "global_val.h"
#endif

#include "JED_generator.h" 

//return 0 失敗
//return 1 成功
//return 2 成功但腳位修正

//array [0] func lsb 


//+++ que6
// ic 0 =>  
// ic 1 =>  
// ic 2 =>  
// ic 3 =>  
// ic 4 =>  
// ic 5 =>  
int auto_solve_que6(byte std_id[] , int which_ic){
    // scan col (x5)
    if(which_ic==0){//row L
        byte N_in = 7;
        byte in_pin[] = {2,3,4,5,6,7,8};
        byte N_ou = 7;
        byte ou_pin[] = {17,18,19,20,21,22,23};
        int table_size = 128;
        unsigned int true_table[128];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<128 ;i++) true_table[i] = 0UL;
        //img 0
        true_table[0]   = 0;
        true_table[1]   = 0;
        true_table[2]   = 0;
        true_table[3]   = 0;
        true_table[4]   = 0;
        //img 1
        true_table[0 + (1<<4)]  =  get_dot_arr_col(name_and_number[0] , 0);
        true_table[1 + (1<<4)]  =  get_dot_arr_col(name_and_number[0] , 1);
        true_table[2 + (1<<4)]  =  get_dot_arr_col(name_and_number[0] , 2);
        true_table[3 + (1<<4)]  =  get_dot_arr_col(name_and_number[0] , 3);
        true_table[4 + (1<<4)]  =  get_dot_arr_col(name_and_number[0] , 4);
        //img 2
        true_table[0 + (2<<4)]  =  get_dot_arr_col(name_and_number[1] , 0);
        true_table[1 + (2<<4)]  =  get_dot_arr_col(name_and_number[1] , 1);
        true_table[2 + (2<<4)]  =  get_dot_arr_col(name_and_number[1] , 2);
        true_table[3 + (2<<4)]  =  get_dot_arr_col(name_and_number[1] , 3);
        true_table[4 + (2<<4)]  =  get_dot_arr_col(name_and_number[1] , 4);
        //img 3
        true_table[0 + (3<<4)]  =  get_dot_arr_col(name_and_number[2] , 0);
        true_table[1 + (3<<4)]  =  get_dot_arr_col(name_and_number[2] , 1);
        true_table[2 + (3<<4)]  =  get_dot_arr_col(name_and_number[2] , 2);
        true_table[3 + (3<<4)]  =  get_dot_arr_col(name_and_number[2] , 3);
        true_table[4 + (3<<4)]  =  get_dot_arr_col(name_and_number[2] , 4);
        //img 4
        true_table[0 + (4<<4)]  =  0;
        true_table[1 + (4<<4)]  =  0;
        true_table[2 + (4<<4)]  =  0;
        true_table[3 + (4<<4)]  =  0;
        true_table[4 + (4<<4)]  =  0;
        //img 5
        true_table[0 + (5<<4)]  =  get_dot_arr_col(name_and_number[2] , 0);
        true_table[1 + (5<<4)]  =  get_dot_arr_col(name_and_number[2] , 1);
        true_table[2 + (5<<4)]  =  get_dot_arr_col(name_and_number[2] , 2);
        true_table[3 + (5<<4)]  =  get_dot_arr_col(name_and_number[2] , 3);
        true_table[4 + (5<<4)]  =  get_dot_arr_col(name_and_number[2] , 4);

        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_dect;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(N_ou, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        return 1;
    }
    if(which_ic==1){//row 01
        byte N_in = 7;
        byte in_pin[] = {2,3,4,5,6,7,8};
        byte N_ou = 7;
        byte ou_pin[] = {17,18,19,20,21,22,23};
        int table_size = 128;
        unsigned int true_table[128];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<128 ;i++) true_table[i] = 0UL;
        //img 0
        true_table[5]           =  get_dot_arr_col(name_and_number[0] , 0);
        true_table[6]           =  get_dot_arr_col(name_and_number[0] , 1);
        true_table[7]           =  get_dot_arr_col(name_and_number[0] , 2);
        true_table[8]           =  get_dot_arr_col(name_and_number[0] , 3);
        true_table[9]           =  get_dot_arr_col(name_and_number[0] , 4);
        //img 1 
        true_table[5 + (1<<4)]  =  get_dot_arr_col(name_and_number[1] , 0);
        true_table[6 + (1<<4)]  =  get_dot_arr_col(name_and_number[1] , 1);
        true_table[7 + (1<<4)]  =  get_dot_arr_col(name_and_number[1] , 2);
        true_table[8 + (1<<4)]  =  get_dot_arr_col(name_and_number[1] , 3);
        true_table[9 + (1<<4)]  =  get_dot_arr_col(name_and_number[1] , 4);
        //img 2
        true_table[5 + (2<<4)]  =  get_dot_arr_col(name_and_number[2] , 0);
        true_table[6 + (2<<4)]  =  get_dot_arr_col(name_and_number[2] , 1);
        true_table[7 + (2<<4)]  =  get_dot_arr_col(name_and_number[2] , 2);
        true_table[8 + (2<<4)]  =  get_dot_arr_col(name_and_number[2] , 3);
        true_table[9 + (2<<4)]  =  get_dot_arr_col(name_and_number[2] , 4);
        //img 3
        true_table[5 + (3<<4)]  =  0;
        true_table[6 + (3<<4)]  =  0;
        true_table[7 + (3<<4)]  =  0;
        true_table[8 + (3<<4)]  =  0;
        true_table[9 + (3<<4)]  =  0;
        //img 4
        true_table[5 + (4<<4)]  =  0;
        true_table[6 + (4<<4)]  =  0;
        true_table[7 + (4<<4)]  =  0;
        true_table[8 + (4<<4)]  =  0;
        true_table[9 + (4<<4)]  =  0;
        //img 5
        true_table[5 + (5<<4)]  =  0;
        true_table[6 + (5<<4)]  =  0;
        true_table[7 + (5<<4)]  =  0;
        true_table[8 + (5<<4)]  =  0;
        true_table[9 + (5<<4)]  =  0;

        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_dect;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(N_ou, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        return 1;
    }
    if(which_ic==2){//row 10
        byte N_in = 7;
        byte in_pin[] = {2,3,4,5,6,7,8};
        byte N_ou = 7;
        byte ou_pin[] = {17,18,19,20,21,22,23};
        int table_size = 128;
        unsigned int true_table[128];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<128 ;i++) true_table[i] = 0UL;
        //img 0
        true_table[0]           =  0;
        true_table[1]           =  0;
        true_table[2]           =  0;
        true_table[3]           =  0;
        true_table[4]           =  0;
        //img 1
        true_table[0 + (1<<4)]  =  0;
        true_table[1 + (1<<4)]  =  0;
        true_table[2 + (1<<4)]  =  0;
        true_table[3 + (1<<4)]  =  0;
        true_table[4 + (1<<4)]  =  0;
        //img 2
        true_table[0 + (2<<4)]  =  get_dot_arr_col(name_and_number[0] , 0);
        true_table[1 + (2<<4)]  =  get_dot_arr_col(name_and_number[0] , 1);
        true_table[2 + (2<<4)]  =  get_dot_arr_col(name_and_number[0] , 2);
        true_table[3 + (2<<4)]  =  get_dot_arr_col(name_and_number[0] , 3);
        true_table[4 + (2<<4)]  =  get_dot_arr_col(name_and_number[0] , 4);
        //img 3
        true_table[0 + (3<<4)]  =  get_dot_arr_col(name_and_number[1] , 0);
        true_table[1 + (3<<4)]  =  get_dot_arr_col(name_and_number[1] , 1);
        true_table[2 + (3<<4)]  =  get_dot_arr_col(name_and_number[1] , 2);
        true_table[3 + (3<<4)]  =  get_dot_arr_col(name_and_number[1] , 3);
        true_table[4 + (3<<4)]  =  get_dot_arr_col(name_and_number[1] , 4);
        //img 4
        true_table[0 + (4<<4)]  =  get_dot_arr_col(name_and_number[2] , 0);
        true_table[1 + (4<<4)]  =  get_dot_arr_col(name_and_number[2] , 1);
        true_table[2 + (4<<4)]  =  get_dot_arr_col(name_and_number[2] , 2);
        true_table[3 + (4<<4)]  =  get_dot_arr_col(name_and_number[2] , 3);
        true_table[4 + (4<<4)]  =  get_dot_arr_col(name_and_number[2] , 4);
        //img 5
        true_table[0 + (5<<4)]  =  0;
        true_table[1 + (5<<4)]  =  0;
        true_table[2 + (5<<4)]  =  0;
        true_table[3 + (5<<4)]  =  0;
        true_table[4 + (5<<4)]  =  0;

        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_dect;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(N_ou, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        return 1;
    }
    if(which_ic==3){//row 11
        byte N_in = 7;
        byte in_pin[] = {2,3,4,5,6,7,8};
        byte N_ou = 7;
        byte ou_pin[] = {17,18,19,20,21,22,23};
        int table_size = 128;
        unsigned int true_table[128];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<128 ;i++) true_table[i] = 0UL;
        //img 0
        true_table[5]           =  0;
        true_table[6]           =  0;
        true_table[7]           =  0;
        true_table[8]           =  0;
        true_table[9]           =  0;
        //img 1 
        true_table[5 + (1<<4)]  =  0;
        true_table[6 + (1<<4)]  =  0;
        true_table[7 + (1<<4)]  =  0;
        true_table[8 + (1<<4)]  =  0;
        true_table[9 + (1<<4)]  =  0;
        //img 2
        true_table[5 + (2<<4)]  =  0;
        true_table[6 + (2<<4)]  =  0;
        true_table[7 + (2<<4)]  =  0;
        true_table[8 + (2<<4)]  =  0;
        true_table[9 + (2<<4)]  =  0;
        //img 3
        true_table[5 + (3<<4)]  =  get_dot_arr_col(name_and_number[0] , 0);
        true_table[6 + (3<<4)]  =  get_dot_arr_col(name_and_number[0] , 1);
        true_table[7 + (3<<4)]  =  get_dot_arr_col(name_and_number[0] , 2);
        true_table[8 + (3<<4)]  =  get_dot_arr_col(name_and_number[0] , 3);
        true_table[9 + (3<<4)]  =  get_dot_arr_col(name_and_number[0] , 4);
        //img 4
        true_table[5 + (4<<4)]  =  get_dot_arr_col(name_and_number[1] , 0);
        true_table[6 + (4<<4)]  =  get_dot_arr_col(name_and_number[1] , 1);
        true_table[7 + (4<<4)]  =  get_dot_arr_col(name_and_number[1] , 2);
        true_table[8 + (4<<4)]  =  get_dot_arr_col(name_and_number[1] , 3);
        true_table[9 + (4<<4)]  =  get_dot_arr_col(name_and_number[1] , 4);
        //img 5
        true_table[5 + (5<<4)]  =  get_dot_arr_col(name_and_number[2] , 0);
        true_table[6 + (5<<4)]  =  get_dot_arr_col(name_and_number[2] , 1);
        true_table[7 + (5<<4)]  =  get_dot_arr_col(name_and_number[2] , 2);
        true_table[8 + (5<<4)]  =  get_dot_arr_col(name_and_number[2] , 3);
        true_table[9 + (5<<4)]  =  get_dot_arr_col(name_and_number[2] , 4);

        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_dect;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(N_ou, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        return 1;
    }
    
    else if(which_ic==4){//col ,
        byte N_in = 4;
        byte in_pin[] = {2,3,4,5};
        byte N_ou = 10;
        byte ou_pin[] = {23,22,21,20,19,18,17,16,15,14};
        int table_size = 16;
        unsigned int true_table[16];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<16 ;i++) true_table[i] = 0UL;
        true_table[0] = (1<<0) ;
        true_table[1] = (1<<1) ;
        true_table[2] = (1<<2) ;
        true_table[3] = (1<<3) ;
        true_table[4] = (1<<4) ;
        true_table[5] = (1<<5) ;
        true_table[6] = (1<<6) ;
        true_table[7] = (1<<7) ;
        true_table[8] = (1<<8) ;
        true_table[9] = (1<<9) ;


        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_dect;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(N_ou, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        return 1;
    }





    //+++++ 5 bit state reg
    //0-4 scan word 1
    //5   dark
    //6-10 scan 
    //11  dark
    //12-16
    //17  dark

    else if(which_ic==3){//state reg
        byte N_in = 6;
        byte in_pin[] = {23,22,21,20,19,2}; // 2 is x from div clk
        byte N_ou = 5;
        byte ou_pin[] = {23,22,21,20,19};
        int table_size = 64;
        unsigned int true_table[64];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<table_size ;i++) true_table[i] = 0UL;
        true_table[0]  = 1 ;  true_table[0  | (1<<5)] = 1 ;
        true_table[1]  = 2 ;  true_table[1  | (1<<5)] = 2 ;
        true_table[2]  = 3 ;  true_table[2  | (1<<5)] = 3 ;
        true_table[3]  = 4 ;  true_table[3  | (1<<5)] = 4 ;
        true_table[4]  = 0 ;

        true_table[6]  = 7 ;  true_table[6  | (1<<5)] = 7 ;
        true_table[7]  = 8 ;  true_table[7  | (1<<5)] = 8 ;
        true_table[8]  = 9 ;  true_table[8  | (1<<5)] = 9 ;
        true_table[9]  = 10;  true_table[9  | (1<<5)] = 10 ;
        true_table[10] = 6 ;

        true_table[12] = 13 ; true_table[12 | (1<<5)] = 13 ;
        true_table[13] = 14 ; true_table[13 | (1<<5)] = 14 ;
        true_table[14] = 15 ; true_table[14 | (1<<5)] = 15 ;
        true_table[15] = 16 ; true_table[15 | (1<<5)] = 16 ;
        true_table[16] = 12 ;

        //true_table[4  | (1<<5)] = 5 ;
        //true_table[10 | (1<<5)] = 10;
        //true_table[16 | (1<<5)] = 16 ;

        //when end at this word , if x go to dark
        true_table[4  | (1<<5)] = 5;  
        true_table[10 | (1<<5)] = 11;
        true_table[16 | (1<<5)] = 17; 

        // if x state at dark
        true_table[5  | (1<<5)] = 5;  
        true_table[11 | (1<<5)] = 11;
        true_table[17 | (1<<5)] = 17; 
        //else , go to next word
        true_table[5]  = 6 ;
        true_table[11] = 12 ;
        true_table[17] = 0 ;


        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_reg;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(N_ou, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        
        return 1;
    }
    else if(which_ic==4){ //counter
        byte N_in = 6;
        byte in_pin[] = {23,22,21,20,19,18};
        byte N_ou = 6;
        byte ou_pin[] = {23,22,21,20,19,18};
        int table_size = 64;
        unsigned int true_table[64];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<table_size ; i++)
            true_table[i] = i+1;
        true_table[63] = 0 ;
        
        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_reg;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(N_ou, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        
        return 1;
    }
}//que6




//++++ que5
    //+++++ 5 bit state reg
    //0-4 scan word 1
    //5   dark
    //6-10 scan 
    //11  dark
    //12-16
    //17  dark

int auto_solve_que5(byte std_id[] , int which_ic){
    // scan col (x5)
    if(which_ic==0){//row
        byte N_in = 5;
        byte in_pin[] = {2,3,4,5,6};
        byte N_ou = 7;
        byte ou_pin[] = {17,18,19,20,21,22,23};
        int table_size = 32;
        unsigned int true_table[32];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<32 ;i++) true_table[i] = 0UL;
        true_table[0] = get_dot_arr_col(name_and_number[0] , 0) ;
        true_table[1] = get_dot_arr_col(name_and_number[0] , 1) ;
        true_table[2] = get_dot_arr_col(name_and_number[0] , 2) ;
        true_table[3] = get_dot_arr_col(name_and_number[0] , 3) ;
        true_table[4] = get_dot_arr_col(name_and_number[0] , 4) ;

        true_table[6] = get_dot_arr_col(name_and_number[1] , 0) ;
        true_table[7] = get_dot_arr_col(name_and_number[1] , 1) ;
        true_table[8] = get_dot_arr_col(name_and_number[1] , 2) ;
        true_table[9] = get_dot_arr_col(name_and_number[1] , 3) ;
        true_table[10] = get_dot_arr_col(name_and_number[1] , 4) ;

        true_table[12] = get_dot_arr_col(name_and_number[2] , 0) ;
        true_table[13] = get_dot_arr_col(name_and_number[2] , 1) ;
        true_table[14] = get_dot_arr_col(name_and_number[2] , 2) ;
        true_table[15] = get_dot_arr_col(name_and_number[2] , 3) ;
        true_table[16] = get_dot_arr_col(name_and_number[2] , 4) ;
        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_dect;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(7, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        return 1;
    }
    else if(which_ic==1){//col
        byte N_in = 5;
        byte in_pin[] = {2,3,4,5,6};
        byte N_ou = 5;
        byte ou_pin[] = {23,22,21,20,19};
        int table_size = 32;
        unsigned int true_table[32];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<32 ;i++) true_table[i] = 0UL;
        true_table[0] = 0B00001 ;
        true_table[1] = 0B00010 ;
        true_table[2] = 0B00100 ;
        true_table[3] = 0B01000 ;
        true_table[4] = 0B10000 ;

        true_table[6] = 0B00001 ;
        true_table[7] = 0B00010 ;
        true_table[8] = 0B00100 ;
        true_table[9] = 0B01000 ;
        true_table[10]= 0B10000 ;

        true_table[12] = 0B00001 ;
        true_table[13] = 0B00010 ;
        true_table[14] = 0B00100 ;
        true_table[15] = 0B01000 ;
        true_table[16] = 0B10000 ;

        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_dect;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(N_ou, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        return 1;
    }
    //+++++ 5 bit state reg
    //0-4 scan word 1
    //5   dark
    //6-10 scan 
    //11  dark
    //12-16
    //17  dark

    else if(which_ic==2){//state reg
        byte N_in = 6;
        byte in_pin[] = {23,22,21,20,19,2}; // 2 is x from div clk
        byte N_ou = 5;
        byte ou_pin[] = {23,22,21,20,19};
        int table_size = 64;
        unsigned int true_table[64];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<table_size ;i++) true_table[i] = 0UL;
        true_table[0]  = 1 ;  true_table[0  | (1<<5)] = 1 ;
        true_table[1]  = 2 ;  true_table[1  | (1<<5)] = 2 ;
        true_table[2]  = 3 ;  true_table[2  | (1<<5)] = 3 ;
        true_table[3]  = 4 ;  true_table[3  | (1<<5)] = 4 ;
        true_table[4]  = 0 ;

        true_table[6]  = 7 ;  true_table[6  | (1<<5)] = 7 ;
        true_table[7]  = 8 ;  true_table[7  | (1<<5)] = 8 ;
        true_table[8]  = 9 ;  true_table[8  | (1<<5)] = 9 ;
        true_table[9]  = 10;  true_table[9  | (1<<5)] = 10 ;
        true_table[10] = 6 ;

        true_table[12] = 13 ; true_table[12 | (1<<5)] = 13 ;
        true_table[13] = 14 ; true_table[13 | (1<<5)] = 14 ;
        true_table[14] = 15 ; true_table[14 | (1<<5)] = 15 ;
        true_table[15] = 16 ; true_table[15 | (1<<5)] = 16 ;
        true_table[16] = 12 ;

        //true_table[4  | (1<<5)] = 5 ;
        //true_table[10 | (1<<5)] = 10;
        //true_table[16 | (1<<5)] = 16 ;

        //when end at this word , if x go to dark
        true_table[4  | (1<<5)] = 5;  
        true_table[10 | (1<<5)] = 11;
        true_table[16 | (1<<5)] = 17; 

        // if x state at dark
        true_table[5  | (1<<5)] = 5;  
        true_table[11 | (1<<5)] = 11;
        true_table[17 | (1<<5)] = 17; 
        //else , go to next word
        true_table[5]  = 6 ;
        true_table[11] = 12 ;
        true_table[17] = 0 ;


        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_reg;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(N_ou, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        
        return 1;
    }
    else if(which_ic==3){ //counter
        byte N_in = 6;
        byte in_pin[] = {23,22,21,20,19,18};
        byte N_ou = 6;
        byte ou_pin[] = {23,22,21,20,19,18};
        int table_size = 64;
        unsigned int true_table[64];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<table_size ; i++)
            true_table[i] = i+1;
        true_table[63] = 0 ;
        
        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_reg;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(N_ou, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        
        return 1;
    }
}//que5



int auto_solve_que4(byte std_id[] , int which_ic){

    
    if(which_ic==0){//row
        byte N_in = 5;
        byte in_pin[] = {2,3,4,5,6};
        byte N_ou = 7;
        byte ou_pin[] = {17,18,19,20,21,22,23};
        int table_size = 32;
        unsigned int true_table[32];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<32 ;i++) true_table[i] = 0UL;
        true_table[0*8+0] = get_dot_arr_col(name_and_number[0] , 0) ;
        true_table[0*8+1] = get_dot_arr_col(name_and_number[0] , 1) ;
        true_table[0*8+2] = get_dot_arr_col(name_and_number[0] , 2) ;
        true_table[0*8+3] = get_dot_arr_col(name_and_number[0] , 3) ;
        true_table[0*8+4] = get_dot_arr_col(name_and_number[0] , 4) ;

        true_table[1*8+0] = get_dot_arr_col(name_and_number[1] , 0) ;
        true_table[1*8+1] = get_dot_arr_col(name_and_number[1] , 1) ;
        true_table[1*8+2] = get_dot_arr_col(name_and_number[1] , 2) ;
        true_table[1*8+3] = get_dot_arr_col(name_and_number[1] , 3) ;
        true_table[1*8+4] = get_dot_arr_col(name_and_number[1] , 4) ;

        true_table[2*8+0] = get_dot_arr_col(name_and_number[2] , 0) ;
        true_table[2*8+1] = get_dot_arr_col(name_and_number[2] , 1) ;
        true_table[2*8+2] = get_dot_arr_col(name_and_number[2] , 2) ;
        true_table[2*8+3] = get_dot_arr_col(name_and_number[2] , 3) ;
        true_table[2*8+4] = get_dot_arr_col(name_and_number[2] , 4) ;
        ALL_MC_cfg = MC_cfg_dect;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(7, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        return 1;
    }
    else if(which_ic==1){
        byte N_in = 3;
        byte in_pin[] = {2,3,4};
        byte N_ou = 5;
        byte ou_pin[] = {23,22,21,20,19};
        int table_size = 8;
        unsigned int true_table[8];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<8 ;i++) true_table[i] = 0UL;
        true_table[0] = 0B10000 ;
        true_table[1] = 0B01000 ;
        true_table[2] = 0B00100 ;
        true_table[3] = 0B00010 ;
        true_table[4] = 0B00001 ;
        ALL_MC_cfg = MC_cfg_dect;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(5, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        return 1;
    }
    else if(which_ic==2){
        byte N_in = 3;
        byte in_pin[] = {23,22,21};
        byte N_ou = 3;
        byte ou_pin[] = {23,22,21};
        int table_size = 8;
        unsigned int true_table[8];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        for(int i=0 ; i<8 ;i++) true_table[i] = 0UL;
        true_table[0] = 1 ;
        true_table[1] = 2 ;
        true_table[2] = 3 ;
        true_table[3] = 4 ;
        true_table[4] = 0 ;
        ALL_MC_cfg = MC_cfg_reg;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(3, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        
        return 1;
    }
    else if(which_ic==3){
        byte N_in = 2;
        byte in_pin[] = {23,22};
        byte N_ou = 2;
        byte ou_pin[] = {23,22};
        int table_size = 4;
        unsigned int true_table[4];
        int dont_care_size = 0;
        unsigned long dont_care[] = {};   
        
        true_table[0] = 1 ;
        true_table[1] = 2 ;
        true_table[2] = 0 ;
        true_table[3] = 0 ;
        
        ALL_MC_cfg = MC_cfg_reg;
        jed_array_init();
        count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
        assign_pin(3, ou_pin ,cnt_ou_orang_use_and_term);
        int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
        if(re<0)return 0;
        disable_not_use_term();
        print_jed();
        
        return 1;
    }





    
}

int auto_solve_que3(byte std_id[] , int which_ic){
    byte N_in = 6;
    byte in_pin[] = {2,3,4,5,6,7};
    
    byte N_ou = 7;
    // byte ou_pin[] = {17,18,19,20,21,22,23};//right
    //byte ou_pin[] = {22,21,20,19,18,17,16};
byte ou_pin[] = {16,17,18,19,20,21,22,23};
    //byte ou_pin[] = {22,21,20,19,18,17,16};
    int table_size = 50;
    unsigned int true_table[50];
    int dont_care_size = 14;
    unsigned long dont_care[] = {50,51,52,53,54,55,56,57,58,59,60,61,62,63};   
    if(which_ic==1){
        for(int i=0 ; i<50 ;i++) true_table[i] = seg_dark;
        true_table[3] = seg_C;
        for(int i=0 ; i<9 ; i++) true_table[4+i] = seg_num[ std_id[i] ];
        true_table[14] = seg_C;
        for(int i=0 ; i<9 ; i++) true_table[15+i] = seg_num[ std_id[i] ];
        true_table[29] = seg_only_abfg;
        true_table[30] = seg_only_cdeg;
        true_table[36] = seg_only_a;
        true_table[37] = seg_only_f;
        true_table[38] = seg_only_e;
        true_table[39] = seg_only_d;
        true_table[45] = seg_only_adef;
        true_table[47] = seg_only_adef;
        true_table[49] = seg_E;
        //反轉使化簡
        all_output_NOT = 1;
        ALL_MC_cfg = MC_cfg_dect;
        for(int i=0 ; i<50 ; i++)true_table[i]  = ~true_table[i];
    }
    else if(which_ic==2){
        for(int i=0 ; i<50 ;i++) true_table[i] = seg_dark;
        true_table[2] = seg_C;
        for(int i=0 ; i<9 ; i++) true_table[3+i] = seg_num[ std_id[i] ];
        true_table[15] = seg_C;
        for(int i=0 ; i<9 ; i++) true_table[16+i] = seg_num[ std_id[i] ];
        true_table[28] = seg_only_cdeg;
        true_table[31] = seg_only_abfg;
        true_table[35] = seg_only_a;
        true_table[40] = seg_only_d;
        true_table[45] = seg_only_ad;
        true_table[47] = seg_only_ad;
        true_table[49] = seg_n;
        //反轉使化簡
        all_output_NOT = 1;
        ALL_MC_cfg = MC_cfg_dect;
        for(int i=0 ; i<50 ; i++)true_table[i]  = ~true_table[i];
    }
    else if(which_ic==3){
        for(int i=0 ; i<50 ;i++) true_table[i] = seg_dark;
        true_table[1] = seg_C;
        for(int i=0 ; i<9 ; i++) true_table[2+i] = seg_num[ std_id[i] ];
        true_table[16] = seg_C;
        for(int i=0 ; i<9 ; i++) true_table[17+i] = seg_num[ std_id[i] ];
        true_table[27] = seg_only_abfg;
        true_table[32] = seg_only_cdeg;
        true_table[34] = seg_only_a;
        true_table[41] = seg_only_d;
        true_table[42] = seg_only_c;
        true_table[43] = seg_only_b;
        true_table[45] = seg_only_abcd;
        true_table[47] = seg_only_abcd;
        true_table[49] = seg_d;
        //反轉使化簡
        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_dect;
        for(int i=0 ; i<50 ; i++){Serial.print(true_table[i]);Serial.print(" "); true_table[i]= ~true_table[i]; Serial.println(true_table[i]);}
    }
    else if(which_ic==4){
        for(int i=0 ; i<49 ; i++)true_table[i]  = i+1;
        true_table[49] = 0;
        N_ou = 6; 
        in_pin[0] = 22;
        in_pin[1] = 21;
        in_pin[2] = 20;
        in_pin[3] = 19;
        in_pin[4] = 18;
        in_pin[5] = 17;
        ou_pin[0] = 22;
        ou_pin[1] = 21;
        ou_pin[2] = 20;
        ou_pin[3] = 19;
        ou_pin[4] = 18;
        ou_pin[5] = 17;
        all_output_NOT = 0;//不反轉
        ALL_MC_cfg = MC_cfg_reg;
    }
    else{
        return 0;
    }
    if(digitalRead(BTN_OK)==0)dont_care_size=0;
    else if(digitalRead(BTN_D)==0)dont_care_size=4;
    
    jed_array_init();
    count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
    int ass_res = 1;
    if(which_ic!=4) assign_pin(7, ou_pin ,cnt_ou_orang_use_and_term);
    else ass_res = assign_pin(6, ou_pin ,cnt_ou_orang_use_and_term);
    int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
 //add change final pin order   
    if(re<0)return 0;
    disable_not_use_term();
#ifdef printJED
    print_jed();
#endif
    return ass_res;
}
int auto_solve_que2(byte std_id[] ,int which_ic){
    byte N_in = 5;
    byte in_pin[5] = {2,3,4,5,6};//前面低
    byte N_ou = 7;
    byte ou_pin[7] = {17,18,19,20,21,22,23};6;
    int table_size = 32;
    unsigned int true_table[32];
    const int dont_care_size = 0;
    unsigned long dont_care[] = {};   
    if(which_ic==0){
        for(int i=0 ; i<table_size ;i++) true_table[i] = seg_dark;
        true_table[1] = seg_num[ std_id[8] ];
        true_table[2] = seg_num[ std_id[7] ];
        true_table[4] = seg_num[ std_id[6] ];
        true_table[17] = seg_d;
        true_table[18] = seg_n;
        true_table[20] = seg_E;
        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_dect;
        
    }
    else if(which_ic==1){
        for(int i=0 ; i<31 ; i++)true_table[i]  = i+1;
        true_table[31] = 0;
        N_ou = 5;
        ou_pin[0] = 23;
        ou_pin[1] = 22;
        ou_pin[2] = 21;
        ou_pin[3] = 20;
        ou_pin[4] = 19;
        in_pin[0] = 23;
        in_pin[1] = 22;
        in_pin[2] = 21;
        in_pin[3] = 20;
        in_pin[4] = 19;
        
        all_output_NOT = 0;//不反轉
        ALL_MC_cfg = MC_cfg_reg;
        //ALL_MC_cfg = MC_cfg_dect;
    }
    else{
        return 0;
    }

    jed_array_init();
    count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
    int ass_res = 1;
    if(which_ic!=1) assign_pin(7, ou_pin ,cnt_ou_orang_use_and_term);
    else ass_res = assign_pin(5, ou_pin ,cnt_ou_orang_use_and_term);
    int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
    if(re<0)return 0;
    disable_not_use_term();
#ifdef printJED
    print_jed();
#endif
    return ass_res;
}
int auto_solve_que1(byte std_id[] ,int which_ic){
    byte N_in = 4;
    byte in_pin[] = {4,3,2,1};
    byte N_ou = 7;
    byte ou_pin[] = {17,18,19,20,21,22,23};
    int table_size = 16;
    unsigned int true_table[16];
    const int dont_care_size = 0;
    unsigned long dont_care[] = {};   
    if(which_ic==0){
        for(int i=0 ; i<16 ;i++) true_table[i] = seg_dark;
        true_table[1] = seg_C;
        for(int i=0 ; i<9 ; i++) true_table[2+i] = seg_num[ std_id[i] ];
        
        all_output_NOT = 0;
        ALL_MC_cfg = MC_cfg_dect;
    }
    else{
        return 0;
    }
    jed_array_init();
    count_hm_must_use_and_term_for_each_pin(N_in, in_pin, N_ou, ou_pin, table_size,true_table, dont_care_size,dont_care);
    int ass_res = 0;
    if(which_ic==0) ass_res = assign_pin(7, ou_pin ,cnt_ou_orang_use_and_term);
    int re = convert_to_JED(N_in, in_pin, N_ou, final_ou_pin_order, table_size,true_table , dont_care_size,dont_care);
    if(re<0)return 0;
    disable_not_use_term();
#ifdef printJED
    print_jed();
#endif
    return ass_res;
}
