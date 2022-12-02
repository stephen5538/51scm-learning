#include "public.h"
#include "smg.h"
#include "pwm.h"

void main()
{
    u8 dir = 0; //默认为 0
    u8 duty = 0;
    pwm_init(0XFF, 0XF6, 100, 0); //定时时间为 0.01ms，PWM 周期是100 * 0.01ms = 1ms，占空比为 0 %

    while (1)
    {
        if (dir == 0) //当 dir 为递增方向
        {
            duty++; //占空比递增
            if (duty == 70)
                dir = 1; //当到达一定值切换方向，占空比最大能到 100，但到
            达 70 左右再递增，
            //肉眼也分辨不出亮度变化
        }
        else
        {
            duty--;
            if (duty == 0)
                dir = 0; //当到达一定值切换方向
        }
        pwm_set_duty_cycle(duty); //设置占空比
        delay_ms(1);              //短暂延时，让呼吸灯有一个流畅的效果
    }
}
