#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

//直流电机控制管脚
sbit DC_Motor = P1 ^ 0;
//直流电机运行时间为5000ms
#define DC_MOTOR_RUN_TIME 5000
void delay_ms(u16 ms)
{
    u16 i, j;
    for (i = ms; i > 0; i--)
        for (j = 110; j > 0; j--)
            ;
}

int main()
{
    //开启电机
    DC_Motor = 1;
    delay_ms(DC_MOTOR_RUN_TIME);
    DC_Motor = 0;
    while (1)
    {
        /* code */
    }

    return 0;
}
