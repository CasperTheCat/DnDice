#include "dice_functions.h"
#include <algorithm>

typedef uint32_t (*FNCTN_PTR)();

uint32_t roll(FNCTN_PTR dice)
{
    return dice();
}

uint32_t rollMulti(uint32_t rounds, FNCTN_PTR dice)
{
	uint32_t ret = 0;
	for (uint32_t i = 0; i < rounds; ++i)
		ret += dice();
	return ret;
}

uint32_t rollAdvantage(FNCTN_PTR dice)
{
	return std::max(dice(), dice());
}

uint32_t rollDisadvantage(FNCTN_PTR dice)
{
	return std::min(dice(), dice());
}

