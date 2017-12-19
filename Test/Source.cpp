#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#endif


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
#include <mutex>
#include <unordered_map>
#include <map>
#include <thread>
#include <string>


#define ITER 10000000
#define ITER_STEPPING ITER/10

volatile bool globalStop = false;
std::mutex mTex;


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


void tFunc()
{
	// Vars
	std::map<uint64_t, uint64_t> maps;
	uint64_t res = 0;
	uint64_t mins = UINT32_MAX; // Dice should never sum to this!
	uint64_t maxs = 0;

	// Lifting
	for (int i = 0; i < ITER; ++i)
	{
		if (globalStop) return;

		uint64_t local = 0;
		local += rollAdvantage(Dice::td20);

		if (local < mins) mins = local;
		if (local > maxs) maxs = local;
		res += local;
		maps.emplace(local, maps[local]++);
	}




	// Percentile THolds
	float uThreshold5th = ITER * 0.05;
	float uThreshold25th = ITER * 0.25;
	float uThreshold50th = ITER * 0.50;
	float uThreshold75th = ITER * 0.75;
	float uThreshold95th = ITER * 0.95;


	uint64_t uPercentileSum = 0;
	// Dealing with map!

	{
		std::lock_guard<std::mutex> lck(mTex);

			std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;

		std::cout << "Average result = " << res / float(ITER) * 0.01
			<< "\nMin Result = " << std::floor(mins * 0.01)
			<< "\nMax Result = " << std::floor(maxs * 0.01)
			<< std::endl;


		for (auto value_ : maps)
		{
			//std::cout << value_.first << ":" << value_.second << std::endl;
			uint64_t uTemp = value_.second;
			if (uPercentileSum + uTemp >= uThreshold5th && uPercentileSum < uThreshold5th) std::cout << "5th Percentile: " << value_.first * 0.01 << std::endl;
			if (uPercentileSum + uTemp >= uThreshold25th && uPercentileSum < uThreshold25th) std::cout << "25th Percentile: " << value_.first * 0.01 << std::endl;
			if (uPercentileSum + uTemp >= uThreshold50th && uPercentileSum < uThreshold50th) std::cout << "50th Percentile: " << value_.first * 0.01 << std::endl;
			if (uPercentileSum + uTemp >= uThreshold75th && uPercentileSum < uThreshold75th) std::cout << "75th Percentile: " << value_.first * 0.01 << std::endl;
			if (uPercentileSum + uTemp >= uThreshold95th && uPercentileSum < uThreshold95th) std::cout << "95th Percentile: " << value_.first * 0.01 << std::endl;
			uPercentileSum += uTemp;
		}
	}
}

int main(int argc, char **argv)
{

	// Stack alloc
	std::thread *tArr[12];
	
	for(int i = 0; i < 12; ++i)
	{
		tArr[i] = new std::thread(tFunc); // Launch the threads!
	}

	// Setup loop
	std::string command;
	char* part;

	while(true)
	{
		getline(std::cin, command);
		part = strtok(&command[0], " ");
		if(part && strcmp(part,"exit") == 0)
		{
			part = strtok(nullptr, " ");
			if(!part || strcmp(part,"-f") == 0)
			{
				globalStop = true;
			}
			// break
			break;
		}
	} 

	for (int i = 0; i < 12; ++i)
	{
		tArr[i]->join();
	}


	return 0;
}