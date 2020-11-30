#pragma once
#include <deque>
#include <vector>
#include<numeric>
#include <cstdlib>
#include <iostream>

class Individual
{
private:
	std::deque<int> chromosome;
	int difference, quantity;
	void calculateFitness(int C);
public:
	Individual(int C, std::vector<int>);
	Individual();
	int getDifference();
	int getQuantity();
	std::deque<int> getChromosome();
	void mutate(std::vector<int>, int C, int mutationChance, int geneChance);
	
	static int RandomNumber(int a, int b) {
		return a + (rand() % (b - a + 1));
	}

	bool operator<(Individual const& ind) const;
};