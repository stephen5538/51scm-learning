#ifndef _2XPT2046_H
#define _2XPT2046_H
#include "public.h"

sbit DIN = P3 ^ 4;
sbit CS = P3 ^ 5;
sbit CLK = P3 ^ 6;
void xpt2046_write_data(u8 dat);
u16 xpt2046_read_data();
u16 xpt2046_read_adc_value(u8 cmd);
#endif