#pragma once
class Helper
{
public:
    /// <summary>
    /// Print the top level menu
    /// </summary>
    static void printMainMenu(bool isAdmin = false);

    /// <summary>
    /// Request the user for a valid input. Any non-int input will be parsed as -1
    /// </summary>
    static int requestMenuSelection(bool isAdmin = false);

    /**
     * @brief Check whether the given string is an integer or a float
     *
     * @param s The given string
     * @return true if the string is an integer or a float
     * @return false if the string is neither an integer nor a float
     */
    static bool isNumber(std::string s);
};