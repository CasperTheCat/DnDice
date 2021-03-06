#ifndef __VERMANIC_DICE__
#define __VERMANIC_DICE__

#include <random>
#include <chrono>

namespace Dice
{

	std::chrono::high_resolution_clock hrc;
	std::mt19937_64 gen(hrc.now().time_since_epoch().count());
	std::uniform_real_distribution<double> distrib(0, 2);
    auto d100 = [] {return static_cast<uint32_t>(std::floor((distrib(gen) * 50) + 1.f)); };
	auto d20 = [] {return static_cast<uint32_t>(std::floor((distrib(gen) * 10) + 1.f)); };
	auto d12 = [] {return static_cast<uint32_t>(std::floor((distrib(gen) * 6) + 1.f)); };
	auto d10 = [] {return static_cast<uint32_t>(std::floor((distrib(gen) * 5) + 1.f)); };
	auto d8 = [] {return static_cast<uint32_t>(std::floor((distrib(gen) * 4) + 1.f)); };
	auto d6 = [] {return static_cast<uint32_t>(std::floor((distrib(gen) * 3) + 1.f)); };
	auto d4 = [] {return static_cast<uint32_t>(std::floor((distrib(gen) * 2) + 1.f)); };
	auto d3 = [] {return static_cast<uint32_t>(std::floor((distrib(gen) * 1.5) + 1.f)); };
    auto d2 = [] {return static_cast<uint32_t>(std::floor((distrib(gen)) + 1.f)); };

	auto ad20 = [] { return std::uniform_int_distribution<uint32_t>(1,20)(gen); };

	auto nd20 = [] {return static_cast<uint32_t>(std::floor((distrib(gen) * 10) + 1.f)); };

	auto td20 = [] {return static_cast<uint32_t>(std::floor( (distrib(gen) * 10) + 1.f) * 100.f); };
}

#endif
