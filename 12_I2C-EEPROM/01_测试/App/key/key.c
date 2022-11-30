#include "key.h"
/**
 * @brief 检测独立按键是否按下，按下则返回对应键值
 *
 * @param mode
 * 			mode=0：单次扫描按键
 *			mode=1：连续扫描按键
 * @return u8
 * 			KEY1_PRESS：K1 按下
 *			KEY2_PRESS：K2 按下
 *			KEY3_PRESS：K3 按下
 *			KEY4_PRESS：K4 按下
 *			KEY_UNPRESS：未有按键按下
 */
u8 key_scan(u8 mode)
{
	//静态全局变量
	static u8 key = 1;
	//如果为1 将key 重置为1 这样永远会走if
	//如果为0 第一次走if 之后要等用户松手 等所有按键变成高电平 才会走else if 将key置为1
	if (mode)
	{
		key = 1;
	}

	if (key == 1 && (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0))
	{
		delay_10us(1000);
		//置0
		key = 0;
		if (KEY1 == 0)
			return KEY1_PRESS;
		else if (KEY2 == 0)
			return KEY2_PRESS;
		else if (KEY3 == 0)
			return KEY3_PRESS;
		else if (KEY4 == 0)
			return KEY4_PRESS;
	}
	else if (KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1)
	{
		//置1
		key = 1;
	}
	return KEY_UNPRESS;
}