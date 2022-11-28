#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
void delay_10us(u16 ten_us)
{
    while (ten_us--)
    {
    }
}
void delay_ms(u16 ms)
{
    u16 i, j;
    for (i = ms; i > 0; i--)
    {
        for (j = 110; j > 0; j--)
        {
        }
    }
}

// 74HC595 控制管脚
//移位寄存器时钟输入
sbit SRCLK595 = P3 ^ 6;
//存储寄存器时钟输入
sbit RCLK595 = P3 ^ 5;
//串行数据输入
sbit SER = P3 ^ 4;
//点阵列控制端口
#define LEDDZ_COL_PORT P0

u8 ghc595_buf[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void ghc595_send_byte(u8 dat)
{
    u8 i;
	  RCLK595 = 0; //存储寄存器时钟上升沿将前面写入到寄存器的数据输出
    //循环将一个字节的每个byte传输
    //由高位到地位传输
    for (i = 0; i < 8; i++)
    {
        //将dat的最高位右移到第一位 赋给SER
        SER = dat >> 7;
        // dat 左移一位 将次低位放入最高位
        dat = dat << 1;
        SRCLK595 = 0;
        delay_10us(1);
        SRCLK595 = 1;
        ; //移位寄存器时钟上升沿将端口数据送入寄存器中
        delay_10us(1);
    }
    RCLK595 = 1;
    delay_10us(1);
   
}

int main()
{
    u8 i = 0;
    LEDDZ_COL_PORT = 0; //将 LED 点阵列全部设置为 0，即 LED 阴极为低电平
    while (1)
    {
        for (i = 0; i < 8; i++)
        {
            ghc595_send_byte(0);//消除前面寄存器缓存数据
            ghc595_send_byte(ghc595_buf[i]);////写入新的数据
            delay_ms(500);
        }
    }

    return 0;
}
