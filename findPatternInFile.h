#include <iostream>
#include <fstream>
#include <vector>

void solutionFirstProblem(std::vector<std::string> files, std::vector<std::string> patterns)
{
	std::cout << "SOLUTION 1\n";

	for (auto &file_name : files)
	{
		std::ifstream infile(file_name); // create ifstream var to read from
		std::string currLine;

		while (std::getline(infile, currLine))
		{
			std::cout << "Current line is " << currLine << ".\n";
		}
	}

	std::cout << "PRINTING PATTERNS:\n";

	for (auto &file_name : patterns)
	{
		std::ifstream infile(file_name); // create ifstream var to read from
		std::string currLine;

		while (std::getline(infile, currLine))
		{
			std::cout << "Current line is " << currLine << ".\n";
		}
	}
}
