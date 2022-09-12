#include <iostream>
#include <fstream>
#include <vector>

void solutionSecondProblem(std::vector<std::string> files)
{
	std::cout << "SOLUTION 2\n";

	for (auto &file_name : files)
	{
		std::ifstream infile(file_name); // create ifstream var to read from
		std::string currLine;

		while (std::getline(infile, currLine))
		{
			std::cout << "Current line is " << currLine << ".\n";
		}
	}
}
