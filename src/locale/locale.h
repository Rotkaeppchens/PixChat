/**
 * @file
 * @brief The private header for the locale module
 *
 * @author Lukas Deutscher
 * @date 07.07.2018
 */

#include "../includes/locale.h"     // The public header
#include "../includes/config.h"     // The config module
#include "../includes/log.h"        // The log module
#include "../includes/utility.h"    // Basic utility functions
#include <zlib.h>   // The zlib header
#include <map>      // The default map type
#include <vector>   // The default vector type
#include <string>   // The default string type

static std::map<std::string, std::string> gLocaleMap;
