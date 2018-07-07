/**
 * @file
 * @brief Some functions to make things easier
 *
 * @author Lukas Deutscher
 * @date 08.12.2017
 */

#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <string>

std::vector<std::string> StrSplitFirst(const std::string &Str, const std::string Delimiter);
std::vector<std::string> StrSplit(const std::string &Str, const std::string &Delimiter);
std::string StrTrim(std::string Str);
std::string GetOsString();

#endif
