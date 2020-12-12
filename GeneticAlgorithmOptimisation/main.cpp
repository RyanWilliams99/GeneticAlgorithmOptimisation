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
	//TestGeneticAlgorithmLogResults(ROULETTE, BasicAdd, 100);
	TestGeneticAlgorithmLogResults(TOURNAMENT, BasicAdd, 100);

	//WS3 Fitness function
	//TestGeneticAlgorithmLogResults(ROULETTE, WS3, 1000);
	//TestGeneticAlgorithmLogResults(TOURNAMENT, WS3, 1000);

	//WOPT Function
	//TestGeneticAlgorithmLogResults(ROULETTE, wOpt, 100);
	//TestGeneticAlgorithmLogResults(TOURNAMENT, wOpt, 1);

}