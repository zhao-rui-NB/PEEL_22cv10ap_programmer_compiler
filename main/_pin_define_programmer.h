//1:disconnect node //0:connect node 
//jed  byte*6 data
//    0       1         2         3         4         5  
//[L0..L7][L8..L15][L16..L23][L24..L31][L32..L39][L40..L43.X.X.X.have_use_this_line] 
  
#define PIN_1       0
#define PIN_1_BAR       1
#define PIN_2       4
#define PIN_2_BAR       5
#define PIN_3       8
#define PIN_3_BAR       9
#define PIN_4       12
#define PIN_4_BAR       13
#define PIN_5       16
#define PIN_5_BAR       17
#define PIN_6       20
#define PIN_6_BAR       21
#define PIN_7       24
#define PIN_7_BAR       25
#define PIN_8       28
#define PIN_8_BAR       29
#define PIN_9       32
#define PIN_9_BAR       33
#define PIN_10      36
#define PIN_10_BAR      37
#define PIN_11      40
#define PIN_11_BAR      41
#define PIN_13      42
#define PIN_13_BAR      43

#define FB_23       2
#define FB_23_bar       3
#define FB_22       6
#define FB_22_bar       7
#define FB_21       10
#define FB_21_bar       11
#define FB_20       14
#define FB_20_bar       15
#define FB_19       18
#define FB_19_bar       19
#define FB_18       22
#define FB_18_bar       23
#define FB_17       26
#define FB_17_bar       27
#define FB_16       30
#define FB_16_bar       31
#define FB_15       34
#define FB_15_bar       35
#define FB_14       38
#define FB_14_bar       39

#define MC_cfg_dect         0b00000101
#define MC_cfg_dect_not     0b00000100
#define MC_cfg_reg          0b00010001
#define MC_cfg_reg_not      0b01010000

//N of AND term at jed line
const uint8_t PROGMEM AND_for_MC23[8]     /**/      = {2,3,4,5,6,7,8,9};
const uint8_t PROGMEM AND_for_MC22[10]    /**/      = {11,12,13,14,15,16,17,18,19,20};
const uint8_t PROGMEM AND_for_MC21[12]    /**/      = {22,23,24,25,26,27,28,29,30,31,32,33};
const uint8_t PROGMEM AND_for_MC20[14]    /**/      = {35,36,37,38,39,40,41,42,43,44,45,46,47,48};
const uint8_t PROGMEM AND_for_MC19[16]    /**/      = {50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65};
const uint8_t PROGMEM AND_for_MC18[16]    /**/      = {67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82};
const uint8_t PROGMEM AND_for_MC17[14]    /**/      = {84,85,86,87,88,89,90,91,92,93,94,95,96,97};
const uint8_t PROGMEM AND_for_MC16[12]    /**/      = {99,100,101,102,103,104,105,106,107,108,109,110};
const uint8_t PROGMEM AND_for_MC15[10]    /**/      = {112,113,114,115,116,117,118,119,120,121};
const uint8_t PROGMEM AND_for_MC14[8]     /**/      = {123,124,125,126,127,128,129,130};
const uint8_t PROGMEM N_AND_term[10]      /**/      = {8,10,12,14,16,16,14,12,10,8};
const uint8_t PROGMEM EN_and_line[10]     /**/      = {1,10,21,34,49,66,83,98,111,122}; 


