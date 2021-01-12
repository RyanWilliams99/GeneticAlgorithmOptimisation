#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <random>
#include <iomanip>

#include "HelperDisplayGA.h"
#include "HelperBasicIO.h"
#include "GeneticAlgorithm.h"


int main()
{
	//BasicAdd Function
	//TestGeneticAlgorithmLogResults(TOURNAMENT, BasicAdd, 10);
	//TestGeneticAlgorithmLogResults(ROULETTE, BasicAdd, 10);

	//WS3 Fitness function
	//TestGeneticAlgorithmLogResults(TOURNAMENT, WS3, 10);
	//TestGeneticAlgorithmLogResults(ROULETTE, WS3, 10);

	//WOPT Function
	TestGeneticAlgorithmLogResults(TOURNAMENT, wOpt, 10);
	//TestGeneticAlgorithmLogResults(ROULETTE, wOpt, 10);
}
