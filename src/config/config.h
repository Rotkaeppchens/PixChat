/**
 * @file
 * @brief The header for the configuration class
 *
 * @author Lukas Deutscher
 * @date 07.12.2017
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "../includes/utility.h" // The utility functions
#include <iostream> // The standard io stream
#include <string>   // The string library
#include <fstream>  // The file stream lib
#include <map>      // The basic map type;
#include <vector>	// The basic vector type
#include "default_config.h" // The default config map

/**
 * The file name of the config file.
 * Saved for later uses.
 */
std::string gConfigFileName;
/**
 * The holding map in which we load the configurations
 */
std::map<std::string, std::string> gConfigMap;

std::map<std::string, std::string> GetDefaultConfigMap();

#endif
