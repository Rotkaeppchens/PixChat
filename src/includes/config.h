/**
 * @file
 * @brief The public header for the config module
 *
 * @author Lukas Deutscher
 * @date 20.12.2017
 */

#include <string>
#include <vector>

bool LoadConfig(const std::string &FileName, const std::string &ConfigDelimiter, const std::string &CommentChar);
void DumpConfigEntries();
bool ConfigKeyExists(const std::string &ConfigName);

/**
 * The functions are all read functions for different types.
 */
std::string ReadConfigString(const std::string &ConfigName);
int         ReadConfigInt   (const std::string &ConfigName);
double      ReadConfigDouble(const std::string &ConfigName);

std::vector<std::string>    ReadConfigStringVec (const std::string &ConfigName, const std::string &Delimiter);
std::vector<int>            ReadConfigIntVec    (const std::string &ConfigName, const std::string &Delimiter);
