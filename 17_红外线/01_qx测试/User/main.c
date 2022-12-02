#include "public.h"

typedef unsigned char uchar;
typedef unsigned int uint;

//储存检测红外高低电平持续时间
uchar IRtime;
//储存解码后的四个字节数据
uchar IRcord[4];
//包含起始码在内的33位数据
uchar IRdata[33];
//解码后4个字节数据接收完成标记位
bit IRpro_ok;
// 33位数据接收完成标志
bit IRok;

//初始化定时器0 外部中断0 串口
void init()
{
    //设置定时器0工作模式2 8位自动重装
    TMOD |= 0x02;
    //初始化定时器0 寄存器 定时器0溢出一次时间位256个机器周期
    TL0 = TH0 = 0;
    //总中断打开
    EA = 1;
    //定时器0中断打开
    ET0 = 1;
    //启动定时器0
    TR0 = 1;
    //设置外部中断0 -> 跳变沿触发方式
    IT0 = 1;
    //打开 外部中断0
    EX0 = 1;

    //定时器1 工作模式2 8位自动重装
    TMOD |= 0x20;
    //比特率9600
    TL1 = TH1 = 0xfd;
    //启动定时器1
    TR1 = 1;
    //串口工作模式1  10位异步收发
    SM1 = 1;
    //打开串口接收总中断
    ES = 1;
}

//定时器0 中断
//每中断一次需要 (256*1.085us=277.76us)
void timer0() interrupt 1
{
    IRtime++; // 277.76us
}

//外部中断
void int0() interrupt 0
{
    //静态变量用于存入33次数据计数
    static uchar i;
    //开始储存脉宽标记位
    static bit startflag;
    if (startflag)
    {
        //判断引导码 如果是引导码则从起始码开始存
        if (IRtime < 53 && IRtime >= 32)
        {
            i = 0;
        }
        //以T0溢出的次数来计算脉宽把这个时间
        //存放在数组中
        IRdata[i] = IRtime;
        //计数清零
        IRtime = 0;
        //计数脉宽存入次数自加
        i++;
        //表示已经存入了33次脉宽
        if (i == 33)
        {
            IRok = 1; //脉宽检查完成
            i = 0;    //把脉宽计数清零准备下次脉宽
            startflag = 0;
        }
    }
    else
    {
        //定时计数器清零
        IRtime = 0;
        //开始处理标志位置1
        startflag = 1;
    }
}
//把提取的33次脉宽进行解码
void IRcordpro()
{
    uchar i; //处理四个字节
    uchar j; // 1个字节的8位数据
    uchar k; //处理33次脉宽
    k = 1;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; i++)
        {
            //数据从高到低接收数据
            //脉宽时间1125us 代表位数字1
            if (IRdata[k] > 5)
            {
                //最高位赋值1 其它位不变
                IRcord[i] |= 0x80;
            }
            //避免最后一次把数据移出去
            if (j < 7)
            {
                //数据右移
                IRcord[i] >>= 1;
            }
            k++;
        }
    }
    //解码完成
    IRpro_ok = 1;
}

void main()
{
    //计数串口发送字节数
    uchar i;
    init();
    while (1)
    {
        //判断33次脉宽是否提取完成
        if (IRok)
        {
            //解码4个字节数据
            IRcordpro();
            //清零标记 等待下一次脉宽检查
            IRok = 0;
            //判断解码完成
            if (IRpro_ok)
            {
                //清零标记
                IRpro_ok = 0;
                //通过串口把数据发送出去
                for (i = 0; i < 4; i++)
                {
                    SBUF = IRcord[i];
                    while (!TI)
                    {
                        TI = 0;
                    }
                }
            }
        }
    }
}
