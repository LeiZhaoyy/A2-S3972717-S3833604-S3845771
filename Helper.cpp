#include <iostream>
#include <sstream>
#include "Helper.h"

using namespace std;

void Helper::printMainMenu(bool isAdmin)
{
	std::cout << "Main Menu:" << std::endl;
	std::cout << "    1. Display Meal Options" << std::endl;
	std::cout << "    2. Purchase Meal" << std::endl;
	std::cout << "    3. Save and Exit" << std::endl;
	
	// if (isAdmin)
	// {
		std::cout << "Administrator-Only Menu:" << std::endl;
		std::cout << "    4. Add Food" << std::endl;
		std::cout << "    5. Remove Food" << std::endl;
		std::cout << "    6. Display Balance" << std::endl;
		std::cout << "    7. Abort Program" << std::endl;
	//}
}

