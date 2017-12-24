/**
 * @file
 * @brief The public header for the config module
 *
 * @author Lukas Deutscher
 * @date 20.12.2017
 */

bool LoadConfig(std::string FileName, std::string ConfigDelimiter, std::string CommentChar);
void DumpConfigEntries();
bool ConfigKeyExists(const std::string &ConfigName);

/**
 * The functions are all read functions for different types.
 */
std::string ReadConfigString(const std::string ConfigName);
int         ReadConfigInt   (const std::string ConfigName);
double      ReadConfigDouble(const std::string ConfigName);
