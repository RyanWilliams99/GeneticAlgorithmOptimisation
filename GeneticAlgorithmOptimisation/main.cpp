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
	
	//TestGeneticAlgorithmLogResults(ROULETTE, 2);
	TestGeneticAlgorithmLogResults(TOURNAMENT, 10);

}