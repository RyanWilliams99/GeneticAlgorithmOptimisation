#pragma once




const int N = 50; //Numnber of genes
const int P = 10; //population 
const int GENERATIONS = 10;
const float MUTRATE = 0.2;
const float MUTSTEP = 1.0;

//Each individual
typedef struct {
	float gene[N];
	float fitness;
} individual;

//Each generation
typedef struct {
	int generation;
	float bestFitness;
	float meanFitness;
} GenerationResult;

typedef struct {
	//TODO
} GAResult;



enum SelectionType { ROULETTE, TOURNAMENT };

void RunGeneticAlgorithm(SelectionType slectionType);
void RunGeneticAlgorithmWithLogging(SelectionType slectionType);