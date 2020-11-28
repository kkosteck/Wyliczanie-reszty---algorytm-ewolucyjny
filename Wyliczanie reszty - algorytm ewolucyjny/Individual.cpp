#include "Individual.h"

Individual::Individual(std::vector<int> chromosome) {
	this->chromosome = chromosome;
	fitness = calculateFitness();
};

int Individual::calculateFitness() {

	return 0;
}

void Individual::mutate(int genes[]) {


}

int Individual::getFitness() { return fitness; }

int randomNumber(int a, int b) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(a, b); // define the range

	return distr(gen);
}

std::vector<int> Individual::getChromosome() { return chromosome; }