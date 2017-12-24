/**
 * @file
 * @brief The header for the configuration class
 *
 * @author Lukas Deutscher
 * @date 07.12.2017
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @warning We need the string & vector class here, so this header includes it.
 */
#include "../includes/utility.h" // The utility functions
#include <iostream> // The standard io stream
#include <string>   // The string library
#include <fstream>  // The file stream lib
#include <vector>   // The basic vector type;

/**
 * @struct ConfigEntry
 * @brief The intern format for an config entry
 *
 * This struct is not for outside use
 * and only for the intern use of the config class.
 *
 */
typedef struct
{
    /**
     * The name of the config entry
     */
    std::string Name;
    /**
     * The value of the config entry as string,
     * will be converted if read with the function.
     */
    std::string Value;
} ConfigEntry;

/**
 * The file name of the config file.
 * Saved for later uses.
 */
std::string gConfigFileName;
/**
 * The holding vector in which we load the configurations
 */
std::vector<ConfigEntry*> gConfigVec;

ConfigEntry* CreateConfigEntry(const std::string Name, const std::string Value);

#endif
