#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
//独立按键的引脚
sbit KEY1 = P3 ^ 1;
sbit KEY2 = P3 ^ 0;
sbit KEY3 = P3 ^ 2;
sbit KEY4 = P3 ^ 3;
// LED1引脚
sbit LED1 = P2 ^ 0;
//独立按键按下的键值
#define KEY1_PRESS 1
#define KEY2_PRESS 2
#define KEY3_PRESS 3
#define KEY4_PRESS 4
#define KEY_UNPRESS 0

void delay_10us(u16 ten_us)
{
    while (ten_us--)
    {
        /* code */
    }
}
/**
 * @brief
 *
 * @param mode mode=1 连续扫描按键
 *             mode=0 单次扫描按键
 * @return u8
 */
u8 key_scan(u8 mode)
{
    //static 全局变量
    static u8 key = 1;
    //连续扫描按键
    if (mode)
    {
        key = 1;
    }
    if (key == 1 && (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0))
    {
        delay_10us(1000);
        key = 0;
        if (KEY1 == 0)
        {
            return KEY1_PRESS;
        }
        if (KEY2 == 0)
        {
            return KEY2_PRESS;
        }
        if (KEY3 == 0)
        {
            return KEY3_PRESS;
        }
        if (KEY4 == 0)
        {
            return KEY1_PRESS;
        }
    }
    //当四个按键全部都变成1 高电平的时候 才将key 重新置为1
    else if (KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1)
    {
        key = 1;
    }
    return KEY_UNPRESS;
}

int main()
{
    static u8 key = 1;

    while (1)
    {
        key = key_scan(0);
        if (key == KEY1_PRESS)
        {
            LED1 = !LED1;
        }
    }
    return 0;
}
