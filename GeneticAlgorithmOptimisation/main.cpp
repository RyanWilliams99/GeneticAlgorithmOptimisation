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
	//TestGeneticAlgorithmLogResults(TOURNAMENT, BasicAdd, 1);
	//TestGeneticAlgorithmLogResults(ROULETTE, BasicAdd, 100);

	//WS3 Fitness function
	//TestGeneticAlgorithmLogResults(TOURNAMENT, WS3, 100);
	TestGeneticAlgorithmLogResults(ROULETTE, WS3, 100);

	//WOPT Function
	//TestGeneticAlgorithmLogResults(TOURNAMENT, wOpt, 1);
	//TestGeneticAlgorithmLogResults(ROULETTE, wOpt, 100);
}
