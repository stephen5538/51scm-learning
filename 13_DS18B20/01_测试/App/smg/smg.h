#ifndef _smg_H
#define _smg_H

#include "public.h"
//数码管段选引脚
#define SMG_A_DP_PORT P0

//数码管位选引脚
sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

void smg_display(u8 dat[], u8 pos);

//共阴极数码管显示 0-F 的断码数据


#endif