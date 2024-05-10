#include <iostream>
#include <sstream>
#include "Helper.h"

using namespace std;

void Helper::printMainMenu(bool isAdmin)
{
	std::cout << "Main Menu" << std::endl;
	std::cout << "    1. Display Meal Options" << std::endl;
	std::cout << "    2. Purchase Meal" << std::endl;
	std::cout << "    3. Save and Exit" << std::endl;
	
	if (isAdmin)
	{
		std::cout << "Administrator-Only Menu:" << std::endl;
		std::cout << "    4. Add Food" << std::endl;
		std::cout << "    5. Remove Food" << std::endl;
		std::cout << "    6. Display Balance" << std::endl;
		std::cout << "    7. Display Balance" << std::endl;
	}
}

int Helper::requestMenuSelection(bool isAdmin)
{
	if (isAdmin)
	{
		cout << "Select your option (1-7): ";
	}
	else
	{
		cout << "Select your option (1-3): ";
	}

	string input;
	getline(cin, input);

	if (input == "Exit")
		return 3;

	if (isNumber(input))
		return stoi(input);
	else
		return -1;
}

bool Helper::isNumber(string s)
{
	string::const_iterator it = s.begin();
	char dot = '.';
	int nb_dots = 0;
	while (it != s.end())
	{
		if (*it == dot)
		{
			nb_dots++;
			if (nb_dots > 1)
			{
				return !s.empty() && s[0] != dot && it == s.end();
			}
		}
		else if (!isdigit(*it))
		{
			return !s.empty() && s[0] != dot && it == s.end();
		}

		++it;
	}
}
