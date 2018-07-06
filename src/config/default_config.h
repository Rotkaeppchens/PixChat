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
	
	// The default log Level
	DefaultConfigMap["client.log.level.default"] = "INFO";
	
	// Possible values disabled, optional, required
	DefaultConfigMap["client.tls.active"] = "required";
	
	return DefaultConfigMap;
}
