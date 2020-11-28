#pragma once
#include <deque>
#include<numeric>
#include <ctime>
class Individual
{
private:
	std::deque<int> chromosome;
	int difference, quantity;
	void calculateFitness(int C);
public:
	Individual(int C, int genes[]);
	Individual();
	int getDifference();
	int getQuantity();
	std::deque<int> getChromosome();
	void mutate(int genes[], int C);
	
	static int RandomNumber(int a, int b) {
		return a + (rand() % (b - a + 1));
	}

	bool operator<(Individual const& ind) const;
};