#include "genTxtFiles.h"
#include "findPatternInFile.h" // solution first problem
#include "palindromeInFile.h" // solution second problem
#include "commonSubFiles.h" // solution third problem
#include <vector>

bool verbose;

// Prints the current development version
void prtVersion()
{
	std::cout << "3.2.0\n";
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
	std::cout << "  -ffp, --files-first-problem FILE1, FILE2 ...\n";
	std::cout << "       Specify the files that will be used to find a pattern. -f or --file option must be used along this one.\n\n";

	std::cout << "  -pfp, --patterns-first-problem	FILE1, FILE2 ...\n";
	std::cout << "       Specify the pattern files that will be used. -p or --pattern option must be used along this one.\n\n";

	std::cout << ":: < Second problem > :: \n";
	std::cout << "Use the following options for detecting malicious palindromes in files.\n";
	std::cout << "  -fsp --files-second-problem FILE1, FILE2 ...\n";
	std::cout << "       Specify the files that will be used to find malicious code inside them. \n\n";

	std::cout << ":: < Third problem > :: \n";
	std::cout << "Use the following options for detecting malicious palindromes in files.\n";
	std::cout << "  -ftp --files-third-problem FILE1, FILE2 ...\n";
	std::cout << "       Specify the files that will be used to find malicious code inside them. \n\n";

	std::cout << ":: < Simulation mode > :: \n";
	std::cout << "  -s, --simulate					Creates three random files in current directory and solves the problems using them.\n\n";

	std::cout << ":: < Other opts > :: \n";
	std::cout << "  -v, --verbose						prints the program specifics in runtime.\n";
	std::cout << "  -h, --help						shows this help menu and exit.\n";
	std::cout << "  -l, --logs						generates log for first problem.\n";
	std::cout << "  --version						displays current version of script.\n";
}

// Argc: number of arguments including the program name
// Argv: the vector in char ** format
int main(int argc, char ** argv)
{
	// Vectors to save the names of the files and patterns the program will later use
	std::vector<std::string> files; // existing files
	std::vector<std::string> files_second; // existing files
	std::vector<std::string> files_third; // existing files
	std::vector<std::string> patterns; // existing patterns
	std::vector<std::string> gen_files; // create files
	std::vector<std::string> gen_patterns; // create patterns

	// Boolean opts
	bool file_opt = false;
	bool files_second_opt = false;
	bool files_third_opt = false;
	bool pattern_opt = false;
	bool gen_file_opt = false;
	bool gen_pattern_opt = false;

	// Boolean control variables
	bool patterns_inputed = false;
	bool patterns_generated = false;
	bool files_generated = false;
	bool files_inputed = false;
	bool files_second_inputed = false;
	bool files_third_inputed = false;

	// Boolean extras
	bool simulation = false; // inputting patterns
	bool logs = false; // inputting patterns

	// Some defaults
	int default_text_size = 1000000;
	int default_pattern_size = 5;

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

		if ((files_second_opt == true) && (files_second_inputed == false))  // if file_second_opt active and files_second_inputed still false
		{
			// New opt in argv[aux] detected
			if (argv[aux][0] == '-')
			{
				files_second_inputed = true; // can no longer add into this opt
				continue;
			}

			files_second.push_back(argv[aux]);
			aux++;

			continue;
		}

		if ((files_third_opt == true) && (files_third_inputed == false))  // if file_third_opt active and files_third_inputed still false
		{
			// New opt in argv[aux] detected
			if (argv[aux][0] == '-')
			{
				files_third_inputed = true; // can no longer add into this opt
				continue;
			}

			files_third.push_back(argv[aux]);
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

		// Use files to solve first problem
		if ((argv[aux] == std::string("-ffp")) || (argv[aux] == std::string("--files-first-problem")))
	      {
	            file_opt = true;
			aux++;
		      continue;
	      }

		// Use patterns to solve first problem
	      if ((argv[aux] == std::string("-pfp")) || (argv[aux] == std::string("--patterns-first-problem")))
	      {
		      pattern_opt = true; // selects the option to work with
			aux++;
		      continue;
	      }

		// Files for the second problem
	      if ((argv[aux] == std::string("-fsp")) || (argv[aux] == std::string("--files-second-problem")))
	      {
			files_second_opt = true; // selects the option to work with
			aux++;
		      continue;
	      }

	      if ((argv[aux] == std::string("-ftp")) || (argv[aux] == std::string("--files-third-problem")))
	      {
			files_third_opt = true; // selects the option to work with
			aux++;
		      continue;
	      }

		// Start simulation mode
		if ((argv[aux] == std::string("-s")) || (argv[aux] == std::string("--simulate")))
	      {
			simulation = true; //automatically ignore any other commands and go straight to simulation
			files.clear();
			patterns.clear();
			break;
	      }

		// Activate verbose mode
	      if ((argv[aux] == std::string("-v")) || (argv[aux] == std::string("--verbose"))) // if file options selected
	      {
			verbose = true;
			aux++;
			continue;
	      }

	      if ((argv[aux] == std::string("-l")) || (argv[aux] == std::string("--logs"))) // if logs active
	      {
			logs = true;
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

		// Creating vectors to find solution
		std::vector<std::string> files_vector;
		std::vector<std::string> patterns_vector;

		// Creating default files
		genText(default_text_size, "transmission1.txt");
		genText(default_text_size, "transmission2.txt");
		genPattern(default_pattern_size, "mcode1.txt");
		genPattern(default_pattern_size, "mcode2.txt");
		genPattern(default_pattern_size, "mcode3.txt");

		// Pushing transmission vectors
		files.push_back("transmission1.txt");
		files.push_back("transmission2.txt");

		// Pushing mcode patterns
		patterns.push_back("mcode1.txt");
		patterns.push_back("mcode2.txt");
		patterns.push_back("mcode3.txt");

		if (verbose) std::cout << "::- Vectors & files created\n";

		// Once the files are created, the solutions for the three problems will run

		if (verbose) std::cout << "::- Solution for the first problem:\n";
		// Solution one
		solutionFirstProblem(files, patterns, logs);

		if (verbose) std::cout << "::- Solution for the second problem:\n";
		// Solution two
		solutionSecondProblem(files);

		if (verbose) std::cout << "::- Solution for the third problem:\n";
		// Solution three
		solutionThirdProblem(files);

		if (verbose) std::cout << "::- Simulation mode terminated.\n";
		exit(0);
	}

	// Code to generate random files
	if (gen_file_opt)
	{
		if (verbose) std::cout << "Generating files.\n";

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

		// If default is two, using <N> and <M> options
		if (gen_files.size() == 2)
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

	// Code to validate if files exist
	if (file_opt)
	{
		if (files.empty())
		{
			std::cout << "\n::-Missing arguments. Try findPattern -h or findPattern --help for more information. \n";
			exit(1);
		}

		// Else use the files
		for (auto &file_name : files)
		{
			if (verbose) std::cout << "Searching for file : " << file_name << "\n";

			std::ifstream infile(file_name); // create ifstream var to read from

			if(infile.fail())
			{
				if (verbose) std::cout << "File does not exist\n";
				std::cout << "\n::-Inputted '" << file_name << "' file does not exist. Ignoring it and going to the next file.\n\n";

				continue;
			}

			if (verbose) std::cout << "File does exist\n";
		}
	}

	// Code to validate if files exist
	if (files_second_opt)
	{
		if (files_second.empty())
		{
			std::cout << "\n::-Missing arguments. Try findPattern -h or findPattern --help for more information. \n";
			exit(1);
		}

		// Else use the files
		for (auto &file_name : files_second)
		{
			if (verbose) std::cout << "Searching for file : " << file_name << "\n";

			std::ifstream infile(file_name); // create ifstream var to read from

			if(infile.fail())
			{
				std::cout << "\n::-Error. Inputted '" << file_name << "' file does not exist.";
				exit(0);
			}

			if (verbose) std::cout << "File does exist\n";
		}
	}

	if (files_third_opt)
	{
		if ((files_third.empty()) || (files_third.size() == 1))
		{
			std::cout << "\n::-Missing arguments. Try findPattern -h or findPattern --help for more information. \n";
			exit(1);
		}

		if (files_third.size() == 2)
		{
			std::ifstream infile(files_third[0]); // create ifstream var to read from

			if(infile.fail())
			{
				std::cout << "\n::-Error. Inputted '" << files_third[0] << "' file does not exist.";
				exit(0);
			}

			std::ifstream infileTwo(files_third[1]); // create ifstream var to read from

			if(infileTwo.fail())
			{
				std::cout << "\n::-Error. Inputted '" << files_third[1] << "' file does not exist.";
				exit(0);
			}

			if (verbose) std::cout << "Both files exist\n";
		}

		if (files_third.size() > 2)
		{
			std::cout << "\n::- Invalid syntax. Try findPattern -h or findPattern --help for more information. \n";
			exit(0);
		}

	}

	// Code to generate random patterns
	if (gen_pattern_opt)
	{
		if (verbose) std::cout << "Generating patterns.\n";

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

		// If default is two, using <N> and <M> options
		if (gen_patterns.size() == 2)
		{
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

	// Code to validate if patterns exist
	if (pattern_opt)
	{
		if (patterns.empty())
		{
			std::cout << "\n::-Missing arguments. Try findPattern -h or findPattern --help for more information. \n";
			exit(1);
		}

		// Else use the patterns
		for (auto &file_name : patterns)
		{
			if (verbose) std::cout << "Searching for pattern : " << file_name << "\n";

			std::ifstream infile(file_name); // create ifstream var to read from

			if(infile.fail())
			{
				std::cout << "\n::-Error. Inputted '" << file_name << "' file does not exist.";
				exit(0);
			}

			if (verbose) std::cout << "Pattern file does exist\n\n";
		}
	}

	// If both patterns and files exist, pass those vectors to function 1.
	if ((files.size() != 0) && (patterns.size() != 0) && (file_opt) && (pattern_opt)) // if file_opt and pattern_opt selected
	{
		// Solve first problem function
		solutionFirstProblem(files, patterns, logs);
	}
	else if ((files.size() != 0) && patterns.empty())
	{
			std::cout << "::-Missing arguments. -pfp or --patterns-first-problem files should also be specified.\n";
			exit(1);
	}
	else if (files.empty() && (patterns.size() != 0)) // if files empty but patterns not
	{
			std::cout << "::-Missing arguments. -ffp or --files-first-problem files should also be specified.\n";
			exit(1);
	}


	if ((files_second.size() != 0) && (files_second_opt)) // if file_opt and pattern_opt selected
	{
		// Solve first problem function
		solutionSecondProblem(files_second);
	}

	if ((files_third.size() != 0) && (files_third_opt)) // if file_opt and pattern_opt selected
	{
		// Solve first problem function
		solutionThirdProblem(files_third);
	}
}
