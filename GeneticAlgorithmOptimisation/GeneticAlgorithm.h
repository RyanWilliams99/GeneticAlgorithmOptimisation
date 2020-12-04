#pragma once

const int N = 50; //Numnber of genes
const int P = 50; //population 
const int GENERATIONS = 50;
const float MUTRATE = 0.2;
const float MUTSTEP = 1.0;

typedef struct {
	float gene[N];
	float fitness;
} individual;


void RunGeneticAlgorithm();
