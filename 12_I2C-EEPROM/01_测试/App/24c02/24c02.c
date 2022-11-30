#include "24c02.h"
#include "iic.h"
/**
 * @brief 在 AT24CXX 指定地址写入一个数据
 *
 * @param addr 写入数据的目的地址
 * @param dat :要写入的数据
 */
void at24c02_write_one_byte(u8 addr, u8 dat)
{
	iic_start();
	iic_write_byte(0XA0);
	iic_wait_ack();
	iic_write_byte(addr);
	iic_wait_ack();
	iic_write_byte(dat);
	iic_wait_ack();
	iic_stop();
	delay_ms(10);
}
/**
 * @brief 在 AT24CXX 指定地址读出一个数据
 *
 * @param  addr:开始读数的地址
 * @return u8 读到的数据
 */
u8 at24c02_read_one_byte(u8 addr)
{
	u8 temp = 0;
	iic_start();
	iic_write_byte(0XA0);
	iic_wait_ack();
	iic_write_byte(addr);
	iic_wait_ack();
	iic_start();
	iic_write_byte(0XA1);
	iic_wait_ack();
	temp = iic_read_byte(0);
	iic_stop();
	return temp;
}
