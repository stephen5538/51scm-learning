#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
//定义 74HC595 控制管脚
sbit SRCLK = P3 ^ 6; //移位寄存器时钟输入
sbit RCLK595 = P3 ^ 5;  //存储寄存器时钟输入
sbit SER = P3 ^ 4;
#define LEDDZ_COL_PORT P0 //点阵列控制端口

u8 gled_row[8] = {0x38, 0x7C, 0x7E, 0x3F, 0x3F, 0x7E, 0x7C, 0x38};
u8 gled_col[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};

void delay_10us(u16 ten_us)
{
    while (ten_us--)
    {
    }
}
void hc595_write_data(u8 dat)
{
    u8 i = 0;
		RCLK595 = 0;
    for (i = 0; i < 8; i++) //循环 8 次即可将一个字节写入寄存器中
    {
        SER = dat >> 7; //优先传输一个字节中的高位
        dat <<= 1;      //将低位移动到高位
        SRCLK = 0;
        delay_10us(1);
        SRCLK = 1;
        delay_10us(1); //移位寄存器时钟上升沿将端口数据送入寄存器中
    }
   
		RCLK595 = 1; //存储寄存器时钟上升沿将前面写入到寄存器的数据输出
    delay_10us(1);
    
}

int main()
{
    u8 i = 0;
    while (1)
    {
        for (i = 0; i < 8; i++)
        {
            hc595_write_data(gled_row[i]);
            LEDDZ_COL_PORT = gled_col[i];
            delay_10us(100);
            hc595_write_data(0);
        }
    }

    return 0;
}
