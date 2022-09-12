#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define ARR_SIZE(type) \
	(sizeof(type) / sizeof (int))

std::string pre_process(std::string line)
{
	// Add $ at the begginning and @ at the end
	/* line = "$" + line + "@"; */
	/* line = line + "#"; */

	for (int i = 0; i < line.length(); i += 2)
	{
		line.insert(i, "#");
	}

	line.insert(line.length(), "#");

	return line;
}

double minized_values(double val_one, double val_two)
{
	(val_one < val_two) ? val_one : val_two
}

int max_index(t_arr, size)
{
	int aux = 0;

	for (int i = 0; i < size; i++)
	{
		if (t_arr[i] > aux)
		{
			aux = t_arr;
		}
	}

	return aux;
}

int getIndex(biggest, t_arr, size)
{
	for (int i = 0; i < size; i++)
	{
		if (t_arr[i] == biggest)
		{
			return i;
		}
	}
}


void detectPalindrome(std::string line, int aux)
{
	// "asd anna asd" case odd
	// "asd ana asd" case odd
	/* line = pre_process(line); */
	line = pre_process(line);

	int size = line.length();
	int t_arr[size] = {0};

	int center, right = 0;

	for (int i = 0; i < size; i++)
	{
		int mirror_i = 2*center - i;
		std::cout << "mirror: " << mirror_i << "\n";

		if (right > i)
		{
			t_arr[i] = minimize_values(right - i, t_arr[mirror_i]);
		}
		else
		{
			t_arr[i] = 0;
		}

		try
		{
			while (line[i + i + t_arr[i]] == line[i - 1 - t_arr[i]])
			{
				t_arr[i] += 1;
			}
		}
		catch
		{
			;
		}

		if (i + t_arr[i] > right)
		{
			center = i;
			right = i + t_arr[i];
		}
	}

	int biggest_array_value = max_index(t_arr, size);
	int bgv_index = getIndex(biggest_array_value, t_arr, size);

	print (string[c - r : c + r].replace("#",""))
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
		detectPalindrome(line, aux);
		exit(0);
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
