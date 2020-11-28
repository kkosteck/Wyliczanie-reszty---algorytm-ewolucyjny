#pragma once
#include <vector>
#include <random>
class Individual
{
private:
	std::vector<int> chromosome;
	int fitness;
	int calculateFitness();
	int randomNumber(int a, int b);
public:
	Individual(std::vector<int> chromosome);
	int getFitness();
	std::vector<int> getChromosome();
	void mutate(int genes[]);
};