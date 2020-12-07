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

	
	RunGeneticAlgorithmWithLogging(ROULETTE);
	RunGeneticAlgorithmWithLogging(TOURNAMENT);

	//PrintLine("Running basic GA with Tournament wheel selection...");
	//RunGeneticAlgorithm(TOURNAMENT);



}