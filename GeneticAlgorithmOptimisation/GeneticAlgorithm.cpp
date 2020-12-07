#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <random>
#include <iomanip>
#include <math.h>

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


float GenerateFitnessValuesWorkSheet3(Individual ind)
{

	float fitness = 0;

	fitness += 10 * N;

	float x = 0.0f;

	float sum = 0.0f;

	float pie = atan(1) * 4;

	for (size_t i = 0; i < N; i++)
	{
		x = ind.gene[i];

		sum += (x * x) - (10 * cos(2 * pie * x));

	}

	fitness += sum;

	return fitness;

}


float GetPopulationFitness(Individual population[])
{
	float t = 0;
	for (int i = 0; i < P; i++)
		t = t + population[i].fitness;
	return t;
}


float GetBestFitnessInPopulation(Individual pop[])
{

	float returnValue = FLT_MAX;
	for (size_t i = 0; i < P; i++)
	{
		if (pop[i].fitness < returnValue)
			returnValue = pop[i].fitness;
	}
	return returnValue;
}

float GetMeanFitnessInPopulation(Individual pop[])
{
	float returnValue = 0.0f;
	for (size_t i = 0; i < P; i++)
	{
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
GeneticAlgortihmResult RunGeneticAlgorithm(SelectionType selectionType)
{
	GeneticAlgortihmResult returnValue;
	//GA Result contains every generation and its mean fitness

	switch (selectionType)
	{
	case ROULETTE:
		//printf("Running basic GA with Roulette wheel selection (theoritical limits, max fitness %8.2f, min fitness %4.2f)...\n", MAXPOSSIBLEFITNESS, MINPOSSIBLEFITNESS);
		break;
	case TOURNAMENT:
		//printf("Running basic GA with Tournament selection (theoritical limits, max fitness %8.2f, min fitness %4.2f)...\n", MAXPOSSIBLEFITNESS, MINPOSSIBLEFITNESS);
		break;
	default:
		break;
	}

	srand(time(NULL));
	//std::cout << std::setprecision(4);

	Individual population[P];
	Individual offspring[P];

	/////////////////////////////
	//Create initial population//
	/////////////////////////////
	for (int i = 0; i < P; i++)
	{
		for (int j = 0; j < N; j++)
		{
			population[i].gene[j] = RandomFloat(MINGENEVALUE, MAXGENEVALUE);
		}
		population[i].fitness = 0;
	}

	/////////////
	//main loop//
	/////////////
	for (int i = 0; i < GENERATIONS; ++i) {

		GenerationResult currrentGeneration{ };

		currrentGeneration.generation = i + 1;


		//Get fitness values for each individual
		for (int j = 0; j < P; j++)
		{
			population[j].fitness = GenerateFitnessValuesWorkSheet3(population[j]);
		}

		//std::cout << "Population" << std::endl;
		//PrintPopulationFitness(population);


		/////////////
		//Selection//
		/////////////
		switch (selectionType)
		{
		case ROULETTE:
			for (int i = 0; i < P; i++) {

				int selection_point = RandomFloat(0, GetPopulationFitness(population));
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
				if (population[parent1].fitness < population[parent2].fitness)
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

		//returnValue.push_back


		returnValue.GenerationResults.push_back(currrentGeneration); //Push this generation onto the return value

		/////////////////////
		//Update Population//
		/////////////////////
		for (int i = 0; i < P; i++)
			population[i] = offspring[i];
		
		
	}
	return returnValue;
}


void TestGeneticAlgorithmLogResults(SelectionType selectionType, int numberOfRuns)
{

	std::vector<GeneticAlgortihmResult> result;
	GeneticAlgortihmResult tempResult;

	result.push_back(tempResult);

	for (size_t i = 0; i < numberOfRuns; i++)
	{

		result.push_back(RunGeneticAlgorithm(selectionType));




		//tempResult = RunGeneticAlgorithm(selectionType); //Result from 1 run of the GA
		//for (size_t j = 0; j < tempResult.size(); j++)
		//{
		//	//get 
		//	tempResult[j].generation = (result[j].generation + tempResult[j].generation) / result.size();
		//	tempResult[j].meanFitness = (result[j].meanFitness + tempResult[j].meanFitness) / result.size();
		//	tempResult[j].bestFitness = (result[j].bestFitness + tempResult[j].bestFitness) / result.size();

		//	
		//	result[i].
		//}

	}



	//average all runs
	//write to csv and console
	//WriteGAResultToCSV(selectionType, result);
	//PrintGAResultToConsole(selectionType, result);

}
