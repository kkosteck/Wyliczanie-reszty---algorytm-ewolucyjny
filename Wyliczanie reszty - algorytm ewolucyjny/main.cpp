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
	sort(temp.begin(), temp.end(), std::greater<int>());
	for (auto& y : temp) {
		*file << y << " ";
	}
	*file << std::endl;
}


int main(int argc, char* argv[]) { //change, generationLimit, populationSize, mutationChance, addGeneChance, removeGeneChance
	srand((unsigned)time(0));

	if (argc < 8) {
		std::cout << "Not enough arguments!" << std::endl;
		return 1;
	}

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

	std::pair<Individual,int> theBestOfGenerations;
	everyGen << "GENERATION " << "QUANTITY " << "DIFFERENCE " << "DENOMINATIONS" << std::endl;
	theBestGen << "GENERATION " << "QUANTITY " << "DIFFERENCE " << "DENOMINATIONS" << std::endl;

	for (int generation = 1;; ++generation) {
		std::vector<Individual> newGeneration;
		Individual indTemp = *min_element(population.begin(), population.end());
		writeLog(&everyGen, indTemp, generation);

		if(generation == 1)
			theBestOfGenerations = std::make_pair(indTemp, generation);
		else if (indTemp < theBestOfGenerations.first) {
			writeLog(&theBestGen, indTemp, generation);
			theBestOfGenerations = std::make_pair(indTemp, generation);
			std::cout << "1" << std::endl;
		}
		else if (generation - theBestOfGenerations.second > generationLimit && theBestOfGenerations.first.getDifference() == 0)
			break;

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
	std::cout << "Quantity: " << theBestOfGenerations.first.getQuantity() << " Difference: " << theBestOfGenerations.first.getDifference();
	std::deque<int> temp = theBestOfGenerations.first.getChromosome();
	std::cout << " Denominations: ";
	sort(temp.begin(), temp.end(), std::greater<int>());
	for (auto& y : temp) {
		std::cout << y << " ";
	}
	std::cout << std::endl;
	std::cout << "Generation: " << theBestOfGenerations.second << std::endl;
}
