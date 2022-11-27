#include <reg52.h>
typedef unsigned int u16; //对系统默认数据类型进行重定义
typedef unsigned char u8;
sbit BEEP = P2 ^ 5;
void delay_10us(u16 ten_us)
{
    while (ten_us--)
        ;
}
int main(int argc, char const *argv[])
{
    u16 i = 2000;
    while (1)
    {
        while (i--)
        {
            BEEP = !BEEP;
            delay_10us(100);
        }
        i = 0;
        BEEP = 0;//关闭蜂鸣器
    }

    return 0;
}
