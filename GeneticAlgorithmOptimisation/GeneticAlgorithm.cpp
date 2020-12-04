#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <random>
#include <iomanip>

#include "HelperDisplayGA.h"
#include "GeneticAlgorithm.h"



float RandomFloat(float min, float max) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

float GenerateFitnessValues(individual ind)
{
	float fitness = 0;
	for (int i = 0; i < N; i++) {
		fitness = fitness + ind.gene[i];
	}
	return fitness;

}


void RunGeneticAlgorithm()
{
	//First of all set population size number of generations 
	//Run GA and output

	srand(time(NULL));
	std::cout << std::setprecision(4);

	individual population[P];
	individual offspring[P];


	//Create initial population
	for (int i = 0; i < P; i++)
	{
		for (int j = 0; j < N; j++)
		{
			population[i].gene[j] = RandomFloat(0.0, MUTSTEP);
		}
		population[i].fitness = 0;
	}

	std::cout << "Initial Genes" << std::endl;
	PrintPopulationGenes(population);

	//5 Generations
	for (int generation = 0; generation < GENERATIONS; ++generation) {



		std::cout << "--------------------------------------------------------------Generation" << generation + 1 << "-------------------------------------------------------" << std::endl;

		//Get fitness values for each individual
		for (int i = 0; i < P; i++)
		{
			population[i].fitness = GenerateFitnessValues(population[i]);
		}

		std::cout << "Population" << std::endl;
		PrintPopulationFitness(population);

		//Selection
		for (int i = 0; i < P; i++) {
			int parent1 = rand() % P;
			int parent2 = rand() % P;
			if (population[parent1].fitness > population[parent2].fitness)
				offspring[i] = population[parent1];
			else
				offspring[i] = population[parent2];
		}


		//Crossover
		individual temp;
		for (int i = 0; i < P; i += 2)
		{
			temp = offspring[i];
			int crosspoint = rand() % N;
			for (int j = crosspoint; j < N; j++) {
				offspring[i].gene[j] = offspring[i + 1].gene[j];
				offspring[i + 1].gene[j] = temp.gene[j];
			}
		}

		//Mutation
		for (int i = 0; i < P; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (rand() < MUTRATE)
				{
					float alter = RandomFloat(0.0, MUTSTEP);
					if (rand() % 2) offspring[i].gene[j] = offspring[i].gene[j] + alter;
					else offspring[i].gene[j] = offspring[i].gene[j] - alter;
				}
			}
		}


		////Mutation old
		//for (int i = 0; i < P; i++) {
		//	for (int j = 0; j < N; j++) {
		//		if (rand() < MUTRATE) {
		//			if (offspring[i].gene[j] == 1) offspring[i].gene[j] = 0;
		//			else offspring[i].gene[j] = 1;
		//		}
		//	}
		//}


		std::cout << "Offspring" << std::endl;
		PrintPopulationFitness(offspring);

		//Copy offspring to population
		for (int i = 0; i < P; i++)
		{
			population[i] = offspring[i];
		}

	}

	//std::cout << "Final Genes" << std::endl;
	//PrintPopulationGenes(population);

	return;

}