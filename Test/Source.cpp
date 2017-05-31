#include <iostream>
#include <chrono>
#include <algorithm>
#include <string.h>
//#include <opencv2/video.hpp>
//#include <opencv2/opencv.hpp>
//#include <boost/filesystem.hpp>
//#include <boost/timer.hpp>
#include <omp.h>
#include "../dice.h"
#include "../dice_functions.h"
#include <functional>
#include <unordered_map>
#include <map>
#define ITER 10000000


int test_func()
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


int main(int argc, char **argv)
{
	int mT = omp_get_max_threads();
	omp_set_num_threads(mT);


	//int x = test_func();

	// Some informative tests
	//
	std::map<uint32_t, uint32_t> maps;
	uint32_t res = 0;
	uint32_t mins = UINT32_MAX; // Dice should never sum to this!
	uint32_t maxs = 0;
//#pragma omp parallel for schedule(static) reduction(+:res), reduction(+:maxs), reduction(+:mins)
	for (int i = 0; i < ITER; ++i)
	{
		uint32_t local = 0;
		local += rollMulti(3, Dice::td6);
		//local -= roll(Dice::d3);

		// Lowest Drop

		if (local < mins) mins = local;
		if (local > maxs) maxs = local;
		res += local;
		maps.emplace(local, maps[local]++);
	}

	std::cout << "Average result = " << res / float(ITER) 
		<< "\nMin Result = " << mins
		<< "\nMax Result = " << maxs
	<< std::endl;


	// Percentile THolds
	float uThreshold5th = ITER * 0.05;
	float uThreshold25th = ITER * 0.25;
	float uThreshold50th = ITER * 0.50;
	float uThreshold75th = ITER * 0.75;
	float uThreshold95th = ITER * 0.95;

	uint32_t uPercentileSum = 0;
	// Dealing with map!
	for (auto value_ : maps)
	{
		//std::cout << value_.first << ":" << value_.second << std::endl;
		uint32_t uTemp = value_.second;
		if(uPercentileSum + uTemp >= uThreshold5th && uPercentileSum < uThreshold5th) std::cout << "5th Percentile: " << value_.first << std::endl;
		if(uPercentileSum + uTemp >= uThreshold25th && uPercentileSum < uThreshold25th) std::cout << "25th Percentile: " << value_.first << std::endl;
		if(uPercentileSum + uTemp >= uThreshold50th && uPercentileSum < uThreshold50th) std::cout << "50th Percentile: " << value_.first << std::endl;
		if(uPercentileSum + uTemp >= uThreshold75th && uPercentileSum < uThreshold75th) std::cout << "75th Percentile: " << value_.first << std::endl;
		if(uPercentileSum + uTemp >= uThreshold95th && uPercentileSum < uThreshold95th) std::cout << "95th Percentile: " << value_.first << std::endl;
		uPercentileSum += uTemp;
	}


	return 0;
}