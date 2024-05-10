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

		int option = Helper::requestMenuSelection();

		if (option == 1)
		{

		}
		else if (option == 2)
		{

		}
		else if (option == 3)
		{
			return EXIT_SUCCESS;
		}
		else if (option == 4)
		{

		}
		else if (option == 5)
		{

		}
		else if (option == 6)
		{

		}
		else if (option == 7)
		{

		}
		else if (option == 2)
		{

		}
		else if (option == 2)
		{




		}
	}
}
