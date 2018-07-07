/**
 * @file
 * @brief In this header there will be the default values for the config keys
 *
 * @author Lukas Deutscher
 * @date 06.07.2018
 */

#include "config.h"

/**
 * @brief Returns the default config map
 *
 * @return map The default map
 */
std::map<std::string, std::string> GetDefaultConfigMap()
{
    // The default map
    std::map<std::string, std::string> DefaultConfigMap;

    // The log options
    DefaultConfigMap["client.log.path"] = "../log/";
    DefaultConfigMap["client.log.file"] = "general.log";
    DefaultConfigMap["client.log.level.default"] = "INFO";

    // The time to wait for a timeout
    DefaultConfigMap["client.gloox.updatetime"] = "10";

    // Possible values disabled, optional, required
    DefaultConfigMap["client.tls.active"] = "required";

    // Locale File options
    DefaultConfigMap["client.locale.path"] = "../loc/";
    DefaultConfigMap["client.locale.file"] = "en";
    DefaultConfigMap["client.locale.post"] = ".loc";
    // This value is the max length of the line read buffer
    DefaultConfigMap["client.locale.bufferlength"] = "256";
    DefaultConfigMap["client.locale.keydelimiter"] = ":";

    return DefaultConfigMap;
}
