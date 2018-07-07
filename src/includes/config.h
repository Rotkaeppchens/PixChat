/**
 * @file
 * @brief The public header for the config module
 *
 * @author Lukas Deutscher
 * @date 20.12.2017
 */

#include <string>

/**
 * @struct ConfigInt3
 *
 * @brief A config struct to hold 3 ints
 */
struct ConfigInt3
{
    int a;
    int b;
    int c;
};

/**
 * @struct ConfigInt4
 *
 * @brief A config struct to hold 4 ints
 */
struct ConfigInt4
{
    int a;
    int b;
    int c;
    int d;
};

bool LoadConfig(const std::string &FileName, const std::string &ConfigDelimiter, const std::string &CommentChar);
void DumpConfigEntries();
bool ConfigKeyExists(const std::string &ConfigName);

/**
 * The functions are all read functions for different types.
 */
std::string ReadConfigString(const std::string &ConfigName);
int         ReadConfigInt   (const std::string &ConfigName);
double      ReadConfigDouble(const std::string &ConfigName);
ConfigInt3* ReadConfigInt3  (const std::string &ConfigName, const std::string &Delimiter);
ConfigInt4* ReadConfigInt4  (const std::string &ConfigName, const std::string &Delimiter);
