#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
//定义 74HC595 控制管脚
sbit SRCLK595 = P3 ^ 6; //移位寄存器时钟输入
sbit RCLK595 = P3 ^ 5;  //存储寄存器时钟输入
sbit SER = P3 ^ 4;
#define LEDDZ_COL_PORT P0 //点阵列控制端口
void delay_10us(u16 ten_us)
{
    while (ten_us--)
    {
    }
}
void hc595_write_data(u8 dat)
{
    u8 i = 0;
		RCLK595=0;
    for (i = 0; i < 8; i++) //循环 8 次即可将一个字节写入寄存器中
    {
        SER = dat >> 7; //优先传输一个字节中的高位
        dat <<= 1;      //将低位移动到高位
        SRCLK595 = 0;
        delay_10us(1);
        SRCLK595 = 1;
        delay_10us(1); //移位寄存器时钟上升沿将端口数据送入寄存器中
    }
    RCLK595 = 1;
    delay_10us(1);
    //RCLK595 = 0; //存储寄存器时钟上升沿将前面写入到寄存器的数据输出
}

int main()
{
    //将 LED 点阵左边第一列设置为 0，即 LED 阴极为低电平，其余列为 1，即高电平
    LEDDZ_COL_PORT = 0x7f;//0111 1111
    while (1)
    { //将 LED 点阵上边第一行设置为 1，即 LED 阳极为高电平，其余行为 0，即低电平
        hc595_write_data(0x80);//1000 0000
    }

    return 0;
}
