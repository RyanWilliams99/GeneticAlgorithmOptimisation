#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair

#include "GeneticAlgorithm.h"
#include "HelperBasicIO.h"

void WriteCSV(std::string filename, std::vector<std::pair<std::string, std::vector<float>>> dataset) {
    // Make a CSV file with one or more columns of integer values
    // Each column of data is represented by the pair <column name, column data>
    //   as std::pair<std::string, std::vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size

    // Create an output filestream object
    std::ofstream myFile(filename);

    // Send column names to the stream
    for (int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";

    // Send data to the stream
    for (int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for (int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }

    // Close the file
    myFile.close();

}


void WriteGAResultToCSV(SelectionType selectionType, FitnessFunction fitFunction, GeneticAlgortihmResult gaResult)
{
	printf("Writing results to csv...\n\n");
	// current date/time based on current system
	time_t now = time(0);

	// convert now to string form
	//char* dt = ctime(&now);

	// Make three vectors, each of length 100 filled with 1s, 2s, and 3s
	std::vector<float> generation;
	std::vector<float> meanFitness;
	std::vector<float> bestFitness;

	for (size_t i = 0; i < gaResult.GenerationResults.size(); i++)
	{
		generation.push_back(gaResult.GenerationResults[i].generation);
		meanFitness.push_back(gaResult.GenerationResults[i].meanFitness);
		bestFitness.push_back(gaResult.GenerationResults[i].bestFitness);

	}


	//Generation //Mean fitness //Best fitness


	time_t timer;
	struct tm y2k = { 0 };
	double seconds;

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	seconds = difftime(timer, mktime(&y2k));



	// Wrap into a vector

	std::pair<std::string, std::vector<float>> val1 = { "Generation", generation };
	std::pair<std::string, std::vector<float>> val2 = { "Mean Fitness", meanFitness };
	std::pair<std::string, std::vector<float>> val3 = { "Best Fitness", bestFitness };



	std::vector<std::pair<std::string, std::vector<float>>> vals = { val1, val2, val3 };


	std::string pathAndFilename;

	switch (selectionType)
	{
	case ROULETTE:
		switch (fitFunction)
		{
		case WS3:
			pathAndFilename = "../Output/RouletteWS3(ID" + std::to_string(seconds) + ").csv";
			break;
		case wOpt:
			pathAndFilename = "../Output/RouletteWOPT(ID" + std::to_string(seconds) + ").csv";
			break;
		case BasicAdd:
			pathAndFilename = "../Output/RouletteBasicAdd(ID" + std::to_string(seconds) + ").csv";
			break;
		default:
			break;
		}
		break;
	case TOURNAMENT:
		switch (fitFunction)
		{
		case WS3:
			pathAndFilename = "../Output/TournamentWS3(ID" + std::to_string(seconds) + ").csv";
			break;
		case wOpt:
			pathAndFilename = "../Output/TournamentWOPT(ID" + std::to_string(seconds) + ").csv";
			break;
		case BasicAdd:
			pathAndFilename = "../Output/TournamentBasicAdd(ID" + std::to_string(seconds) + ").csv";
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	WriteCSV(pathAndFilename, vals);
}


void PrintGAResultToConsole(SelectionType selectionType, GeneticAlgortihmResult gaResult)
{

	PrintLine("Gen | Mean Fit | Best Fit");
	for (size_t i = 0; i < gaResult.GenerationResults.size(); i++)
	{
		printf("%2.3d | %8.4f | %8.4f \n", gaResult.GenerationResults[i].generation, gaResult.GenerationResults[i].meanFitness, gaResult.GenerationResults[i].bestFitness);
	}
}
