#pragma once

const int N = 50; //Numnber of genes
const int P = 10; //population 
const int GENERATIONS = 10;
const float MUTRATE = 0.2;
const float MUTSTEP = 1.0;


typedef struct {
	float gene[N];
	float fitness;
} individual;

enum SelectionType {ROULETTE, TOURNAMENT};


void RunGeneticAlgorithm(SelectionType slectionType);

typedef struct {
	int generation;
	float bestFitness;
	float meanFitness;
} GAResult;

std::vector<GAResult> result;

