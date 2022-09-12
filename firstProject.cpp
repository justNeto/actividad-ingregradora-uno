#include "genTxtFiles.h"
#include <vector>

bool verbose;

// Prints the current development version
void prtVersion()
{
	std::cout << "2.1.0\n";
}

// Prints the help usage of the program
void prtHelp()
{
	std::cout << "Usage: firstProject [OPTIONS] ... [FILE] ... \n\n";

	std::cout << "Use the following options for generating test random files and patterns.\n\n";
	std::cout << "  -gf, --generate-files <N> <M>\n";
	std::cout << "       Generate a number of <N> random files with a length of <M>. They will be named automatically as transmission<0..N>.\n";
	std::cout << "       If no <M> value selected, default file size of length 10000 will be used.\n\n";
	std::cout << "  -gp, --generate-patterns <N> <M>\n";
	std::cout << "       Generate a number of <N> random patterns with a length of <M>. They will be automatically as mcode<0...N>.\n";
	std::cout << "       If no <M> value selected, default file size of length 10 will be used.\n\n";

	std::cout << ":: < First problem > :: \n";
	std::cout << "Use the following options for searching patterns in files.\n";
	std::cout << "  -f, --file FILE1, FILE2 ...\n";
	std::cout << "       Specify the files that will be used to find a pattern. -f or --file option must be used along this one.\n\n";

	std::cout << "  -p, --pattern	FILE1, FILE2 ...\n";
	std::cout << "       Specify the pattern files that will be used. -p or --pattern option must be used along this one.\n\n";

	std::cout << ":: < Simulation mode > :: \n";
	std::cout << "  -s, --simulate					Creates three random files in current directory and solves the problems using them.\n\n";

	std::cout << ":: < Other opts > :: \n";
	std::cout << "  -v, --verbose						prints the program specifics in runtime.\n";
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

	// Opts
	bool file_opt = false;
	bool pattern_opt = false;
	bool gen_file_opt = false;
	bool gen_pattern_opt = false;

	// Control vars
	bool patterns_inputed = false;
	bool patterns_generated = false;
	bool files_generated = false;
	bool files_inputed = false;

	bool simulation = false; // inputting patterns

	// Some defaults
	int default_text_size = 10000;
	int default_pattern_size = 10;

	if (argc == 1) // no opts passed, program was just executed
	{
		prtHelp();
		exit(1);
	}

	int aux = 1;

	// Loop to get the correct opts for the program
	while (aux != argc)
	{
		if ((file_opt == true) && (files_inputed == false))  // if file_opt active and files_inputed still false
		{
			// New opt in argv[aux] detected
			if (argv[aux][0] == '-')
			{
				files_inputed = true; // can no longer add into this opt
				continue;
			}

			files.push_back(argv[aux]);
			aux++;

			continue;
		}

		if ((pattern_opt == true) && (patterns_inputed == false))  // if file_opt active and files_inputed still false
		{
			if (argv[aux][0] == '-')
			{
				patterns_inputed = true; // can no longer add into this opt
				continue;
			}

			patterns.push_back(argv[aux]);
			aux++;

			continue;
		}

		if ((gen_file_opt == true) && (files_generated == false))  // if file_opt active and files_inputed still false
		{
			if (argv[aux][0] == '-')
			{
				files_generated = true;
				continue;
			}

			gen_files.push_back(argv[aux]);
			aux++;

			continue;
		}

		if ((gen_pattern_opt == true) && (patterns_generated == false))  // if file_opt active and files_inputed still false
		{
			if (argv[aux][0] == '-')
			{
				patterns_generated = true;
				continue;
			}

			gen_patterns.push_back(argv[aux]);
			aux++;

			continue;
		}

		// Generate new files of random characters
		if ((argv[aux] == std::string("-gf")) || (argv[aux] == std::string("--generate-files")))
	      {
			gen_file_opt = true; // selects the option to work with
			aux++;
			continue;
	      }

		// Generate new files of random patterns
		if ((argv[aux] == std::string("-gp")) || (argv[aux] == std::string("--generate-patterns")))
	      {
			gen_pattern_opt = true; // selects the option to work with
			aux++;
			continue;
	      }

		// Use files to solve the problems
		if ((argv[aux] == std::string("-f")) || (argv[aux] == std::string("--file")))
	      {
	            file_opt = true;
			aux++;
		      continue;
	      }

		// Use patterns to solve the problems
	      if ((argv[aux] == std::string("-p")) || (argv[aux] == std::string("--pattern"))) // if file options selected
	      {
		      pattern_opt = false; // selects the option to work with
			aux++;
		      continue;
	      }

		// Start simulation mode
		if ((argv[aux] == std::string("-s")) || (argv[aux] == std::string("--simulate")))
	      {
			simulation = true; //automatically ignore any other commands and go straight to simulation
			aux++;
			break;
	      }

		// Activate verbose mode
	      if ((argv[aux] == std::string("-v")) || (argv[aux] == std::string("--verbose"))) // if file options selected
	      {
			verbose = true;
			aux++;
			continue;
	      }

		// Show current version of proyect
	      if (argv[aux] == std::string ("--version")) // if file options selected
	      {
			prtVersion();
		      exit(0);
	      }

	      if ((argv[aux] == std::string ("-h")) || (argv[aux] == std::string("--help"))) // if file options selected
	      {
			prtHelp();
			exit(0);
	      }

	      // If not entering a file then some erros has been made
	      std::cout << "Invalid option. Try findPattern -h or findPattern --help for more information.\n";
		exit(1);
	}

	// Checking all the opts
	if (simulation == true)
	{
		if (verbose) std::cout << "| --- [Simulation mode activated] --- | \n";
		if (verbose) std::cout << "In simulation mode, default values will be used for file length and pattern length.\n";
		if (verbose) std::cout << "::- Creating files\n";

		// Creating default files
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

	// Code to generate random files
	if (gen_file_opt)
	{
		if (gen_files.empty())
		{
			std::cout << "\n::-Missing arguments. Try findPattern -h or findPattern --help for more information. \n";
			exit(1);
		}

		// If default is only one, then only number of files selected. Thus, using default size.
		if (gen_files.size() == 1)
		{
			// Generate all the files with default value
			if (verbose) std::cout << "Generating " << gen_files[0] << " files.\n";

			for (int i = 1; i < std::stoi(gen_files[0]) + 1; i++)
			{
				std::string aux = std::to_string(i);
				std::string result = "transmission" + aux + ".txt";

				genText(default_text_size, result);
			}
		}

		if (gen_files.size() == 2) // if default is only one, then only number of files selected. Thus, using default size.
		{
			// Generate all the files with default value
			if (verbose) std::cout << "Generating " << gen_files[0] << " files of length " << gen_files[1] << ".\n"; // number of files

			for (int i = 1; i < std::stoi(gen_files[0]) + 1; i++)
			{
				std::string aux = std::to_string(i);
				std::string result = "transmission" + aux + ".txt";

				int aux2 = std::stoi(gen_files[1]);

				genText(aux2, result);
			}
		}
		// After inputing opts process them
		if (gen_files.size() > 2)
		{
			std::cout << "\n::- Invalid syntax. Try findPattern -h or findPattern --help for more information. \n";
			exit(1);
		}

	}

	// Code to solve the problems with existing files
	if (file_opt)
	{
		if (files.empty())
		{
			std::cout << "\n::-Missing arguments. Try findPattern -h or findPattern --help for more information. \n";
			exit(1);
		}
	}

	// Code to generate random patterns
	if (gen_pattern_opt)
	{
		std::cout << "Generating patterns\n";

		// If empty then delete the pattern.
		if (gen_patterns.empty())
		{
			std::cout << "\n::-Missing arguments. Try findPattern -h or findPattern --help for more information. \n";
			exit(1);
		}

		// If default is only one, then only number of files selected. Use default size
		if (gen_patterns.size() == 1)
		{
			// Generate all the files with default value
			if (verbose) std::cout << "Generating " << gen_patterns[0] << " files.\n";

			for (int i = 1; i < std::stoi(gen_patterns[0]) + 1; i++)
			{
				std::string aux = std::to_string(i);
				std::string result = "mcode" + aux + ".txt";

				genPattern(default_pattern_size, result);
			}
		}

		// If default is only one, then only number of files selected. Thus, using default size.
		if (gen_patterns.size() == 2)
		{
			std::cout << "Inside the gen_patterns\n";
			// Generate all the files with default value
			if (verbose) std::cout << "Generating " << gen_patterns[0] << " files of length " << gen_patterns[1] << ".\n"; // number of files

			for (int i = 1; i < std::stoi(gen_patterns[0]) + 1; i++)
			{
				std::string aux = std::to_string(i);
				std::string result = "mcode" + aux + ".txt";

				int aux2 = std::stoi(gen_patterns[1]);

				genPattern(aux2, result);
			}
		}

		// After inputing opts process them
		if (gen_patterns.size() > 2)
		{
			std::cout << "\n::- Invalid syntax. Try findPattern -h or findPattern --help for more information. \n";
			exit(1);
		}

	}

	// Code to solve the problems with existing patterns
	if (pattern_opt)
	{
		if (verbose)
		{
			if (patterns.empty())
			{
				std::cout << "\n::-Missing arguments. Try findPattern -h or findPattern --help for more information. \n";
			}
			else
			{
				std::cout << "\n::-Will use this patterns to find solution: \n";

				for (auto const &names : patterns)
				{
					std::cout << names << "\n";
				}
			}
		}
	}
}
