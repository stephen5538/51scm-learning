#ifndef _iic_H
#define _iic_H

#include "public.h"

sbit IIC_SCL = P2 ^ 1;
sbit IIC_SDA = P2 ^ 0;

void iic_start(void);
void iic_stop(void);
void iic_write_byte(u8 txd);
u8 iic_read_byte(u8 ack);
u8 iic_wait_ack(void);
void iic_ack(void);
void iic_nack(void);

#endif
