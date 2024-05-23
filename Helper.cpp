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

// int Helper::requestMenuSelection(bool isAdmin)
// {
//     int selection = -1; // Initialize selection variable

//     if (isAdmin)
//     {
//         cout << "Select your option (1-7): ";
//     }
//     else
//     {
//         cout << "Select your option (1-3): ";
//     }

//     string input;
//     getline(cin, input);

//     if (input == "Exit")
//     {
//         selection = 3;
//     }
//     else if (isNumber(input))
//     {
//         selection = stoi(input);
//     }

//     return selection; // Return the final selection value
// }

// bool Helper::isNumber(string s)
// {
//     string::const_iterator it = s.begin();
//     char dot = '.';
//     int nb_dots = 0;
//     bool validNumber = true; // Assume it's a valid number initially

//     while (it != s.end() && validNumber) // Check for both end of string and validity
//     {
//         if (*it == dot)
//         {
//             nb_dots++;
//             if (nb_dots > 1)
//             {
//                 validNumber = !s.empty() && s[0] != dot && it == s.end();
//             }
//         }
//         else if (!isdigit(*it))
//         {
//             validNumber = !s.empty() && s[0] != dot && it == s.end();
//         }

//         ++it;
//     }

//     return validNumber;
// }