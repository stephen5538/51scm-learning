#include "xpt2046.h"
#include "intrin.h"
/**
 * @brief xpt2046写数据
 *
 * @param dat
 */
void xpt2046_write_data(u8 dat)
{
    u8 i;
    u8 temp;
    CLK = 0;
    _nop_();
    for (i = 0; i < 8; i++)
    {
        // 1000 0000
        //先传高位再传低位
        temp = dat & 0x80;
        if (temp)
        {
            DIN = 1;
        }
        else
        {
            DIN = 0;
        }
        // CLK 由低到高产生一个上升沿，
        //从而写入数据
        CLK = 1;
        _nop_();
        CLK = 0;
        _nop_();
        dat = dat << 1;
    }
}
/**
 * @brief 读数据
 *
 * @return u8 XPT2046 返回 12 位数据
 */
u16 xpt2046_read_data()
{
    u8 i;
    u16 dat = 0;
    CLK = 0;
    _nop_();
    for (i = 0; i < 12; i++)
    {
        dat = dat << 1;
        CLK = 1;
        _nop_();
        CLK = 0;
        _nop_();
        //先读取高位，再读取低位。
        dat = dat | DOUT;
    }
    return dat;
}

/**
 * @brief xpt2046 读AD数据
 *
 * @param cmd 指令
 * @return u16 AD值
 */
u16 xpt2046_read_adc_value(u8 cmd)
{
    u8 i;
    u16 adc_value = 0;
    CLK = 0;                 //先拉低时钟
    CS = 0;                  //使能 XPT2046
    xpt2046_write_data(cmd); //发送命令字
    for (i = 6; i > 0; i--)
        ; //延时等待转换结果
    CLK = 0;
    _nop_();
    CLK = 1; //发送一个时钟，清除 BUSY
    _nop_();
    adc_value = xpt2046_read_data();
    CS = 1; //关闭 XPT2046
    return adc_value;
}