#ifndef __VERMANIC_DICE__
#define __VERMANIC_DICE__

#include <random>
#include <chrono>

namespace Dice
{

	std::chrono::high_resolution_clock hrc;
	std::mt19937_64 gen(hrc.now().time_since_epoch().count());
	std::uniform_real_distribution<double> distrib(0, 2);
	auto d20 = [] {return static_cast<uint32_t>(std::ceil(distrib(gen) * 10)); };
	auto d12 = [] {return static_cast<uint32_t>(std::ceil(distrib(gen) * 6)); };
	auto d10 = [] {return static_cast<uint32_t>(std::ceil(distrib(gen) * 5)); };
	auto d8 = [] {return static_cast<uint32_t>(std::ceil(distrib(gen) * 4)); };
	auto d6 = [] {return static_cast<uint32_t>(std::ceil(distrib(gen) * 3)); };
	auto d4 = [] {return static_cast<uint32_t>(std::ceil(distrib(gen) * 2)); };
	auto d3 = [] {return static_cast<uint32_t>(std::ceil(distrib(gen) * 1.5)); };

	auto ad20 = [] { return std::uniform_int_distribution<uint32_t>(1,20)(gen); };

	auto nd20 = [] {return static_cast<uint32_t>(std::floor((distrib(gen) * 10) + 1.f)); };
}

#endif
