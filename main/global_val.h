#define  have_global_val_h

#include <U8g2lib.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

#include "_pin_define.h"
#include "_pin_define_programmer.h"

#ifndef WDTO_8S
    #define WDTO_8S 9
#endif


//++++++++++++++++++++++++++++++++++++++可變的變數++++++++++++++++++++++++++++
unsigned long last_btn_time = 0;
unsigned long start = 0;
bool btn_up = 1;
byte return_word = 0; //(for btn)

byte std_id[] = {1,1,0,1,5,4,2,3,7};
byte name_and_number[3] = {'Z',3,7};
byte que_num = 6;
byte burn_type = 0;

byte JED[133][6];
byte cnt_ou_orang_use_and_term[] = {0,0,0,0,0,0,0,0,0,0};
byte final_ou_pin_order[10] = {0,0,0,0,0,0,0,0,0,0};
bool all_output_NOT = 0;
int ALL_MC_cfg = 0b00000101;

const byte que_N = 6; //how many qusetion
const byte que_1_burn_type_N = 1;
const char  *que_1_burn_type[] = {"解碼"};
const byte que_2_burn_type_N = 2;
const char *que_2_burn_type[] = {"解碼" , "計數"};
const byte que_3_burn_type_N = 5;
const char *que_3_burn_type[] = {"AUTO" , "七段左" , "七段中" , "七段右" , "計數"};
const byte que_4_burn_type_N = 4;
const char *que_4_burn_type[] = {"row ic","col_ic","cntR","cntW"};
const byte que_5_burn_type_N = 4;
const char *que_5_burn_type[] = {"row ic","col_ic","st_reg","cnt"};
const byte que_6_burn_type_N = 7;
const char *que_6_burn_type[] = {"row_00","row_01","row_10","row_11","col_ic","st_reg","cnt"};

//24x64  // peel programmer img
const PROGMEM uint8_t image_data_F1[] = {0xfe, 0xff, 0x1f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x3e, 0x01, 0x0c, 0x1a, 0x01, 0x00, 0x1a, 0xfe, 0xff, 0x1b, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x18};
const PROGMEM uint8_t image_data_F2[] = {0xfe, 0xff, 0x1f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x3e, 0x01, 0x0c, 0x1a, 0x01, 0x00, 0x1a, 0xfe, 0xff, 0x1b, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const PROGMEM uint8_t image_data_F3[] = {0xfe, 0xff, 0x1f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x3d, 0x00, 0x2f, 0x3d, 0x00, 0x2f, 0x01, 0x00, 0x20, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x3e, 0x01, 0x0c, 0x1a, 0x01, 0x00, 0x26, 0xfe, 0xff, 0x27, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const PROGMEM uint8_t image_data_F4[] = {0xfe, 0xff, 0x1f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0xf1, 0xff, 0x23, 0x1d, 0x12, 0x2e, 0xd1, 0x12, 0x22, 0xd1, 0x0c, 0x22, 0x1d, 0x00, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x21, 0x22, 0x1d, 0x43, 0x2e, 0x11, 0x45, 0x22, 0x11, 0x49, 0x22, 0x1d, 0x31, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x21, 0x22, 0x1d, 0x43, 0x2e, 0x11, 0x45, 0x22, 0x11, 0x49, 0x22, 0x1d, 0x31, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x3e, 0x22, 0x1d, 0x41, 0x2e, 0x11, 0x41, 0x22, 0x11, 0x41, 0x22, 0x1d, 0x22, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x7c, 0x22, 0x1d, 0x02, 0x2e, 0x11, 0x01, 0x22, 0x11, 0x02, 0x22, 0x1d, 0x7c, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x00, 0x22, 0x1d, 0x00, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x00, 0x22, 0x1d, 0x00, 0x2e, 0x11, 0x00, 0x22, 0xf1, 0xff, 0x23, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x3e, 0x01, 0x0c, 0x1a, 0x01, 0x00, 0x26, 0xfe, 0xff, 0x27, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const PROGMEM uint8_t image_data_F5[] = {0xfe, 0xff, 0x1f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0xf1, 0xff, 0x23, 0x1d, 0x12, 0x2e, 0xd1, 0x12, 0x22, 0xd1, 0x0c, 0x22, 0x1d, 0x00, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x21, 0x22, 0x1d, 0x43, 0x2e, 0x11, 0x45, 0x22, 0x11, 0x49, 0x22, 0x1d, 0x31, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x21, 0x22, 0x1d, 0x43, 0x2e, 0x11, 0x45, 0x22, 0x11, 0x49, 0x22, 0x1d, 0x31, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x3e, 0x22, 0x1d, 0x41, 0x2e, 0x11, 0x41, 0x22, 0x11, 0x41, 0x22, 0x1d, 0x22, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x7c, 0x22, 0x1d, 0x02, 0x2e, 0x11, 0x01, 0x22, 0x11, 0x02, 0x22, 0x1d, 0x7c, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x00, 0x22, 0x1d, 0x00, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x00, 0x22, 0x1d, 0x00, 0x2e, 0x11, 0x00, 0x22, 0xf1, 0xff, 0x23, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x3e, 0x01, 0x0c, 0x1a, 0x01, 0x00, 0x1a, 0xfe, 0xff, 0x1b, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const PROGMEM uint8_t image_data_Final[] = {0xfe, 0xff, 0x1f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x0c, 0x20, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0xf1, 0xff, 0x23, 0x1d, 0x12, 0x2e, 0xd1, 0x12, 0x22, 0xd1, 0x0c, 0x22, 0x1d, 0x00, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x21, 0x22, 0x1d, 0x43, 0x2e, 0x11, 0x45, 0x22, 0x11, 0x49, 0x22, 0x1d, 0x31, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x21, 0x22, 0x1d, 0x43, 0x2e, 0x11, 0x45, 0x22, 0x11, 0x49, 0x22, 0x1d, 0x31, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x3e, 0x22, 0x1d, 0x41, 0x2e, 0x11, 0x41, 0x22, 0x11, 0x41, 0x22, 0x1d, 0x22, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x7c, 0x22, 0x1d, 0x02, 0x2e, 0x11, 0x01, 0x22, 0x11, 0x02, 0x22, 0x1d, 0x7c, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x00, 0x22, 0x1d, 0x00, 0x2e, 0x11, 0x00, 0x22, 0x11, 0x00, 0x22, 0x1d, 0x00, 0x2e, 0x11, 0x00, 0x22, 0xf1, 0xff, 0x23, 0x01, 0x00, 0x20, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x20, 0x01, 0x0c, 0x3e, 0x01, 0x0c, 0x1a, 0x01, 0x00, 0x1a, 0xfe, 0xff, 0x1b, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x18};






//++++++++++++++++++++++++++++++for que+++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++8x8 and 7seg data+++++++++++++++++++++++++++++++
#define seg_dark 0b1111111

#define seg_u_o 0b0011100
#define seg_d_o 0b1100010
#define seg_C   0b0110001
#define seg_E   0b0110000 
#define seg_n   0b1101010 
#define seg_d   0b1000010 

#define seg_only_a       0b0111111
#define seg_only_b       0b1011111
#define seg_only_c       0b1101111
#define seg_only_d       0b1110111
#define seg_only_e       0b1111011
#define seg_only_f       0b1111101
#define seg_only_g       0b1111110
#define seg_only_adef    0b0110001
#define seg_only_ad      0b0110111
#define seg_only_abcd    0b0000111

#define seg_only_abfg    0b0011100
#define seg_only_cdeg    0b1100010

const byte seg_num[10] = {
    /*0*/ 0b0000001,
    /*1*/ 0b1001111,
    /*2*/ 0b0010010,
    /*3*/ 0b0000110,
    /*4*/ 0b1001100,
    /*5*/ 0b0100100,
    /*6*/ 0b0100000,
    /*7*/ 0b0001111,
    /*8*/ 0b0000000,
    /*9*/ 0b0000100,
};

// dot arr data
#include "dotarr.h"
unsigned long get_dot_arr_col(byte ch  , int C){
    unsigned long R_data = 0;
    switch(ch){
        case 0:for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) |   pgm_read_byte(dotar_0 + R*5 + C);}return ~R_data;
        case 1:for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) |   pgm_read_byte(dotar_1 + R*5 + C);}return ~R_data;
        case 2:for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) |   pgm_read_byte(dotar_2 + R*5 + C);}return ~R_data;
        case 3:for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) |   pgm_read_byte(dotar_3 + R*5 + C);}return ~R_data;
        case 4:for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) |   pgm_read_byte(dotar_4 + R*5 + C);}return ~R_data;
        case 5:for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) |   pgm_read_byte(dotar_5 + R*5 + C);}return ~R_data;
        case 6:for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) |   pgm_read_byte(dotar_6 + R*5 + C);}return ~R_data;
        case 7:for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) |   pgm_read_byte(dotar_7 + R*5 + C);}return ~R_data;
        case 8:for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) |   pgm_read_byte(dotar_8 + R*5 + C);}return ~R_data;
        case 9:for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) |   pgm_read_byte(dotar_9 + R*5 + C);}return ~R_data;
        
        case 'A':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_A + R*5 + C);}return ~R_data;
        case 'B':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_B + R*5 + C);}return ~R_data;
        case 'C':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_C + R*5 + C);}return ~R_data;
        case 'D':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_D + R*5 + C);}return ~R_data;
        case 'E':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_E + R*5 + C);}return ~R_data;
        case 'F':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_F + R*5 + C);}return ~R_data;
        case 'G':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_G + R*5 + C);}return ~R_data;
        case 'H':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_H + R*5 + C);}return ~R_data;
        case 'I':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_I + R*5 + C);}return ~R_data;
        case 'J':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_J + R*5 + C);}return ~R_data;
        
        case 'K':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_K + R*5 + C);}return ~R_data;
        case 'L':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_L + R*5 + C);}return ~R_data;
        case 'M':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_M + R*5 + C);}return ~R_data;
        case 'N':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_N + R*5 + C);}return ~R_data;
        case 'O':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_O + R*5 + C);}return ~R_data;
        case 'P':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_P + R*5 + C);}return ~R_data;
        case 'Q':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_Q + R*5 + C);}return ~R_data;
        case 'R':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_R + R*5 + C);}return ~R_data;
        case 'S':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_S + R*5 + C);}return ~R_data;
        case 'T':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_T + R*5 + C);}return ~R_data;
        
        case 'U':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_U + R*5 + C);}return ~R_data;
        case 'V':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_V + R*5 + C);}return ~R_data;
        case 'W':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_W + R*5 + C);}return ~R_data;
        case 'X':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_X + R*5 + C);}return ~R_data;
        case 'Y':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_Y + R*5 + C);}return ~R_data;
        case 'Z':for(int R=0 ; R<7 ; R++){R_data  = (R_data<<1UL) | pgm_read_byte(dotar_Z + R*5 + C);}return ~R_data;
    }
    return 0;
}




