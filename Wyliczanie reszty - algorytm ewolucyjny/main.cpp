#include <iostream>
#include <vector>
#include <ctime>
#include<algorithm>
#include "Individual.h"

using namespace std;

int main() {
	srand((unsigned)time(0));

	int genes[] = { 1, 2, 5, 10, 20, 50, 100, 200 };
	int C, populationSize;

	cout << "Podaj wartosc reszty (C):";
	cin >> C;
	cout << "Podaj liczebnosc populacji:";
	cin >> populationSize;

	vector<Individual> population;
	for (int i = 0; i < populationSize; ++i) {
		population.push_back(Individual(C, genes));
	}

	int generationLimit;
	cout << "Ile pokolen chcesz stworzyc:";
	cin >> generationLimit;

	vector<Individual> theBestOfGenerations;
	for (int generation = 1; generation <= generationLimit; ++generation) {
		vector<Individual> newGeneration;

		Individual indTemp = *min_element(population.begin(), population.end());
		cout << "Generation: " << generation << ". ";
		cout << "Quantity: " << indTemp.getQuantity() << " Difference: " << indTemp.getDifference() << endl;
		deque<int> temp = indTemp.getChromosome();
		cout << "Denominations: ";
		for (auto& y : temp) {
			cout << y << " ";
		}
		cout << endl;
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
				temp.mutate(genes, C);
				newGeneration.push_back(temp);
			} 
			else {
				Individual temp = population[ind1];
				temp.mutate(genes, C);
				newGeneration.push_back(temp);
			}
		}
		population = newGeneration;
	}
	cout << "C: " << C << " Generations: " << generationLimit << " Population size: " << populationSize << endl;
	Individual indTemp = *min_element(theBestOfGenerations.begin(), theBestOfGenerations.end());
	cout << "Quantity: " << indTemp.getQuantity() << " Difference: " << indTemp.getDifference() << endl;
	deque<int> temp = indTemp.getChromosome();
	cout << "Denominations: ";
	for (auto& y : temp) {
		cout << y << " ";
	}
	cout << endl;
}
