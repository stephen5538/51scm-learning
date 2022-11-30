#include <ds18b20.h>
#include "intrins.h"
/**
 * @brief   复位 DS18B20
 * 主机输出低电平，保持低电平
 * 时间至少 480us（该时间的时间范围可以从 480 到 960 微妙），以产生复位脉
 * 冲。接着主机释放总线，外部的上拉电阻将单总线拉高，延时 15～60 us，并进
 * 入接收模式
 *
 */
void ds18b20_reset()
{
    DS18B20_PORT = 0; //拉低DQ
    delay_10us(75);
    DS18B20_PORT = 1;
    delay_10us(2);
}

/**
 * @brief 检测 DS18B20 是否存在
 *
 * @return u8 1:未检测到 DS18B20 的存在，0:存在
 */
u8 ds18b20_check()
{
    //超时时间次数
    u8 time_temp = 0;
    //等待 DQ 为低电平
    while (DS18B20_PORT && time_temp < 20)
    {
        time_temp++;
        delay_10us(1);
    }
    if (time_temp >= 20)
    {
        return 1;
    }
    time_temp = 0;
    while (!DS18B20_PORT && time_temp < 20)
    {
        time_temp++;
        delay_10us(1);
    }
    if (time_temp >= 20)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief 从ds18b20 读取一位 bit
 *
 *  主机输出低电平延时 2us，然后主机转入输入模式延
 *   时  2us，然后读取单总线当前的电平，然后延时 50us
 * @return u8
 */
u8 ds18b20_read_bit()
{
    u8 dat = 0;
    //拉低总线
    DS18B20_PORT = 0;
    _nop_();          // 1us
    _nop_();          // 1us
    DS18B20_PORT = 1; //释放总线
    _nop_();
    _nop_(); //该段时间不能过长，必须在15us内读取数据
    //读取从机发送的数据
    if (DS18B20_PORT)
    {
        dat = 1;
    }
    else
    {
        dat = 0;
    }
    delay_10us(5);
    return dat;
}
/**
 * @brief 读取一个字节
 *
 * @return u8
 */
u8 ds18b20_read_byte()
{
    u8 i = 0;
    u8 dat = 0;
    u8 temp = 0;
    //循环8次，每次读取一位，且先读低位再读高位
    for (i = 0; i < 8; i++)
    {
        temp = ds18b20_read_bit();
        //右移一位 将最高放入次高位
        dat = dat >> 1;
        dat = dat | (temp << 7);
    }
    return dat;
}

/**
 * @brief 写一个字节到DS18B20
 *
 * @param dat 一个字节
 */
void ds18b20_write_byte(u8 dat)
{
    u8 i = 0;
    u8 temp = 0;

    for (i = 0; i < 8; i++)
    {
        temp = dat & 0x01;
        dat=dat >> 1; //高位移动低位
        if (temp)
        {
            DS18B20_PORT = 0;
            _nop_();
            _nop_();
            DS18B20_PORT = 1;
            delay_10us(6);
        }
        else
        {
            DS18B20_PORT = 0;
            delay_10us(6);
            DS18B20_PORT = 1;
            _nop_();
            _nop_();
        }
    }
}

/**
 * @brief 初始化 DS18B20 的 IO 口 DQ 同时检测 DS 的存在
 *
 * @return u8 1:不存在，0:存在
 */
u8 ds18b20_init(void)
{
    ds18b20_reset();
    return ds18b20_check();
}

/**
 * @brief 开始温度转换
 *
 */
void ds18b20_start()
{
    ds18b20_reset();          //复位
    ds18b20_check();          //检查ds18b20 是否存在
    ds18b20_write_byte(0xcc); // SKIP ROM
    ds18b20_write_byte(0x44); //转换命令
}

/**
 * @brief 从 ds18b20 得到温度值
 *
 * @return float 温度数据
 */
float ds18b20_read_temperture()
{
    float temp;
    //高位温度
    u8 dath = 0;
    //地位温度
    u8 datl = 0;
    u16 value = 0;

    ds18b20_start();
    ds18b20_reset();          //复位
    ds18b20_check();          //检查ds18b20 是否存在
    ds18b20_write_byte(0xcc); // SKIP ROM
    ds18b20_write_byte(0xbe); //读存储器

    datl = ds18b20_read_byte(); //低字节
    dath = ds18b20_read_byte(); //高字节

    value = (dath << 8) + datl; //合并为16位数据

    if ((value & 0xf800) == 0xf800) //判断符号位，负温度
    {
        value = (~value) + 1;     //数据取反再加1
        temp = value * (-0.0625); //乘以精度
    }
    else //正温度
    {
        temp = value * 0.0625;
    }
    return temp;
}