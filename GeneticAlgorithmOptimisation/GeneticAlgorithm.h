#pragma once

#include <vector>

/// <summary>
/// Accessible to other files
/// </summary>
const int N = 3; //Number of genes
const int P = 50; //Population 
const int GENERATIONS = 50; //Generations

const float MUTRATE = 1; 
const float MINGENEVALUE = -5.12f;
const float MAXGENEVALUE = 5.12f;
const float MUTSTEP = 5.12f; //????

//Each individual
typedef struct {
	float gene[N];
	float fitness;
	float adjustedFitness; //used for roulette wheel with minimisation function
} Individual;

//Each generation
typedef struct {
	int generation;
	float bestFitness;
	float meanFitness;
} GenerationResult;

//Each time we run
typedef struct {
	std::vector<GenerationResult> GenerationResults;
} GeneticAlgortihmResult;


enum SelectionType { ROULETTE, TOURNAMENT };

enum FitnessFunction { WS3, wOpt };

void TestGeneticAlgorithmLogResults(SelectionType selectionType, FitnessFunction fitnessFunction, int numberOfRuns);

