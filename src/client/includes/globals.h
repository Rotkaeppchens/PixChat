/**
 * @file
 * @brief Global definitions for the whole project
 *
 * @author Lukas Deutscher
 * @date 21.12.2017
 */

#ifndef GLOBALS_H
#define GLOBALS_H

/**
 * @def PROJECT_NAME
 * @brief The project name
 */
#define PROJECT_NAME "PixChat"
/**
 * @def PROJECT_VERSION_NR
 * @brief The version number of the project
 */
#define PROJECT_VERSION_NR "0.2"

/**
 * @def CONFIG_FILE_NAME
 * @brief The config file name to read.
 */
#define CONFIG_FILE_NAME "../etc/client.cfg"
/**
 * @def CONFIG_DELIMITER
 * @brief The delimiter between name and value in the config.
 */
#define CONFIG_DELIMITER ":"
/**
 * @def CONFIG_COMMENT_CHAR
 * @brief The char used to invoke comments in the config file.
 */
#define CONFIG_COMMENT_CHAR "#"
/**
 * @def LOG_FILE_PATH
 * @brief The file path to the log file
 */
#define LOG_FILE_PATH "../log/general.log"

/**
 * @def GLOOX_UPDATE_TIME
 * @brief The time to wait for timeout
 */
#define GLOOX_UPDATE_TIME 10

#endif
