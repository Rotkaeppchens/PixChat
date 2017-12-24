/**
 * @file
 * @brief The log functions
 *
 * This file defines the log functions used to write messages with levels to a file.
 *
 * @author Lukas Deutscher
 * @date 11.12.2017
 */

#include "log.h"    // The log header file
#include <iostream> // The standard in/output
#include <string>   // The standard string type
#include <fstream>  // The file stream type
#include <ctime>    // The time header from c

/**
 * @brief Initializes the log module.
 *
 * This function opens a file to write to and stores the handler.
 *
 * @param LogFilePath The path to the log file
 * @return bool The success of the operation.
 */
bool LogInit(const std::string &LogFilePath)
{
    gLogFilePath = LogFilePath;
    gLogOutStrm.open(LogFilePath);

    std::time_t Now = time(0);
    std::string DateTime = ctime(&Now);

    // The linebreak is throug ctime implicit so we use only flush.
    gLogOutStrm << "Log File started on " << DateTime << std::flush;
    gLogOutStrm << "Setting LogLevel for domains..." << std::endl;

    std::string ConfigPrefix = "client.log.level.";

    // The default log level is a special case so we check that beforehand.
    DomainLogLevel* DefaultDomain;

    if (ConfigKeyExists(ConfigPrefix + "default")) {
        DefaultDomain = CreateDomainLogLevel(
            "default",
            ReadConfigLogLevel(ConfigPrefix + "default")
        );
    } else {
        DefaultDomain = CreateDomainLogLevel(
            "default",
            L_INFO
        );
    }

    gLogLevelDomainVec.push_back(DefaultDomain);

    // And the we check the remaining log domains
    for (unsigned int i = 0; i != gLogDomains.size(); ++i) {
        DomainLogLevel* Dll;

        if (ConfigKeyExists(ConfigPrefix + gLogDomains[i])) {
            Dll = CreateDomainLogLevel(
                gLogDomains[i],
                ReadConfigLogLevel(ConfigPrefix + gLogDomains[i])
            );
        } else {
            Dll = CreateDomainLogLevel(
                gLogDomains[i],
                GetDomainLogLevel("default")
            );
        }

        gLogLevelDomainVec.push_back(Dll);
    }

    DumpDomainLogLevel();

    LogMsg(L_INFO, "log", "Logsystem ready.");

    return true;
}

/**
 * @brief Writes a message to the log file
 *
 * This function takes three arguments,
 * from them it builds a message to write to the log file.
 * If the domain is not default then it will check if there is a configuration,
 * for the loglevel in the config file.
 *
 * :TODO: Check Loglevel in the config file.
 *
 * @param LogLevel The LogLevel of the Message.
 * @param LogDomain The domain in which the message is.
 * @param Message The Message string.
 * @return ~
 */
void LogMsg(
    const LogLevelEnum &LogLevel,
    const std::string &LogDomain,
    const std::string &Message
) {
    if (!IsLogLevelPrintable(LogLevel, LogDomain)) {
        return;
    }

    std::time_t Now = time(0);
    std::tm* LocalTime = localtime(&Now);

    std::string NowStr =
        std::to_string(LocalTime->tm_hour) + ":" +
        std::to_string(LocalTime->tm_min) + ":" +
        std::to_string(LocalTime->tm_sec)
    ;

    gLogOutStrm <<
        "[" << NowStr << "] " <<
        "{" << LogDomain << "} " <<
        LogLevel << ": " <<
        Message <<
        std::endl
    ;
}

/**
 * @brief Dumps the domain log level into the log file
 *
 * @return void
 */
void DumpDomainLogLevel()
{
    gLogOutStrm << "Dumping Log Domains..." << std::endl;

    for (unsigned int i = 0; i != gLogLevelDomainVec.size(); ++i) {
        gLogOutStrm <<
            "\tDomainName: " << gLogLevelDomainVec[i]->LogDomain << std::endl <<
            "\tLogLevel: " << std::to_string(gLogLevelDomainVec[i]->LogLevel) << std::endl <<
            "\tBitmap: " << std::to_string(gLogLevelDomainVec[i]->Bitmap) << std::endl
            << std::endl
        ;
    }

    gLogOutStrm << "...finished" << std::endl;
}

/**
 * @brief Creates an DomainLogLevel Object and returns a pointer to this.
 *
 * @param Domain The domain name
 * @param LogLevel The LogLevel
 * @return DomainLogLevel* The Object pointer
 */
DomainLogLevel* CreateDomainLogLevel(const std::string &Domain, const LogLevelEnum &LogLevel)
{
    DomainLogLevel* Dll = new DomainLogLevel();

    Dll->LogDomain = Domain;
    Dll->LogLevel = LogLevel;
    Dll->Bitmap = CreateLogLevelBitmap(LogLevel);

    return Dll;
}

/**
 * @brief Reads the log level from the domain
 *
 * @warning This function assumes the key exists.
 *
 * :TODO: Throw exception in case of misformed config value
 *
 * @param ConfigKey The key to the value
 * @return LogLevelEnum The LogLevel
 */
LogLevelEnum ReadConfigLogLevel(const std::string &ConfigKey)
{
    std::string ConfigValue = ReadConfigString(ConfigKey);
    LogLevelEnum LogLevel;

    if (ConfigValue == "DEBUG") {
        LogLevel = L_DEBUG;
    } else if (ConfigValue == "INFO") {
        LogLevel = L_INFO;
    } else if (ConfigValue == "WARNING") {
        LogLevel = L_WARNING;
    } else if (ConfigValue == "ERROR") {
        LogLevel = L_ERROR;
    } else if (ConfigValue == "OFF") {
        LogLevel = L_OFF;
    } else {
        LogLevel = L_WARNING;
    }

    return LogLevel;
}

/**
 * @brief Returns the active loglevel bitmap for the loglevel
 *
 * This function takes a Loglevel from the loglevel enum and
 * deduces from there the active log level bitmap with the first bit the
 * lowest level.
 *
 * @param LogLevel The loglevel for the bitmap
 * @return int The bitmap with the active loglevel set.
 */
unsigned int CreateLogLevelBitmap(const LogLevelEnum &LogLevel)
{
    unsigned int ActiveBitmap = 0;
    unsigned int ActiveBit = 1;

    // OFF is a special case, therefore we check beforehand
    if (LogLevel == L_OFF) {
        return ActiveBitmap;
    }

    switch (LogLevel) {
        case L_DEBUG:
            ActiveBitmap |= ActiveBit << L_DEBUG;
        case L_INFO:
            ActiveBitmap |= ActiveBit << L_INFO;
        case L_WARNING:
            ActiveBitmap |= ActiveBit << L_WARNING;
        case L_ERROR:
            ActiveBitmap |= ActiveBit << L_ERROR;
            break;
        default:
            ActiveBitmap  = 0;
    }

    return ActiveBitmap;
}

/**
 * @brief Gets the domain log level enum from the hold vector
 *
 * @warning Assumes Domain exists
 *
 * @param Domain The domain
 * @return LogLevelEnum The loglevel
 */
LogLevelEnum GetDomainLogLevel(const std::string &Domain)
{
    for (unsigned int i = 0; i != gLogLevelDomainVec.size(); ++i) {
        if (gLogLevelDomainVec[i]->LogDomain == Domain) {
            return gLogLevelDomainVec[i]->LogLevel;
        }
    }

    return L_OFF;
}

/**
 * @brief Gets the domain bitmap
 *
 * @warning Assumes Domain exists
 *
 * @param Domain The domain
 * @return unsigned int The Bitmap
 */
unsigned int GetDomainLogLevelBitmap(const std::string &Domain)
{
    for (unsigned int i = 0; i != gLogLevelDomainVec.size(); ++i) {
        if (gLogLevelDomainVec[i]->LogDomain == Domain) {
            return gLogLevelDomainVec[i]->Bitmap;
        }
    }

    return L_OFF;
}

/**
 * @brief Checks if the specified loglevel printable is
 *
 * @param LogLevel The LogLevel
 * @param Domain The Domain
 * @return bool The evaluation
 */
bool IsLogLevelPrintable(const LogLevelEnum &LogLevel, const std::string &Domain)
{
    unsigned int DomainBitmap = GetDomainLogLevelBitmap(Domain);
    unsigned int ActiveBit = 1;
    bool IsPrintable = DomainBitmap & (ActiveBit << LogLevel);

    return IsPrintable;
}
