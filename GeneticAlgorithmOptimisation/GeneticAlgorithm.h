#pragma once

#include <vector>

/// <summary>
/// Accessible to other files
/// </summary>
const int N = 10; //Number of genes
const int P = 50; //Population 
const int GENERATIONS = 500; //Generations

const float MUTRATE = 1; 
const float MINGENEVALUE = -5.12f;
const float MAXGENEVALUE = 5.12f;
const float MUTSTEP = 5.12f; //????

//Each individual
typedef struct {
	float gene[N];
	float fitness;
} Individual;

//Each run
typedef struct {
	int generation;
	float bestFitness;
	float meanFitness;
} GeneticAlgorithmResult;

enum SelectionType { ROULETTE, TOURNAMENT };

enum FitnessFunction { WS3, wOpt };

void RunGeneticAlgorithmWithLogging(SelectionType slectionType);