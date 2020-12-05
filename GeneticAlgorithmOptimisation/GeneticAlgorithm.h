#pragma once

#include <vector>


const int N = 50; //Numnber of genes
const int P = 10; //Population 
const int GENERATIONS = 50; //Generations
const float MUTRATE = 0.2; 
const float MUTSTEP = 1.0;


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

//typedef struct {
//	GenerationResult GenerationResults[];
//} GAResult;


enum SelectionType { ROULETTE, TOURNAMENT };

std::vector<GenerationResult> RunGeneticAlgorithm(SelectionType selectionType);

void RunGeneticAlgorithmWithLogging(SelectionType slectionType);

