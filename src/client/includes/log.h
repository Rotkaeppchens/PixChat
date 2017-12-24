/**
 * @file
 * @brief The public header for the log module
 *
 * @author Lukas Deutscher
 * @date 30.12.2017
 */

#include <string>

/**
 * @def DEBUG
 * @brief The debug macro.
 */
#define L_DEBUG(LogDomain, Message) LogMsg(L_DEBUG, LogDomain, Message)
/**
 * @def INFO
 * @brief The info macro.
 */
#define L_INFO(LogDomain, Message) LogMsg(L_INFO, LogDomain, Message)
/**
 * @def WARNING
 * @brief The warning macro.
 */
#define L_WARNING(LogDomain, Message) LogMsg(L_WARNING, LogDomain, Message)
/**
 * @def ERROR
 * @brief The error macro.
 */
#define L_ERROR(LogDomain, Message) LogMsg(L_ERROR, LogDomain, Message)

/**
 * @enum LogLevelEnum
 * @brief This Enum declares the possible log levels.
 *
 * @warning If there is a loglevel added or removed please change
 * the functions ReadConfigLogLevel and CreateLogLevelBitmap
 */
enum LogLevelEnum
{
    L_OFF = 0,
    L_ERROR,
    L_WARNING,
    L_INFO,
    L_DEBUG
};

bool LogInit(const std::string &LogFilePath);
void LogMsg(
    const LogLevelEnum &LogLevel,
    const std::string &LogDomain,
    const std::string &Message
);
