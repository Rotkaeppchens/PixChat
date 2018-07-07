/**
 * @file
 * @brief The function definitions for the helper funcs
 *
 * @author Lukas Deutscher
 * @date 08.12.2017
 */

#include "../includes/utility.h"    // The header file for the utilities
#include <iostream>     // The basic io stream
#include <string>       // The string type
#include <vector>       // The vector type
#include <sstream>      // The string stream
#include <cstring>      // The cstring lib

/**
 * @brief A function to split strings
 *
 * This function takes a string and a delimiter and splits the string,
 * on the first occurence.
 * Exclusiv the Delimiter
 *
 * If the delimiter was not found it returns an vector with the string
 * as the only member.
 *
 * @param Str The string to split
 * @param Delimiter The delimiter with whicht the string shoudl be split
 * @return vector<string> The vector with the splitted strings
 */
std::vector<std::string> StrSplitFirst(const std::string &Str, const std::string Delimiter)
{
    std::vector<std::string> SplitVec;

    auto DelPosition = Str.find(Delimiter);

    if (DelPosition == std::string::npos) {
        SplitVec.push_back(Str);

        return SplitVec;
    }

    std::string FirstPart = Str.substr(0, DelPosition);
    std::string SecondPart = Str.substr(DelPosition + Delimiter.size());

    SplitVec.push_back(FirstPart);
    SplitVec.push_back(SecondPart);

    return SplitVec;
}

/**
 * @brief Takes a string and a delimiter and splits the string on the delimiter
 *
 * If the the delimiter isnt in the string it returns a vector with the string as first part.
 *
 * @param Str The string to split.
 * @param Delimiter The Delimiter to split on
 * @return vector<string> The vector with the string parts
 */
std::vector<std::string> StrSplit(const std::string &Str, const std::string &Delimiter)
{
    std::vector<std::string> SplitVec;

    std::string LastPart = Str;
    std::size_t DelPos = 0;

    while (
        (DelPos = LastPart.find(Delimiter)) != std::string::npos
    ) {
        std::string Part = LastPart.substr(0, DelPos);
        SplitVec.push_back(Part);

        LastPart = LastPart.substr(DelPos + 1, LastPart.length());
    }

    SplitVec.push_back(LastPart);

    return SplitVec;
}

/**
 * @brief Trims the given string
 *
 * Takes a string and and returns it without the leading/trailing spaces.
 *
 * @warning Function not functional.
 * :TODO: Implement function to trim strings.
 *
 * @param Str The string to trim
 * @return string The trimmed string.
 */
std::string StrTrim(std::string Str)
{
    return Str;
}

/**
 * @brief Gets the name of the operating system as string
 *
 * :TODO: Find better solution to filter the operating system.
 *
 * @return string The name of the operating system.
 */
std::string GetOsString()
{
    #ifdef _WIN32
    return "Windows";
    #elif _WIN64
    return "Windows";
    #elif __unix || __unix__
    return "Unix";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #else
    return "Other";
    #endif
}
