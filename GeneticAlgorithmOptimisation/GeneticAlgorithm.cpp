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

float GenerateFitnessValuesWopt(Individual ind)
{

	/*float fitness = 0;

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

	return fitness;*/

}


float GetPopulationFitness(Individual population[])
{
	float t = 0;
	for (int i = 0; i < P; i++)
		t += population[i].fitness;
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
GeneticAlgortihmResult RunGeneticAlgorithm(SelectionType selectionType, FitnessFunction fitnessFunction)
{
	GeneticAlgortihmResult returnValue;
	std::vector<GenerationResult> generationResults;

	//GA Result contains every generation and its mean fitness

	switch (selectionType)
	{
	case ROULETTE:
		switch (fitnessFunction)
		{
		case WS3:
			printf("Benchmarking GA with RW selection and ws3 (Pop %d, Gene size %d, Generations %d, Mutation rate %f)...\n", P, N, GENERATIONS, MUTRATE);
			break;
		case wOpt:
			printf("Benchmarking GA with RW selection and wopt (Pop %d, Gene size %d, Generations %d, Mutation rate %f)...\n", P, N, GENERATIONS, MUTRATE);
			break;
		default:
			break;
		}
		
		break;
	case TOURNAMENT:
		switch (fitnessFunction)
		{
		case WS3:
			printf("Benchmarking GA with Tournament selection and ws3 (Pop %d, Gene size %d, Generations %d, Mutation rate %f)...\n", P, N, GENERATIONS, MUTRATE);
			break;
		case wOpt:
			printf("Benchmarking GA with Tournament selection and wopt (Pop %d, Gene size %d, Generations %d, Mutation rate %f)...\n", P, N, GENERATIONS, MUTRATE);
			break;
		default:
			break;
		}
		
		break;
	default:
		break;
	}

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

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////main loop//////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < GENERATIONS; ++i) {

		GenerationResult currrentGeneration;

		currrentGeneration.generation = i + 1;


		//Get fitness values for each individual
		for (int j = 0; j < P; j++)
		{
			switch (fitnessFunction)
			{
			case WS3:
				population[j].fitness = GenerateFitnessValuesWorkSheet3(population[j]);
				break;
			case wOpt:
				//population[j].fitness = GenerateFitnessValuesWorkSheet3(population[j]);
				break;
			default:
				break;
			}
			
		}

		//std::cout << "Population" << std::endl;
		//PrintPopulationFitness(population);


		/////////////
		//Selection//
		/////////////
		switch (selectionType)
		{
		case ROULETTE:
		{

			//HOW DOES THIS ERROR MAKE IT ONLY DO 1 GENERATION EACH RUN????????
			for (int individual = 0; individual < P; individual++)
			{
				float selection_point = RandomFloat(0, GetPopulationFitness(population));
				float running_total = 0;
				int r = 0;
				while (running_total <= selection_point) {
					running_total += population[r].fitness;
					r++;
				}
				offspring[individual] = population[r - 1];
			}

		}
		case TOURNAMENT:
		{
			for (int i = 0; i < P; i++) {
				int parent1 = rand() % P;
				int parent2 = rand() % P;
				if (population[parent1].fitness < population[parent2].fitness)
					offspring[i] = population[parent1];
				else
					offspring[i] = population[parent2];
			}
			break;
		}
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


		generationResults.push_back(currrentGeneration); //Push this generation onto the return value

		/////////////////////
		//Update Population//
		/////////////////////
		for (int i = 0; i < P; i++)
		{
			population[i] = offspring[i];
		}

	}

	returnValue.GenerationResults.assign(generationResults.begin(), generationResults.end());

	return returnValue;
}


void TestGeneticAlgorithmLogResults(SelectionType selectionType, FitnessFunction fitnessFunction, int numberOfRuns)
{
	srand(time(NULL));

	std::vector<GeneticAlgortihmResult> result; //Store result of the GAs
	GeneticAlgortihmResult allRunsAveraged; //Final result for each GA averaged
	
	float meanFit = 0.0f, bestFit = 0.0f; //used for averaging

	//Run GA numberOfRuns times, store result each time
	for (size_t i = 0; i < numberOfRuns; i++)
		result.push_back(RunGeneticAlgorithm(selectionType, fitnessFunction));


	printf("Averaging results for each generation...\n");
	//for every generation...
	for (size_t j = 0; j < GENERATIONS; j++)
	{
		GenerationResult allGensAveraged;  //Final result for each generation averaged
		meanFit = 0.0f; //reset each time
		bestFit = 0.0f; //reset each time

		//for every time we ran the GA...
		for (size_t i = 0; i < numberOfRuns; i++)
		{
			meanFit += result[i].GenerationResults[j].meanFitness;
			bestFit += result[i].GenerationResults[j].bestFitness;
		}

		//average
		meanFit = meanFit / numberOfRuns;
		bestFit = bestFit / numberOfRuns;

		//store vals
		allGensAveraged.generation = j + 1;
		allGensAveraged.meanFitness = meanFit;
		allGensAveraged.bestFitness = bestFit;

		allRunsAveraged.GenerationResults.push_back(allGensAveraged);
	}

	//write to console then csv
	PrintGAResultToConsole(selectionType, allRunsAveraged);
	WriteGAResultToCSV(selectionType, allRunsAveraged);

}
