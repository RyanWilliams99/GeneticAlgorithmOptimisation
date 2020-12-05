#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <random>
#include <iomanip>

#include "HelperDisplayGA.h"
#include "GeneticAlgorithm.h"
#include "HelperCSV.h"


float RandomFloat(float min, float max) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

float GenerateFitnessValues(Individual ind)
{
	float fitness = 0;
	for (int i = 0; i < N; i++)
		fitness = fitness + ind.gene[i];
	return fitness;
}


float GetPopulationFitness(Individual population[])
{
	float t = 0;

	//std::cout << "( ";

	for (int i = 0; i < P; i++)
	{
		//std::cout << "" << population[i].fitness << " ";

		t = t + population[i].fitness;

	}

	return t;
	//std::cout << ") Total Fitness - " << t << std::endl;
}


float GetBestFitnessInPopulation(Individual pop[])
{
	float returnValue = 0.0f;
	for (size_t i = 0; i < P; i++)
	{
		if (pop[i].fitness > returnValue)
			returnValue = pop[i].fitness;
	}
	return returnValue;
}

float GetMeanFitnessInPopulation(Individual pop[])
{
	float returnValue = 0.0f;
	for (size_t i = 0; i < P; i++)
	{
		if (pop[i].fitness > returnValue)
			returnValue += pop[i].fitness;
	}
	return returnValue / P;
}


/// <summary>
/// Runs a GA
/// </summary>
/// <param name="selectionType">
/// enum defined in GeneticAlgorithm.h
/// </param>
/// <returns>
/// Returns a list of GenerationResult objects, each one contains the mean and best fitness values
/// </returns>
std::vector<GenerationResult> RunGeneticAlgorithm(SelectionType selectionType)
{
	//Return a list of GA results
	std::vector<GenerationResult> returnValue;

	//GA Result contains every generation and its mean fitness



	srand(time(NULL));
	std::cout << std::setprecision(4);

	Individual population[P];
	Individual offspring[P];

	/////////////////////////////
	//Create initial population//
	/////////////////////////////
	for (int i = 0; i < P; i++)
	{
		for (int j = 0; j < N; j++)
		{
			population[i].gene[j] = RandomFloat(0.0, MUTSTEP);
		}
		population[i].fitness = 0;
	}

	/////////////
	//main loop//
	/////////////
	for (int i = 0; i < GENERATIONS; ++i) {

		GenerationResult currrentGeneration{ };

		currrentGeneration.generation = i + 1;
		


		std::cout << "--------------------------------------------------------------Generation" << i + 1 << "-------------------------------------------------------" << std::endl;

		//Get fitness values for each individual
		for (int i = 0; i < P; i++)
		{
			population[i].fitness = GenerateFitnessValues(population[i]);
		}

		std::cout << "Population" << std::endl;
		PrintPopulationFitness(population);


		float totalPopFitness = GetPopulationFitness(population);

		

		/////////////
		//Selection//
		/////////////
		switch (selectionType)
		{
		case ROULETTE:
			for (int i = 0; i < P; i++) {
				//int selection_point = static_cast<int>(rand() % static_cast<int>(totalPopFitness));

				int selection_point = RandomFloat(0, totalPopFitness);

				
				float running_total = 0;
				int j = 0;
				while (running_total <= selection_point) {
					running_total += population[j].fitness;
					j++;
				}
				offspring[i] = population[j - 1];
			}
			break;
		case TOURNAMENT:
			for (int i = 0; i < P; i++) {
				int parent1 = rand() % P;
				int parent2 = rand() % P;
				if (population[parent1].fitness > population[parent2].fitness)
					offspring[i] = population[parent1];
				else
					offspring[i] = population[parent2];
			}
			break;
		default:
			break;
		}

		/////////////
		//Crossover//
		/////////////
		Individual temp;
		for (int i = 0; i < P; i += 2)
		{
			temp = offspring[i];
			int crosspoint = rand() % N;
			for (int j = crosspoint; j < N; j++) {
				offspring[i].gene[j] = offspring[i + 1].gene[j];
				offspring[i + 1].gene[j] = temp.gene[j];
			}
		}

		////////////
		//Mutation//
		////////////
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

		//////////////////////////////////////
		//Calculate and store fitness values//
		//////////////////////////////////////
		currrentGeneration.bestFitness = GetBestFitnessInPopulation(population);
		currrentGeneration.meanFitness = GetMeanFitnessInPopulation(population);

		returnValue.push_back(currrentGeneration);

		/////////////////////
		//Update Population//
		/////////////////////
		for (int i = 0; i < P; i++)
			population[i] = offspring[i];
		
		
	}
	return returnValue;
}


void RunGeneticAlgorithmWithLogging(SelectionType selectionType)
{
	
	std::vector<GenerationResult> gaResult;


	gaResult = RunGeneticAlgorithm(selectionType);

	// current date/time based on current system
	time_t now = time(0);

	// convert now to string form
	char* dt = ctime(&now);




	// Make three vectors, each of length 100 filled with 1s, 2s, and 3s
	std::vector<int> generation;
	std::vector<int> meanFitness;
	std::vector<int> bestFitness;

	for (size_t i = 0; i < gaResult.size(); i++)
	{
		generation.push_back(gaResult[i].generation);
		meanFitness.push_back(gaResult[i].meanFitness);
		bestFitness.push_back(gaResult[i].bestFitness);

	}


	//Generation //Mean fitness //Best fitness


	// Wrap into a vector
	std::vector<std::pair<std::string, std::vector<int>>> vals = { {"Generation", generation}, {"Mean Fitness", meanFitness}, {"Best Fitness", bestFitness} };




	WriteCSV("tste.csv", vals);


}
