#include "public.h"
#include "ds18b20.h"
#include "smg.h"

void main()
{
	u8 i = 0;
	int temp_value;
	u8 temp_buf[5];
	u8 gsmg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

	ds18b20_init();

	while (1)
	{
		i++;
		//间隔一段时间读取温度值，间隔时间要大于温度传感器转换温度时间
		if (i % 50 == 0)
		{
			//保留温度值小数后一位
			temp_value = ds18b20_read_temperture() * 10;
		}
		if (temp_value < 0)
		{
			temp_value = -temp_value;
			temp_buf[0] = 0x40;
		}
		else
		{
			temp_buf[0] = 0x00;
		}
		temp_buf[1] = gsmg_code[temp_value / 1000];					  //百位
		temp_buf[2] = gsmg_code[temp_value % 1000 / 100];			  //十位
		temp_buf[3] = gsmg_code[temp_value % 1000 % 100 / 10] | 0x80; //个位+小数点
		temp_buf[4] = gsmg_code[temp_value % 1000 % 100 % 10];		  //小数点后一位
		smg_display(temp_buf, 4);
	}
}
