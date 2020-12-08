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
	TestGeneticAlgorithmLogResults(ROULETTE, WS3, 10);
	TestGeneticAlgorithmLogResults(TOURNAMENT, WS3, 10);
}