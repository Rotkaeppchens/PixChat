/**
 * @file
 * @brief The locale module, for reading localization files.
 *
 * @author Lukas Deutscher
 * @date 07.07.2018
 */

#include "locale.h"

/**
 * @brief Initializes the locale system and loads a file into the memory.
 *
 * @param FilePath The Path to the locale file.
 * @return void
 */
void LocaleInit(const std::string &FilePath)
{
    L_INFO("locale", "Initializing locale system...");
    L_INFO("locale", "File path: " + FilePath);

    // We open the localization file for reading.
    // If the file is no gz file zlib will just read the normal file
    gzFile File = gzopen(FilePath.c_str(), "r");

    if (File == NULL) {
        L_ERROR("locale", "Couldn't open file: " + FilePath);
        return;
    }

    int BufferLength = ReadConfigInt("client.locale.bufferlength");

    char* LineBuffer = new char[BufferLength];
    std::string KeyDelimiter = ReadConfigString("client.locale.keydelimiter");

    while ((LineBuffer = gzgets(File, LineBuffer, BufferLength)) != NULL)
    {
        std::vector<std::string> LineSplitted = StrSplitFirst(LineBuffer, KeyDelimiter);

        if (LineSplitted.size() == 1) {
            L_WARNING("locale", "Malformed line: " + std::string(LineBuffer));
            continue;
        }

        std::string Key = StrTrim(LineSplitted[0]);
        std::string Value = StrTrim(LineSplitted[1]);

        gLocaleMap[Key] = Value;
    }

    // If the response is NULL it is the eof or an error
    int* Errno = new int;
    const char* ErrorMsg = gzerror(File, Errno);

    if (*Errno != 0) {
        L_ERROR("locale", "There was an error reading the locale file.");
        L_ERROR("locale", "Errno: " + std::to_string(*Errno) + " ErrorMsg: " + std::string(ErrorMsg));
    }

    gzclose_r(File);

    L_INFO("locale", "Locale system ready.");
}

/**
 * @brief Returns the locale string to the key
 *
 * @param Key The locale key
 * @return std::string
 */
std::string GetLocaleString(const std::string &Key)
{
    auto Result = gLocaleMap.find(Key);

    if (Result == gLocaleMap.end()) {
        L_WARNING("locale", "Key: " + Key + " not found.");
        return Key;
    }

    std::string Value = Result->second;

    L_DEBUG("locale", "Key: " + Key + " Value: " + Value);

    return Value;
}

/**
 * @brief Dumps the complete locale to the log
 *
 * @return void
 */
void DumpLocaleToLog()
{
    L_DEBUG("locale", "Starting locale dump...");

    auto Iter = gLocaleMap.begin();

    for(; Iter != gLocaleMap.end(); ++Iter) {
        L_DEBUG("locale", "Key: " + Iter->first + " Value: " + Iter->second);
    }

    L_DEBUG("locale", "Locale dump complete.");
}
