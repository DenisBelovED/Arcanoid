#pragma once
#include<random>

template<typename T>
class RandomGenerator
{
	std::random_device rd;
	T lower_bound, upper_bound;
public:
	RandomGenerator<T>(T lower_bound, T upper_bound) 
	{
		RandomGenerator::lower_bound = lower_bound;
		RandomGenerator::upper_bound = upper_bound;
	}
	int get_int()
	{
		return std::uniform_int_distribution<T>(lower_bound, upper_bound)(rd);
	}
	float get_float()
	{
		return std::uniform_real_distribution<T>(lower_bound, upper_bound)(rd);
	}
};
