/**
 * @file
 * @brief The implementation of the config class
 *
 * Here we define the functions of the config class.
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
    std::string FileName,
    std::string ConfigDelimiter,
    std::string CommentChar
) {
    gConfigFileName = FileName;

    std::ifstream CfgIfStrm(gConfigFileName);

    if (!CfgIfStrm.is_open()) {
        std::cout << "There was an error opening the config file." << std::endl;
    }

    std::vector<ConfigEntry> ConfigVec;
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

        ConfigEntry* CEntry = CreateConfigEntry(SplittedLine[0], SplittedLine[1]);

        gConfigVec.push_back(CEntry);
    }

    CfgIfStrm.close();
    return true;
}

/**
 * @brief This creates a new config entry and returns a pointer to it.
 *
 * This function takes to arguments a name and a value and returns a pointer
 * to a new ConfigEntry object with these values.
 *
 * @param Name The name of the name
 * @param Value The value of the pair
 * @return ConfigEntry* The pointer to the new entry
 */
ConfigEntry* CreateConfigEntry(const std::string Name, const std::string Value)
{
    ConfigEntry* CE = new ConfigEntry();

    CE->Name = Name;
    CE->Value = Value;

    return CE;
}

/**
 * @brief Dumps the config in the cout stream
 *
 * This functions dumps the entire config list in the cout stream
 * and returns the vector with the pointers to the entries.
 *
 * @return void
 */
void DumpConfigEntries()
{
    for (unsigned int i = 0; i != gConfigVec.size(); ++i) {
        std::cout << "Name: " << gConfigVec[i]->Name << " <--> ";
        std::cout << "Value: " << gConfigVec[i]->Value << std::endl;
    }
}

/**
 * @brief Checks if the specified config key exists
 *
 * This function takes a config key name and iterates the saved configs,
 * and returns if the config key exists.
 *
 * @param ConfigName The name of the key to check
 * @return bool The result of the check.
 */
bool ConfigKeyExists(const std::string &ConfigName)
{
    for (unsigned int i = 0; i != gConfigVec.size(); ++i) {
        if (gConfigVec[i]->Name == ConfigName) {
            return true;
        }
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
std::string ReadConfigString(const std::string ConfigName)
{
    for (unsigned int i = 0; i != gConfigVec.size(); ++i) {
        if (gConfigVec[i]->Name != ConfigName) {
            continue;
        }

        return gConfigVec[i]->Value;
    }

    std::cout << "Value not found: " << ConfigName << std::endl;

    return "";
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
int ReadConfigInt(const std::string ConfigName)
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
double ReadConfigDouble(const std::string ConfigName)
{
    double ConfigValue = std::stod(ReadConfigString(ConfigName));

    return ConfigValue;
}
