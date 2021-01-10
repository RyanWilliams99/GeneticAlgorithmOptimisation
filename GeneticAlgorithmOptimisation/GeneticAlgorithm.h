#pragma once

#include <vector>


const int N = 1000; //Number of genes
const int P = 500; //Population 
const int GENERATIONS = 500; //Generations

const float MUTRATE = 0.01; 
const float MUTSTEP = 0.01; 

//Each individual
typedef struct {
	float gene[N];
	float fitness;
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

enum FitnessFunction { WS3, wOpt, BasicAdd};

void TestGeneticAlgorithmLogResults(SelectionType selectionType, FitnessFunction fitnessFunction, int numberOfRuns);

