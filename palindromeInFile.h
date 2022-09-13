#ifndef FND_PALINDROME
#define FND_PALINDROME

#include "findPatternInFile.h"
#include <string>
#include <algorithm>
void prtArr(int arr[], int size) {
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


/* void detectPalindrome(std::string line, int aux) */
std::string detectPalindrome(std::string line, int aux)
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


		while (true)
		{
			int left_boundary = i + 1 + t_arr[i];
			int right_boundary = i - 1 - t_arr[i];

			if ((left_boundary < 0) || (right_boundary < 0) || (left_boundary > size) || (right_boundary > size)) // this means out of bounce
			{
				break;
			}

			if (line[left_boundary] == line[right_boundary])
			{
				t_arr[i] += 1;
			}
			else
			{
				break;
			}
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

	result.erase(std::remove(result.begin(), result.end(), '#'), result.end());

	return result;

}

void findPalindromeInFile(std::string file_name)
{
	std::ifstream infile(file_name); // read current file with file_name name
	std::string searching = "\n[ Searching palindromes in " + file_name + " ]\n";
	std::cout << searching;

	std::string line;

	int longestPalindromeSize = 0;
	std::string longestPalindromeString;
	std::string palindromeLine;

	int aux = 1; // aux variable that represents rows for the file inputed
	int longestPalindromeAux;

	while (std::getline(infile, line)) // gets a line in line variable
	{
		std::string currPalindrome = detectPalindrome(line, aux);

		if (currPalindrome.length() > longestPalindromeSize)
		{
			longestPalindromeString = currPalindrome;
			longestPalindromeSize = currPalindrome.length();
			palindromeLine = line;
			longestPalindromeAux = aux;
		}

		aux++;
	}

	KMPSearchNoLogs(longestPalindromeString, palindromeLine, longestPalindromeAux);
	std::cout << " (with a size of " << longestPalindromeSize << ")\n";
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
