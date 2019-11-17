#include <iostream>
#include <fstream>
#include "Hash.h"



int utils::Bit_Int(int n)
{
	int bit = 0;
	if (n == 0)
		return 1;
	while (n)
	{
		bit++;
		n /= 10;
	}
	return bit;
}

int utils::AsciiSum(string w)
{

	int WordSum = 0;
	for (int i = 0; i < w.length(); i++)
		WordSum += w[i];
	return WordSum;
}