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
	//WS3 Fitness function
	//TestGeneticAlgorithmLogResults(ROULETTE, WS3, 1000);
	//TestGeneticAlgorithmLogResults(TOURNAMENT, WS3, 1000);

	//WOPT Function
	TestGeneticAlgorithmLogResults(TOURNAMENT, wOpt, 1);

}