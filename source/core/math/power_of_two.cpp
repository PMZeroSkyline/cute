#include "power_of_two.h"

#include <cmath>

bool is_pow_of_two(int n)
{
	return (n > 0) && ((n & (n - 1)) == 0);
}
int ceil_pow_of_two(int n)
{
	if (n <= 0)
	{
		return 1;
	}
	return (int)std::pow(2, ceil(log2(n)));
}
int floor_pow_of_two(int n)
{
	if (n <= 0)
	{
		return 1;
	}
	return (int)std::pow(2, floor(log2(n)));
}
int round_pow_of_two(int n)
{
	if (n <= 0)
	{
		return 1;
	}
	int lowerPower = (int)std::pow(2, floor(log2(n)));
	int upperPower = (int)std::pow(2, ceil(log2(n)));
	return (n - lowerPower <= upperPower - n) ? lowerPower : upperPower;
}
