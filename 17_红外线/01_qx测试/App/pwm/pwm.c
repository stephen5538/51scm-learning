#include "xpt2046.h"
#include "pwm.h"

//全局变量定义
u8 gtim_h = 0;     //保存定时器初值高 8 位
u8 gtim_l = 0;     //保存定时器初值低 8 位
u8 gduty = 0;      //保存 PWM 占空比
u8 gtim_scale = 0; //保存 PWM 周期=定时器初值*tim_scale

void pwm_init(u8 tim_h, u8 tim_l, u16 tim_scale, u8 duty)
{
    gtim_h = tim_h; //将传入的初值保存在全局变量中，方便中断函数继续调用
    gtim_l = tim_l;
    gduty = duty;
    gtim_scale = tim_scale;

    TMOD |= 0X01; //选择为定时器 0 模式，工作方式 1
    TH0 = gtim_h; //定时初值设置
    TL0 = gtim_l;
    ET0 = 1; //打开定时器 0 中断允许
    EA = 1;  //打开总中断
    TR0 = 1; //打开定时器
}

void pwm_set_duty_cycle(u8 duty)
{
    gduty = duty;
}

void pwm(void) interrupt 1 //定时器 0 中断函数
{
    static u16 time = 0;
    TH0 = gtim_h; //定时初值设置
    TL0 = gtim_l;
    time++;
    if (time >= gtim_scale) // PWM 周期=定时器初值*gtim_scale，重新开始计数
        time = 0;
    if (time <= gduty) //占空比
        PWM = 1;
    else
        PWM = 0;
}