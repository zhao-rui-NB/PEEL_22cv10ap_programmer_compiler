#include <U8g2lib.h>
//pin define
#define BTN_L   A9//A9
#define BTN_R   A14//A8
#define BTN_D   A8//A10
#define BTN_OK  A12//A12
#define BTN_U   A10//A14

#define BUZZ    43//

#define lcd_L1_U 0
#define lcd_L2_U 16
#define lcd_L3_U 32
#define lcd_L4_U 48

#define lcd_L1_D 15-1
#define lcd_L2_D 31-1
#define lcd_L3_D 47-1
#define lcd_L4_D 63-1

#define PEEL_IAD7 24
#define PEEL_IAD6 26
#define PEEL_IAD5 28
#define PEEL_IAD4 30
#define PEEL_IAD3 31
#define PEEL_IAD2 29
#define PEEL_IAD1 27
#define PEEL_IAD0 25

#define PEEL_TGA4 16//15
#define PEEL_TGA3 17
#define PEEL_TGA2 13
#define PEEL_TGA1 11
#define PEEL_TGA0 9

#define MODE_A 20
#define MODE_B 22

#define PVE 18
#define PCK 3
#define ILL 7

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 44, /* data=*/ 46, /* CS=*/ 47 );