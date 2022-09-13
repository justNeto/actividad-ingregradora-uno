#ifndef FND_PALINDROME
#define FND_PALINDROME

#include "findPatternInFile.h"
#include <string>
#include <algorithm>

#define ARR_SIZE(type) \
	(sizeof(type) / sizeof (int))

void prtArr(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "[" << arr[i] << "]";
	}

	std::cout << "\n";
}

std::string pre_process(std::string line)
{

	for (int i = 0; i < line.length(); i += 2)
	{
		line.insert(i, "#");
	}

	line.insert(line.length(), "#");

	return line;
}

double minimized_values(double val_one, double val_two)
{
	return (val_one < val_two) ? val_one : val_two;
}

int max_index(int t_arr[], int size)
{
	int aux = 0;

	for (int i = 0; i < size; i++)
	{
		if (t_arr[i] > aux)
		{
			aux = t_arr[i];
		}
	}

	return aux;
}

int getIndex(int biggest, int t_arr[], int size)
{
	int index = 0;

	for (int i = 0; i < size; i++)
	{
		if (t_arr[i] == biggest)
		{
			index = i;
			break;
		}
	}

	return index;
}


std::vector<std::string> detectPalindrome(std::string line, int aux)
{
	std::vector<std::string> ans;

	line = pre_process(line);

	int size = line.length();
	int t_arr[size] = {0};

	int center = 0;
	int right = 0;

	for (int i = 0; i < size; i++)
	{
		int mirror_i = 2*center - i;

		if (right > i)
		{
			t_arr[i] = minimized_values(right - i, t_arr[mirror_i]);
		}
		else
		{

			t_arr[i] = 0;
		}

		try 
		{
			while ((line[i + 1 + t_arr[i]] == line[i - 1 - t_arr[i]]))
			{
				t_arr[i] += 1;
			}
		}
		catch (...)
		{
			;
		}

		if ((i + t_arr[i]) > right)
		{
			center = i;
			right = i + t_arr[i];
		}
	}

	int biggest_array_value = max_index(t_arr, size); // r
	int bgv_index = getIndex(biggest_array_value, t_arr, size); // c

	// Left side of palindrome
	int left_side = bgv_index - biggest_array_value;
	int right_side = bgv_index + biggest_array_value;

	aux = left_side;

	std::string result("");
	
	while (aux != right_side)
	{
		result += line[aux];
		aux++;
	}

	std::string init_index = std::to_string(left_side);
	std::string ending_index = std::to_string(right_side);
	
	result.erase(std::remove(result.begin(), result.end(), '#'), result.end());

	ans.push_back(result); // first value of string
	ans.push_back(init_index); // second init index
	ans.push_back(ending_index); // third ending index

	return ans;

}

void findPalindromeInFile(std::string file_name)
{
	std::ifstream infile(file_name); // read current file with file_name name

	std::string searching = "\n[ Searching palindromes in " + file_name + " ]\n";
	std::cout << searching;

	std::string line; // line of infile

	int aux = 1; // aux variable that represents rows for the file inputed

	while (std::getline(infile, line)) // gets a line in line variable
	{
		std::vector<std::string> line_ans = detectPalindrome(line, aux);

		if (line_ans.size() == 3) // beginning, ending, and result strings
		{
			if (line_ans[0].size() > 1)
			{
				KMPSearchNoLogs(line_ans[0], line, aux);
			}
		}

		aux++;
	}
}

void solutionSecondProblem(std::vector<std::string> files)
{
	std::string greetings = "| --- Start searching for palindromes --- | \n";

	std::cout << greetings;

	for (auto &file_name : files) // for file_name in files
	{
		findPalindromeInFile(file_name); // passes file_name to read
	}
}

#endif
