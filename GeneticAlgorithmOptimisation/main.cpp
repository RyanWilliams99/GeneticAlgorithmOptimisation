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
	PrintLine("Running basic GA with Roulette wheel selection...");
	RunGeneticAlgorithm(ROULETTE);

	PrintLine("Running basic GA with Tournament wheel selection...");
	RunGeneticAlgorithm(TOURNAMENT);



}