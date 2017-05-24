#include <iostream>
#include <chrono>
#include <string.h>
//#include <opencv2/video.hpp>
//#include <opencv2/opencv.hpp>
//#include <boost/filesystem.hpp>
//#include <boost/timer.hpp>
#include "../dice.h"
#include "../dice_functions.h"
#define ITER 10000000

int main(int argc, char **argv)
{

	uint32_t min = 0;
	uint32_t max = 0;
	uint32_t truth = 0;

	auto timeS = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	std::cout << "Rolling 1M dice with first method" << std::endl;

	for (int i = 0; i < ITER; ++i)
	{
		uint32_t comp = truth;
		truth += roll(Dice::d20);
		if (truth - comp == 0) return 1;
		if (truth - comp > 20) return 1;
		++min;
		max += 20;
	}
	
	auto timeE = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	std::cout << "Min: " << min << " Actual: " << truth << " Max: " << max << std::endl;
	std::cout << (timeE - timeS) / 1000000000.f << std::endl;

	/////
	//
	/////

	truth = max = min = 0;

	timeS = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	std::cout << "Rolling 1M dice with second method" << std::endl;

	for (int i = 0; i < ITER; ++i)
	{
		uint32_t comp = truth;
		truth += roll(Dice::ad20);
		if (truth - comp == 0) return 1;
		if (truth - comp > 20) return 1;
		++min;
		max += 20;
	}

	timeE = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	std::cout << "Min: " << min << " Actual: " << truth << " Max: " << max << std::endl;
	std::cout << (timeE - timeS) / 1000000000.f << std::endl;

	/////
	//
	/////

	truth = max = min = 0;

	timeS = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	std::cout << "Rolling 1M dice with second method" << std::endl;

	for (int i = 0; i < ITER; ++i)
	{
		uint32_t comp = truth;
		truth += roll(Dice::nd20);
		if (truth - comp == 0) return 1;
		if (truth - comp > 20) return 1;
		++min;
		max += 20;
	}

	timeE = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	std::cout << "Min: " << min << " Actual: " << truth << " Max: " << max << std::endl;
	std::cout << (timeE - timeS) / 1000000000.f << std::endl;


	return 0;
}
