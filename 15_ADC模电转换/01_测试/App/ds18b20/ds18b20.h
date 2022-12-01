#ifndef _DS18B20_H
#define _DS18B20_H

#include "public.h"

sbit DS18B20_PORT = P3 ^ 7;
//函数声明
u8 ds18b20_init(void);
float ds18b20_read_temperture(void);
#endif