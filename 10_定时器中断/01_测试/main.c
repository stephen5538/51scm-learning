#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

sbit LED1 = P2 ^ 0;

void delay_10us(u16 ten_us)
{
    while (ten_us--)
        ;
}

void time0_init()
{
    TMOD |= 0x01; //选择为定时器 0 模式，工作方式 1
    //定时器初始值
    TH0 = 0xFC;
    TL0 = 0x18;
    ET0 = 1; //打开定时器0中断
    EA = 1;  //打开总中断
    TR0 = 1; //打开定时器0
}

int main()
{
    time0_init();

    while (1)
    {
        /* code */
    }

    return 0;
}

void timer0() interrupt 1
{
    static u16 i;
    TH0 = 0xFC;
    TL0 = 0x18;
    i++;
    if (i == 1000)
    {
        i = 0;
        LED1 = !LED1;
    }
}
