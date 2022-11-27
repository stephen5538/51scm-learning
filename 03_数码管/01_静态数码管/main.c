#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

#define SMG_A_DP_PORT P0
//共阴极数码管显示 0~F 的段码数据
u8 gsmg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

int main()
{
    SMG_A_DP_PORT = gsmg_code[0];
    while (1)
    {
    }
    return 0;
}
