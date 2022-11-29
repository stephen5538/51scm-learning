#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

void delay_10us(u16 ten_us)
{
    while (ten_us--)
        ;
}

void uart_init(u8 baud)
{
    //设置定时器1工作方式2
    TMOD |= 0x20;
    //工作方式1
    SCON = 0x50;
    //波特率加倍
    PCON = 0x80;
    //定时器1 初始值设置
    TH1 = baud;
    TL1 = baud;
    //打开接收中断
    ES = 1;
    //打开总中断
    EA = 1;
    //打开定时器1
    TR1 = 1;
}

int main()
{
    uart_init(0xFA);

    while (1)
    {
    }

    return 0;
}

void uart() interrupt 4
{
    u8 rec_data;
    //清除接收中断标志位
    RI = 0;
    //存储接收到的数据
    rec_data = SBUF;
    //将接收到的数据放入发送寄存器
    SBUF = rec_data;
    //等待发送完毕
    while (!TI)
    {
    }
    TI = 0;
}
