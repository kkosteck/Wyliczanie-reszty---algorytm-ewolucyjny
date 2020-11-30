#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <string>
#include "Individual.h"

void writeLog(std::ofstream *file, Individual ind, int generation) {
	*file << generation << " " << ind.getQuantity() << " " << ind.getDifference() << " ";
	std::deque<int> temp = ind.getChromosome();
	for (auto& y : temp) {
		*file << y << " ";
	}
	*file << std::endl;
}


int main(int argc, char* argv[]) { //change, generationLimit, populationSize, mutationChance, addGeneChance, removeGeneChance
	srand((unsigned)time(0));

	std::vector<int> genes = { 1, 2, 5, 10, 20, 50, 100, 200, 500 };
	int C = atoi(argv[1]), generationLimit = atoi(argv[2]), populationSize = atoi(argv[3]);
	int mutationChance = atoi(argv[4]), addGeneChance = atoi(argv[5]), removeGeneChance = atoi(argv[6]);

	std::string filename_everyGen = "every_generetion_" + std::to_string(C) + '_' + std::to_string(generationLimit) + '_' + std::to_string(populationSize) + ".txt";
	std::ofstream everyGen(filename_everyGen);
	std::string filename_theBestGen = "the_best_generations_" + std::to_string(C) + '_' + std::to_string(generationLimit) + '_' + std::to_string(populationSize) + ".txt";
	std::ofstream theBestGen(filename_theBestGen);

	std::vector<Individual> population;
	for (int i = 0; i < populationSize; ++i) {
		population.push_back(Individual(C, genes));
	}

	std::vector<Individual> theBestOfGenerations;
	everyGen << "GENERATION " << "QUANTITY " << "DIFFERENCE " << "DENOMINATIONS" << std::endl;
	theBestGen << "GENERATION " << "QUANTITY " << "DIFFERENCE " << "DENOMINATIONS" << std::endl;

	for (int generation = 1; generation <= generationLimit; ++generation) {
		std::vector<Individual> newGeneration;
		Individual indTemp = *min_element(population.begin(), population.end());
		writeLog(&everyGen, indTemp, generation);
		theBestOfGenerations.push_back(indTemp);
		indTemp = *min_element(theBestOfGenerations.begin(), theBestOfGenerations.end());
		writeLog(&theBestGen, indTemp, generation);

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
