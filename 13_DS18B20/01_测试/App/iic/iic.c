#include "iic.h"

/**
 * @brief 产生I2C起始信号
 *
 */
void iic_start(void)
{
	IIC_SDA = 1;
	delay_10us(1);
	IIC_SCL = 1;
	delay_10us(1);
	IIC_SDA = 0; //当 SCL 为高电平时，SDA 由高变为低
	delay_10us(1);
	IIC_SCL = 0; //钳住 I2C 总线，准备发送或接收数据
	delay_10us(1);
}
/**
 * @brief 产生I2C停止信号
 *
 */
void iic_stop(void)
{
	IIC_SDA = 0;
	delay_10us(1);
	IIC_SCL = 1;
	delay_10us(1);
	IIC_SDA = 1; //当 SCL 为高电平时，SDA 由低变为高
	delay_10us(1);
}
/**
 * @brief 产生I2C应答
 *
 */
void iic_ack(void)
{
	IIC_SCL = 0; // SCL为低电平 才可以修改SDA的数据
	IIC_SDA = 0; // SDA 为低电平
	delay_10us(1);
	IIC_SCL = 1; //设置为高电平 让别人读
	delay_10us(1);
	IIC_SCL = 0; //设置为低电平 让别人可以更改
}
/**
 * @brief 产生I2C非应答
 *
 */
void iic_nack(void)
{
	IIC_SCL = 0; // SCL为低电平 才可以修改SDA的数据
	IIC_SDA = 1; // SDA 为高电平
	delay_10us(1);
	IIC_SCL = 1; //设置为高电平 让别人读
	delay_10us(1);
	IIC_SCL = 0; //设置为低电平 让别人可以更改
}
/**
 * @brief 等待应答信号到来
 *
 * @return u8
 * 			1，接收应答失败
 *			0，接收应答成功
 */
u8 iic_wait_ack(void)
{
	u8 time_temp = 0;

	IIC_SCL = 1;
	delay_10us(1);
	while (IIC_SDA) //等待 SDA 为低电平
	{
		time_temp++;
		if (time_temp > 100) //超时则强制结束 IIC 通信
		{
			iic_stop();
			return 1;
		}
	}
	IIC_SCL = 0;
	return 0;
}
/**
 * @brief I2C 发送一个字节
 *
 * @param dat 字节
 */
void iic_write_byte(u8 dat)
{
	u8 i = 0;
	// SCL为低电平 才可以修改SDA的数据
	IIC_SCL = 0;
	for (i = 0; i < 8; i++)
	{
		if ((dat & 0x80) > 0)
			IIC_SDA = 1;
		else
			IIC_SDA = 0;
		dat <<= 1;
		delay_10us(1);
		IIC_SCL = 1; //设置为高电平 让别人读
		delay_10us(1);
		IIC_SCL = 0; //设置为低电平 让别人可以更改
		delay_10us(1);
	}
}
/**
 * @brief I2C 读取一个字节
 *
 * @param ack ack=1 时，发送 ACK，ack=0，发送 nACK
 * @return 应答或非应答
 */
u8 iic_read_byte(u8 ack)
{
	u8 i = 0, receive = 0;

	for (i = 0; i < 8; i++)
	{
		//设置为低电平 让别人可以更改
		IIC_SCL = 0;
		delay_10us(1);
		//设置为高电平 让自己读
		IIC_SCL = 1;
		receive <<= 1;
		if (IIC_SDA)
		{
			receive++;
		}
		delay_10us(1);
	}
	if (!ack)
		iic_nack();
	else
		iic_ack();

	return receive;
}
