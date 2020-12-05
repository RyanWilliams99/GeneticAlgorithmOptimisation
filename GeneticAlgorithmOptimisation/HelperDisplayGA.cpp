#include <iostream>

#include "GeneticAlgorithm.h"

void PrintPopulationGenes(Individual population[])
{

	for (int i = 0; i < P; i++)
	{
		std::cout << "Individual " << i << " - ";
		for (int j = 0; j < N; j++)
		{

			std::cout << " " << population[i].gene[j];

		}

		std::cout << std::endl;
	}
}

void PrintPopulationFitness(Individual population[])
{
	float t = 0;

	std::cout << "( ";

	for (int i = 0; i < P; i++)
	{
		std::cout << "" << population[i].fitness << " ";

		t = t + population[i].fitness;

	}
	std::cout << ") Total Fitness - " << t << std::endl;
}
