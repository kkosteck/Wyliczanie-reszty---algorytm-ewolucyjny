#include "Individual.h"

Individual::Individual(int C, std::vector<int> genes) {
	int length = RandomNumber(1, 5);
	for (int i = 0; i < length; ++i) {
		chromosome.push_back(genes[RandomNumber(0, genes.size() - 1)]);
	}
	calculateFitness(C);
};

Individual::Individual() {
	difference = 0;
	quantity = 0;
}

void Individual::calculateFitness(int C) {

	difference = abs(C - accumulate(chromosome.begin(), chromosome.end(), 0));
	quantity = chromosome.size();
}

void Individual::mutate(std::vector<int> genes, int C, int mutationChance, int addGeneChance, int removeGeneChance) {

	for (unsigned int i = 0; i < chromosome.size(); ++i) {
		if (RandomNumber(1,100) <= mutationChance) { //10% chances for mutation
			if (RandomNumber(1, 100) <= removeGeneChance) { //10% chance to delete gene
				if (chromosome.size() > 1) { // do not delete if chromosome has only one gene
					chromosome.erase(chromosome.begin() + i);
					--i; // decrease iterator in order to not skip a gene
				}
			}
			else if (RandomNumber(1,100) <= addGeneChance) { //10% chance to add new gene
				chromosome.push_front(genes[RandomNumber(0, genes.size() - 1)]);
				++i; //increase iterator in order to not skip a gene
			}
			else { //80% chance to change gene
				chromosome[i] = genes[RandomNumber(0, genes.size() - 1)];
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