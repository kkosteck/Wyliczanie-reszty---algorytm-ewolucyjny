#include "Individual.h"

Individual::Individual(int C, int genes[]) {
	int length = RandomNumber(1, 5);
	for (int i = 0; i < length; ++i) {
		chromosome.push_back(genes[RandomNumber(0, 7)]);
	}
	calculateFitness(C);
};

void Individual::calculateFitness(int C) {

	difference = abs(C - accumulate(chromosome.begin(), chromosome.end(), 0));
	quantity = chromosome.size();
}

void Individual::mutate(int genes[], int C) {

	for (unsigned int i = 0; i < chromosome.size(); ++i) {
		if (RandomNumber(1,10) == 1) { //10% chances for mutation
			int gene = RandomNumber(0,9); 
			if (gene == 8) { //10% chance to delete gene
				if (chromosome.size() > 1) { // do not delete if chromosome has only one gene
					chromosome.erase(chromosome.begin() + i);
					--i; // decrease iterator in order to not skip a gene
				}
			}
			else if (gene == 9) { //10% chance to add new gene
				chromosome.push_front(genes[RandomNumber(0,7)]);
				++i; //increase iterator in order to not skip a gene
			}
			else { //80% chance to change gene
				chromosome[i] = genes[gene];
			}
		}
	}
	calculateFitness(C);
}

bool Individual::operator<(Individual const& ind) const {
	if (difference < ind.difference)
		return true;
	else if (difference > ind.difference)
		return false;
	else 
		return quantity < ind.quantity;
}

int Individual::getDifference() { return difference; }

int Individual::getQuantity() { return quantity; }

std::deque<int> Individual::getChromosome() { return chromosome; }