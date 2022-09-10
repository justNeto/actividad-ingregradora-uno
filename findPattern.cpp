#include "genTxtFiles.h"
#include <vector>

bool verbose;

void prtVersion()
{
      std::cout << "1.0.0\n";
}

void prtHelp()
{
	std::cout << "Usage: findPattern [OPTIONS] ... [FILE] ... \n\n";

	std::cout << "Finds a certain pattern on a file and points at the index it can be found.\n\n";
	std::cout << "Use the following options for searching patterns in files.\n";
      std::cout << "  -f, --file			search this file for the pattern. Can specify multiple files.\n";
      std::cout << "  -p, --pattern			file with the pattern. Can specify multiple patterns.\n";
      std::cout << "  -v, --verbose			prints the program specifics in runtime.\n";
      std::cout << "  -s, --simulate		creates three random files in current directory and searches for two random patterns.\n\n";

	std::cout << "  -h, --help                shows this help menu and exit.\n";
      std::cout << "  --version                 displays current version of script.\n";
}

// Argc: number of arguments including the program name
// Argv: the vector in char ** format
int main(int argc, char ** argv)
{

	// Defining important variables
	std::vector<std::string> files;
	std::vector<std::string> patterns;

	// Boolean to enter input via the terminal
	bool files_inputed = false; // files already were inputted. Cannot input them twice
	bool patterns_inputed = false; // patterns already were inputted. Cannot input them twice
	bool input_files = false; // inputing files
	bool input_patterns = false; // inputting patterns
	bool simulation = false; // inputting patterns

	if (argc == 1) // no opts passed, program was just executed
	{
		prtHelp();
		exit(1);
	}

	for (int i = 1; i < argc; i++)
	{

		if (input_files == true) // if inputing files then pass them to function to pass patterns.
		{
			files_inputed = true;
			files.push_back(argv[i]);
			continue;
		}
		else if (input_patterns == true)
		{
			patterns_inputed = true;
			patterns.push_back(argv[i]);
			continue;
		}


		if ((argv[i] == std::string("-s")) || (argv[i] == std::string("--simulate")))
	      {
			simulation = true;
			break;
	      }

		if ((argv[i] == std::string("-f")) || (argv[i] == std::string("--file")))
	      {
			if (files_inputed == true)
			{
				std::cout << "Files were already inputted. Cannot add more files.\n";
				break;
			}

		      input_patterns = false;
	            input_files = true;

		      continue;
	      }

	      if ((argv[i] == std::string("-p")) || (argv[i] == std::string("--pattern"))) // if file options selected
	      {
			if (patterns_inputed == true)
			{
				std::cout << "Patterns were already inputted. Cannot add more patterns.\n";
				break;
			}

		      input_files = false;
		      input_patterns = true;

		      continue;
	      }

	      if ((argv[i] == std::string("-v")) || (argv[i] == std::string("--verbose"))) // if file options selected
	      {
			verbose = true;

			if (input_files == true) // if you were adding files
			{
				files_inputed = true; // files are already added
			}
			else if (input_patterns == true)
			{
				patterns_inputed = true; // patterns already added
			}
	      }

	      if (argv[i] == std::string ("--version")) // if file options selected
	      {
			prtVersion();
		      exit(0);
	      }

	      if ((argv[i] == std::string ("-h")) || (argv[i] == std::string("--help"))) // if file options selected
	      {
			prtHelp();
			exit(0);
	      }

	      // If not entering a file then some erros has been made
	      std::cout << "Invalid option. Try findPattern -h or findPattern --help for more information.\n";
		exit(1);
	}

	if (simulation == true)
	{
		std::cout << "::- Simulation mode activated: \n";

		genText(20000, "transmission1.txt");
		genText(20000, "transmission2.txt");
		genPattern(3, "mcode1.txt");
		genPattern(3, "mcode2.txt");
		genPattern(3, "mcode3.txt");
	}
}
