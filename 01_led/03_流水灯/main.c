#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

#define LED_PORT P2
void delay_10us(u16 ten_us)
{
    while (ten_us--)
        ;
}

int main(int argc, char const *argv[])
{
    u8 i = 0;
    while (1)
    {
        for (i = 0; i < 8; i++)
        {
						//0000 0001
						//0000 0010
            LED_PORT = ~(0x01 << i);
            delay_10us(50000);
        }
    }

    return 0;
}
