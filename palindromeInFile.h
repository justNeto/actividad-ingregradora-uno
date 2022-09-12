#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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


void detectPalindrome(std::string line, int aux)
{
	// "asd anna asd" case odd
	// "asd ana asd" case odd
	/* line = pre_process(line); */
	line = pre_process(line);

	int size = line.length();
	int t_arr[size] = {0};

	std::cout << "| ---- Line value: " << line << " ---- |\n\n";

	int center = 0;
	int right = 0;

	for (int i = 0; i < size; i++)
	{
		std::cout << "| --- i val " << i << " --- |\n";

		int mirror_i = 2*center - i;
		std::cout << "Mirror val: " << mirror_i << "\n";

		if (right > i)
		{
			t_arr[i] = minimized_values(right - i, t_arr[mirror_i]);
		}
		else
		{
			std::cout << "Setting value 0 in current index " << i << "\n";
			t_arr[i] = 0;
		}

		while (true)
		{
			if ((line[i + i + t_arr[i]] == line[i - 1 - t_arr[i]]))
			{
				std::cout << "Still finding mirrors\n";
				t_arr[i] += 1;
				continue;
			}
			else
			{
				std::cout << "Not a mirror found\n";
				break;
			}

			break;
		}

		std::cout << "After not founding a mirror.\n";
		std::cout << "I value: " << i << "\n";
		std::cout << "t_arr[i] val: " << t_arr[i] << "\n";
		std::cout << "right: " << right << "\n";

		if (i + t_arr[i] > right)
		{
			std::cout << "Changing center mirror\n";
			center = i;
			right = i + t_arr[i];
		}
	}

	int biggest_array_value = max_index(t_arr, size);
	int bgv_index = getIndex(biggest_array_value, t_arr, size);

	prtArr(t_arr, size);

	std::cout << "Biggest value in array: " << biggest_array_value << "\n";
	std::cout << "Corresponding index: " << biggest_array_value << "\n";

//	print (string[c - r : c + r].replace("#",""))
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
