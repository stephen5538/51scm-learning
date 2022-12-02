#include "public.h"
#include "smg.h"
#include "xpt2046.h"

void main()
{
    u16 adc_value = 0;
    float adc_vol; // ADC 电压值
    u8 adc_buf[3];
    while (1)
    {
        adc_value = xpt2046_read_adc_value(0x94); //测量电位器
        adc_vol = 5.0 * adc_value / 4096;         //将读取的 AD 值转换为电压
        adc_value = adc_vol * 10;                 //放大 10 倍，即保留小数点后一位
        adc_buf[0] = gsmg_code[adc_value / 10] | 0x80;
        adc_buf[1] = gsmg_code[adc_value % 10];
        adc_buf[2] = 0x3e; //显示单位 V
        smg_display(adc_buf, 6);
    }
}
