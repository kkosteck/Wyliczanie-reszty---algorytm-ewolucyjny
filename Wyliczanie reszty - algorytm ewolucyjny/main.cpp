#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "Individual.h"

int main(int argc, char* argv[]) { //change, generationLimit, populationSize, mutationChance, addGeneChance, removeGeneChance
	srand((unsigned)time(0));

	std::vector<int> genes = { 1, 2, 5, 10, 20, 50, 100, 200, 500 };
	int C = atoi(argv[1]), generationLimit = atoi(argv[2]), populationSize = atoi(argv[3]);
	int mutationChance = atoi(argv[4]), addGeneChance = atoi(argv[5]), removeGeneChance = atoi(argv[6]);

	std::vector<Individual> population;
	for (int i = 0; i < populationSize; ++i) {
		population.push_back(Individual(C, genes));
	}

	std::vector<Individual> theBestOfGenerations;
	std::cout << "GENERATION" << "QUANTITY" << "DIFFERENCE" << "DENOMINATIONS" << std::endl;
	for (int generation = 1; generation <= generationLimit; ++generation) {
		std::vector<Individual> newGeneration;

		Individual indTemp = *min_element(population.begin(), population.end());
		std::cout << generation << " " << indTemp.getQuantity() << " " << indTemp.getDifference() << " ";
		std::deque<int> temp = indTemp.getChromosome();
		for (auto& y : temp) {
			std::cout << y << " ";
		}
		std::cout << std::endl;
		theBestOfGenerations.push_back(indTemp);

		// create new generation
		for (int i = 0; i <= populationSize; ++i) {
			int ind1 = Individual::RandomNumber(0, populationSize - 1);
			int ind2 = Individual::RandomNumber(0, populationSize - 1);
			while (ind1 == ind2) {
				ind2 = Individual::RandomNumber(0, populationSize - 1);
			}
			if (population[ind1] < population[ind2]) {
				Individual temp = population[ind1];
				temp.mutate(genes, C, mutationChance, addGeneChance, removeGeneChance);
				newGeneration.push_back(temp);
			} 
			else {
				Individual temp = population[ind1];
				temp.mutate(genes, C, mutationChance, addGeneChance, removeGeneChance);
				newGeneration.push_back(temp);
			}
		}
		population = newGeneration;
	}
	Individual indTemp = *min_element(theBestOfGenerations.begin(), theBestOfGenerations.end());
	std::cout << "Quantity: " << indTemp.getQuantity() << " Difference: " << indTemp.getDifference();
	std::deque<int> temp = indTemp.getChromosome();
	std::cout << " Denominations: ";
	for (auto& y : temp) {
		std::cout << y << " ";
	}
	std::cout << std::endl;
}
