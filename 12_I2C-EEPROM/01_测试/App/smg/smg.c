#include "smg.h"
//共阴极数码管显示 0-F 的断码数据
u8 gsmg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
					0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
/**
 * @brief
 *
 * @param dat 要显示的数据
 * @param pos 从左开始第几个位置开始显示，范围1-8
 */
void smg_display(u8 dat[], u8 pos)
{
	u8 i = 0;
	u8 pos_temp = pos - 1;

	for (i = pos_temp; i < 8; i++)
	{
		switch (i)
		{
		case 0:
			LSC = 1;
			LSB = 1;
			LSA = 1;
			break;
		case 1:
			LSC = 1;
			LSB = 1;
			LSA = 0;
			break;
		case 2:
			LSC = 1;
			LSB = 0;
			LSA = 1;
			break;
		case 3:
			LSC = 1;
			LSB = 0;
			LSA = 0;
			break;
		case 4:
			LSC = 0;
			LSB = 1;
			LSA = 1;
			break;
		case 5:
			LSC = 0;
			LSB = 1;
			LSA = 0;
			break;
		case 6:
			LSC = 0;
			LSB = 0;
			LSA = 1;
			break;
		case 7:
			LSC = 0;
			LSB = 0;
			LSA = 0;
			break;
		}
		SMG_A_DP_PORT = gsmg_code[dat[i - pos_temp]];
		delay_10us(100);
		SMG_A_DP_PORT = 0x00;
	}
}
