#include "ARUtils.h"

using namespace AutoRobo;

void uint_to_uchar(unsigned long src, unsigned char* dst)
{
	unsigned long srccpy = src;
	unsigned long helper;
	unsigned int pos = 0;
	unsigned long div = 10;
	while(src * 10 >= div)
	{
		helper = srccpy - (srccpy / div) * div;
		dst[pos] = (unsigned char)((helper * 10) / div) + '0';
		srccpy = srccpy - helper;
		pos++;
		div *= 10;
	}
	unsigned char i = 0;
	while(i < pos / 2)
	{
		helper = dst[pos - i - 1];
		dst[pos - i - 1] = dst[i];
		dst[i] = helper;
		i++;
	}
}

void debugBreakOnFalse(bool condition)
{
	if(false == condition)
	{
		volatile int aaa; // Should not be optimized out
		aaa = 3;
		int b = aaa;
	}
}
