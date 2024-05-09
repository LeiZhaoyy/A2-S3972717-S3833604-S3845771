#include <iostream>
#include "LinkedList.h"
#include "Helper.h"

int main(int argc, char** argv)
{
	//if (argc < 3)
	//{
	//	std::cerr << "Usage: " << argv[0] << " <foodsfile> <coinsfile>" << std::endl;
	//	return EXIT_FAILURE;
	//}

	//// Extract filenames from command line arguments
	//std::string foodsFile = argv[1];
	//std::string coinsFile = argv[2];

	//// Create an instance of the LinkedList class
	//LinkedList foodList;

	//// Load food data from the specified file
	//foodList.loadFromFile(foodsFile);

	while (true)
	{
		Helper::printMainMenu();

		switch (Helper::requestMenuSelection())
		{
			case 1:
				break;

			case 2:
				break;

			case 4:
				break;

			case 5:
				break;

			case 6:
				break;

			case 7:
				break;

			default:
				return EXIT_SUCCESS;
		}
	}
}
