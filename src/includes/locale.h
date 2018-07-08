/**
 * @file
 * @brief The public header for the locale module
 *
 * This module reads a localization file,
 * that is a file with a simple csv format:
 *  key:value
 *  button.abort:Abort
 * The delimiter is set in the config file under config.locale.keydelimiter
 *
 * The file can be compressed with gzip.
 * The module uses zlib to read so it can be both
 * (a normal text file or a gzip file).
 *
 * @author Lukas Deutscher
 * @date 07.07.2018
 */

#include <string>

void LocaleInit(const std::string &FilePath);
void DumpLocaleToLog();

std::string GetLocaleString(const std::string &Key);
const std::string *GetLocaleStringPtr(const std::string &Key);
