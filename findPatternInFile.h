#include <iostream>
#include <fstream>
#include <vector>


void computeLPSArray(std::string pattern, int pattern_length, int lps_arr[])
{
    int j = 0;
    int i = 1;

    lps_arr[0] = 0; // lps_arr[0] is always 0

    while (i < pattern_length)
    {
        if (pattern[i] == pattern[j]) {
            j++;
            lps_arr[i] = j;
            i++;
        }
        else
        {
            if (j != 0)
		{
			j = lps_arr[j - 1];
            }
            else // if (j == 0)
            {
			lps_arr[i] = 0;
			i++;
            }
        }
    }
}

void KMPSearch(std::string pattern, std::string str, int row)
{
    int pattern_length = pattern.length();
    int str_length = str.length();

    // create lps_arr[] that will hold the longest prefix suffix
    // values for pattern
    int lps_arr[pattern_length];

    // Preprocess the pattern (calculate lps_arr[] array)
    computeLPSArray(pattern, pattern_length, lps_arr);

    int i = 0; // index for str[]
    int j = 0; // index for pattern[]

    while ((str_length - i) >= (pattern_length - j))
    {
        if (pattern[j] == str[i])
	  {
            j++;
            i++;
        }

        if (j == pattern_length)
	  {
		  /* printf("Found pattern at row %d index %d ", row, i - j); */
		  std::cout << "The pattern " << pattern << " was found at row " << row << " index " << i - j + 1 << ".\n";
		  j = lps_arr[j - 1];
        }

        // mismatch after j matches
        else if (i < str_length && pattern[j] != str[i])
	  {
            if (j != 0)
		{
			j = lps_arr[j - 1];
		}
            else
		{
			i = i + 1;
		}
        }
    }
}

void findInFile(std::string file_name, std::string pattern_name)
{
	std::ifstream infile(file_name); // create ifstream var to read from
	std::ifstream inpattern(pattern_name); // create ifstream var to read from

	std::cout << "\nSearching pattern from " << pattern_name << " in file " << file_name << ".\n";

	std::string pattern;
	std::getline(inpattern, pattern);

	std::string line;

	int aux = 1; // aux variable that represents rows

	while (std::getline(infile, line)) // gets a line
	{
		KMPSearch(pattern, line, aux);
		aux++;
	}
}

// First problem consist in each transmission file
void solutionFirstProblem(std::vector<std::string> files, std::vector<std::string> patterns)
{
	std::cout << "SOLUTION 1\n";

	for (auto &file_name : files) // selects the current file name in vector
	{
		for (auto &pattern_name : patterns) // selects the current pattern in vector
		{
			// Check if (pattern_name_file_data) == patern is in current file
			findInFile(file_name, pattern_name);
		}

	}

}
