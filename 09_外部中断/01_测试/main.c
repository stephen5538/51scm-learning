#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

sbit LED1 = P2 ^ 0;
//独立按键k3引脚
sbit KEY3 = P3 ^ 2;
void delay_10us(u16 ten_us)
{
    while (ten_us--)
        ;
}

void exti0_init()
{
    IT0 = 1; //跳变沿触发方式（下降沿）
    EX0 = 1;
    ;       //打开 INT0 的中断允许
    EA = 1; //打开总中断
}

int main()
{
    exti0_init();
    while (1)
    {
        /* code */
    }

    return 0;
}

void exti0() interrupt 0
{
    //消抖
    delay_10us(1000);

    if (KEY3 == 0)
    {
        LED1 = !LED1;
    }
}