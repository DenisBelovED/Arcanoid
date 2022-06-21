#pragma once
#include<random>

class RandomGenerator
{
	std::random_device rd;
	float lower_bound, upper_bound;
public:
	RandomGenerator(float lower_bound, float upper_bound) 
	{
		RandomGenerator::lower_bound = lower_bound;
		RandomGenerator::upper_bound = upper_bound;
	}
	float operator() ()
	{
		return std::uniform_real_distribution<float>(lower_bound, upper_bound)(rd);
	}
};
