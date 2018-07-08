/**
 * @file
 * @brief The implementation of the config module
 *
 * @author Lukas Deutscher
 * @date 07.12.2017
 */

#include "config.h" // The config class header.

/**
 * @brief Parses a config file and puts it in the ram.
 *
 * This function reads the passed file and tries to parse it.
 * The result is put into an intern var to get later,
 * when the config value is needed.
 *
 * @param FileName          The name of the config file to read
 * @param ConfigDelimiter   The delimiter between name and value in the config.
 * @param CommentChar       The character with which the comments begin.
 * @return bool The success of the operation
 */
bool LoadConfig(
    const std::string &FileName,
    const std::string &ConfigDelimiter,
    const std::string &CommentChar
) {
    // First we load the basic config with the default values.
    gConfigMap = GetDefaultConfigMap();

    // Then we load the config file
    gConfigFileName = FileName;

    std::ifstream CfgIfStrm(gConfigFileName);

    if (!CfgIfStrm.is_open()) {
        std::cout << "There was an error opening the config file." << std::endl;
        return false;
    }

    std::string FileBuffer;
    while (getline(CfgIfStrm, FileBuffer)) {
        if (
            FileBuffer.find(ConfigDelimiter) == std::string::npos
            || (
                FileBuffer.find(CommentChar) != std::string::npos
                && FileBuffer.find(CommentChar) == 0
            )
        ) {
            continue;
        }

        std::vector<std::string> SplittedLine = StrSplitFirst(FileBuffer, ConfigDelimiter);

        std::string Key = StrTrim(SplittedLine[0]);
        std::string Value = StrTrim(SplittedLine[1]);

        gConfigMap[Key] = Value;
    }

    CfgIfStrm.close();
    return true;
}

/**
 * @brief Dumps the config in the cout stream
 *
 * This functions dumps the entire config list in the cout stream.
 *
 * @return void
 */
void DumpConfigEntries()
{
    auto MapIter = gConfigMap.begin();
    for (; MapIter != gConfigMap.end(); ++MapIter) {
        std::cout << "Name: " << MapIter->first << " <--> ";
        std::cout << "Value: " << MapIter->second << std::endl;
    }
}

/**
 * @brief Checks if the specified config key exists
 *
 * This function takes a config key name and searches the saved configs,
 * and returns it if the config key exists.
 *
 * @param ConfigName The name of the key to check
 * @return bool The result of the check.
 */
bool ConfigKeyExists(const std::string &ConfigName)
{
    if (gConfigMap.find(ConfigName) != gConfigMap.end()) {
        return true;
    }

    return false;
}

/**
 * @brief Reads and returns the value of the config as an string
 *
 * This function takes the name of a config as parameter and returns the
 * underlying value.
 * If the name das not exist it throws an exception
 *
 * @warning Not finished, returns empty string on not found
 * :TODO: Improve return on not found.
 *
 * @param ConfigName The name of the config value to get.
 * @return std::string The value as string
 */
std::string ReadConfigString(const std::string &ConfigName)
{
    auto MapIter = gConfigMap.find(ConfigName);

    if (MapIter == gConfigMap.end()) {
        std::cout << "Config value: " << ConfigName << " not found." << std::endl;
        //~ L_ERROR("default", "Config value: " + ConfigName + " not found.");
        return "";
    }

    return MapIter->second;
}

/**
 * @brief Read and returns the value of the config as int
 *
 * This function takes the name of a config as parameter and
 * returns die underlying value.
 *
 * @param ConfigName The name of the config value
 * @return int The value of the config as int
 */
int ReadConfigInt(const std::string &ConfigName)
{
    int ConfigValue = std::stoi(ReadConfigString(ConfigName));

    return ConfigValue;
}

/**
 * @brief Read and returns the value of the config as double
 *
 * This function takes the name of a config as parameter and
 * returns die underlying value.
 *
 * @param ConfigName The name of the config value
 * @return double The value of the config as double
 */
double ReadConfigDouble(const std::string &ConfigName)
{
    double ConfigValue = std::stod(ReadConfigString(ConfigName));

    return ConfigValue;
}

std::vector<std::string> ReadConfigStringVec(const std::string &ConfigName, const std::string &Delimiter)
{
    std::string ConfigValue = ReadConfigString(ConfigName);

    std::vector<std::string> StringVec;

    if (ConfigValue != "") {
        StringVec = StrSplit(ConfigValue, Delimiter);
    }

    return StringVec;
}

std::vector<int> ReadConfigIntVec(const std::string &ConfigName, const std::string &Delimiter)
{
    std::vector<std::string> StringVec =  ReadConfigStringVec(ConfigName, Delimiter);

    std::vector<int> IntVec;

    for (auto Iter = StringVec.begin(); Iter != StringVec.end(); ++Iter) {
        if (*Iter != ""){
            IntVec.push_back(std::stoi(*Iter));
        }
    }

    return IntVec;
}
