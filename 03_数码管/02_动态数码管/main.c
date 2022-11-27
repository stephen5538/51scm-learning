#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
//数码管段码口
#define SMG_A_DP_PORT P0
//数码管位选信号控制脚
sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

//共阴极数码管显示 0~F 的段码数据
u8 gsmg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

void delay_10us(u16 ten_us)
{
    while (ten_us--)
        ;
}
void smg_display()
{
    u8 i = 0;
    for (i = 0; i < 8; i++)
    {
        switch (i) //位选
        {
        case 0:
            LSC = 1;
            LSB = 1;
            LSA = 1;
            break;
        case 1:
            LSC = 1;
            LSB = 1;
            LSA = 0;
            break;
        case 2:
            LSC = 1;
            LSB = 0;
            LSA = 1;
            break;
        case 3:
            LSC = 1;
            LSB = 0;
            LSA = 0;
            break;
        case 4:
            LSC = 0;
            LSB = 1;
            LSA = 1;
            break;
        case 5:
            LSC = 0;
            LSB = 1;
            LSA = 0;
            break;
        case 6:
            LSC = 0;
            LSB = 0;
            LSA = 1;
            break;
        case 7:
            LSC = 0;
            LSB = 0;
            LSA = 0;
            break;
        default:
            break;
        }
        SMG_A_DP_PORT = gsmg_code[i]; //传送段选数据
        delay_10us(100);              //延时一段时间，等待显示稳定
        SMG_A_DP_PORT = 0x00;         //消隐
    }
}

int main()
{

    while (1)
    {
        smg_display();
    }
    return 0;
}
