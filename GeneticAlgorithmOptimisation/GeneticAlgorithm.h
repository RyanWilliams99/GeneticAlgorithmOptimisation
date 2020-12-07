#pragma once

#include <vector>


const int N = 10; //Numnber of genes
const int P = 50; //Population 
const int GENERATIONS = 50; //Generations
const float MUTRATE = 0.2; 
const float MINGENEVALUE = -5.12f;
const float MAXGENEVALUE = 5.12f;
const float MUTSTEP = 1.0; //????

const float MINPOSSIBLEFITNESS = N * MINGENEVALUE;
const float MAXPOSSIBLEFITNESS = N * MAXGENEVALUE;

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

enum SelectionType { ROULETTE, TOURNAMENT };

std::vector<GenerationResult> RunGeneticAlgorithm(SelectionType selectionType);

void RunGeneticAlgorithmWithLogging(SelectionType slectionType);

void TestFitnessFunctionWS3(float val1, float val2, float val3);
void TestFitnessFunctionAssignment1(float val1, float val2, float val3);


