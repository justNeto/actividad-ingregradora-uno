#include "genTxtFiles.h"
#include <vector>

bool verbose;

void prtVersion()
{
	std::cout << "1.2.0\n";
}

void prtHelp()
{
	std::cout << "Usage: findPattern [OPTIONS] ... [FILE] ... \n\n";

	std::cout << "Finds a certain pattern on a file and points at the index it can be found.\n\n";
	std::cout << "Use the following options for searching patterns in files.\n";
      std::cout << "  -f, --file						search this file for the pattern. Can specify multiple files.\n";
      std::cout << "  -p, --pattern						file with the pattern. Can specify multiple patterns.\n";
      std::cout << "  -v, --verbose						prints the program specifics in runtime.\n";
      std::cout << "  -s, --simulate					creates three random files in current directory and searches for two random patterns.\n\n";

	std::cout << "Use the following options for generating test random files and patterns.\n";
	std::cout << "  -gf, --generate-files					generate a given number of random files of a given length.  They will be named accordingly.\n";
	std::cout << "  -gp, --generate-patterns				generate a given number of random patterns of a given length. They will be named accordingly.\n\n";

	std::cout << "  -h, --help						shows this help menu and exit.\n";
      std::cout << "  --version						displays current version of script.\n";
}

// Argc: number of arguments including the program name
// Argv: the vector in char ** format
int main(int argc, char ** argv)
{
	// Vectors to save the names of the files and patterns the program will later use
	std::vector<std::string> files; // existing files
	std::vector<std::string> patterns; // existing patterns
	std::vector<std::string> gen_files; // create files
	std::vector<std::string> gen_patterns; // create patterns

	// Boolean to enter input via the terminal
	bool files_generated = false; // files were already generated
	bool files_inputed = false; // files already were inputted
	bool patterns_inputed = false; // patterns already were inputted
	bool patterns_generated = false; // patterns were already generated

	bool input_files = false; // inputing files
	bool input_patterns = false; // inputting patterns

	bool generate_files = false; // inputting file names to generate
	bool generate_patterns = false; // inputting pattern names to generate

	bool simulation = false; // inputting patterns

	if (argc == 1) // no opts passed, program was just executed
	{
		prtHelp();
		exit(1);
	}

	for (int i = 1; i < argc; i++)
	{

		if (verbose)
		{
			// Print current working option
			if (input_files == true) // if inputing files then pass them to function to pass patterns.
			{
				std::cout << "Option inputting files for solution is working\n";
			}
			else if (input_patterns == true)
			{
				std::cout << "Option inputting patterns for solution is working\n";
			}
			if (generate_files == true) // generating files
			{
				std::cout << "Option generating files for solution is working\n";
			}
			else if (generate_patterns == true) // generating patterns
			{
				std::cout << "Option generating patterns for solution is working\n";
			}
		}

		if (input_files == true) // if inputing files then pass them to function to pass patterns.
		{
			files_inputed = true; // will no longer be able to use this option

			if (argv[i][0] == std::string("-"))
			{
				std::cout << "Another option will be used. Exiting current one";
				continue;
			}
			else
			{
				files_inputed = true; // will no longer be able to add more inputed files
				files.push_back(argv[i]);
				continue;
			}
		}
		else if (input_patterns == true)
		{
			patterns_inputed = true;
			patterns.push_back(argv[i]);
			continue;
		}

		if (generate_files == true) // generating files
		{
			files_generated = true;
			gen_files.push_back(argv[i]);
			continue;
		}
		else if (generate_patterns == true) // generating patterns
		{
			patterns_generated = true;
			gen_patterns.push_back(argv[i]);
			continue;
		}

		// Generate new files of random characters
		if ((argv[i] == std::string("-gf")) || (argv[i] == std::string("--generate-files")))
	      {
			if (files_generated == true)
			{
				std::cout << "Files were already generated. Cannot generate more files.\n";
				break;
			}

			generate_files = true;
			continue;
	      }

		// Generate new files of random patterns
		if ((argv[i] == std::string("-gp")) || (argv[i] == std::string("--generate-patterns")))
	      {
			if (patterns_generated == true)
			{
				std::cout << "Patterns were already generated. Cannot generate more files.\n";
				break;
			}

			generate_patterns = true;
			continue;
	      }

		// Use files to solve the problems
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

		// Use patterns to solve the problems
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

		// Start simulation mode
		if ((argv[i] == std::string("-s")) || (argv[i] == std::string("--simulate")))
	      {
			simulation = true; //automatically ignore any other commands and go straight to simulation
			break;
	      }

		// Activate verbose mode
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

			continue;
	      }

		// Show current version of proyect
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
		if (verbose) std::cout << "| --- [Simulation mode activated] --- | \n";
		if (verbose) std::cout << "In simulation mode, default values will be used for file length and pattern length.\n";

		if (verbose) std::cout << "::- Creating files\n";

		genText(20000, "transmission1.txt");
		genText(20000, "transmission2.txt");
		genPattern(5, "mcode1.txt");
		genPattern(5, "mcode2.txt");
		genPattern(5, "mcode3.txt");

		if (verbose) std::cout << "::- Files created\n";

		// Once the files are created, the solutions for the three problems will run

		if (verbose) std::cout << "::- Solution for the first problem:\n";
		// Solution one

		if (verbose) std::cout << "::- Solution for the second problem:\n";
		// Solution two

		if (verbose) std::cout << "::- Solution for the third problem:\n";
		// Solution three

		if (verbose) std::cout << "::- Simulation mode terminated.\n";
		exit(0);
	}

	if (files_generated) //
	{
		if (verbose)
		{
			std::cout << "Will generate this files: \n";

			for (auto const &names : gen_files)
			{
				std::cout << names << "\n";
			}
		}
	}

	if (files_inputed)
	{
		if (verbose)
		{
			std::cout << "Will use this files to find a solution: \n";

			for (auto const &names : files)
			{
				std::cout << names << "\n";
			}
		}
	}

	if (patterns_generated)
	{
		if (verbose)
		{
			std::cout << "Will generate this patterns: \n";

			for (auto const &names : gen_patterns)
			{
				std::cout << names << "\n";
			}
		}
	}

	if (patterns_inputed)
	{
		if (verbose)
		{
			std::cout << "Will use this patterns to find solution: \n";

			for (auto const &names : patterns)
			{
				std::cout << names << "\n";
			}
		}
	}

}
