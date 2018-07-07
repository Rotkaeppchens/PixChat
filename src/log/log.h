/**
 * @file
 * @brief The header to the log module
 *
 * The domains can have each their own loglevel which has to be declared in the
 * config file.
 *
 * The prefix is client.log.level. + the domain name
 *
 * The key client.log.level.default should always exist.
 *
 * @author Lukas Deutscher
 * @date 11.12.2017
 */

#ifndef LOG_H
#define LOG_H

#include "../includes/log.h"
#include "../includes/config.h"
#include <vector> // The vector type
#include <iostream> // The standard in/output
#include <string>   // The standard string type
#include <fstream>  // The file stream type
#include <ctime>    // The time header from c
#include <regex>    // The c++ regex functions

/**
 * @struct DomainLogLevel
 * @brief The struct for a single domain log level
 *
 * This function is only used internally in the log class
 */
struct DomainLogLevel
{
    /**
     * @brief The name of the domain
     */
    std::string LogDomain;
    /**
     * @brief The log level
     */
    LogLevelEnum LogLevel;
    /**
     * @brief The bitmap
     */
    unsigned int Bitmap;
};

// Global Variables
/**
 * @brief The possible Log Domains
 *
 * The default domain isnt in this vector but has to be declared in the config file.
 *
 * If it isnt declared default is INFO
 */
const std::vector<std::string> gLogDomains = {
	"config", 
	"log",
	"interface", 
	"gnf", 
	"friendroster", 
	"gnfmessagesessionhandler",
	"locale"
};
/**
 * @brief The global var for the output file stream
 */
std::ofstream gLogOutStrm;
/**
 * @brief The global var for the file path
 */
std::string gLogFilePath;
/**
 * @brief The global var for the domain log levels.
 */
std::vector<DomainLogLevel*> gLogLevelDomainVec;

// Function definitions
void DumpDomainLogLevel();

LogLevelEnum ReadConfigLogLevel(const std::string &ConfigKey);

DomainLogLevel* CreateDomainLogLevel(const std::string &Domain, const LogLevelEnum &LogLevel);
unsigned int CreateLogLevelBitmap(const LogLevelEnum &LogLevel);

LogLevelEnum GetDomainLogLevel(const std::string &Domain);
unsigned int GetDomainLogLevelBitmap(const std::string &Domain);

bool IsLogLevelPrintable(const LogLevelEnum &LogLevel, const std::string &Domain);

#endif
