/**
 * @file
 * @brief The main function for the client
 *
 * This is the standard main function for the client.
 * It uses gloox and fltk to display and communicate with the xmpp server.
 *
 * @author Lukas Deutscher
 * @date 07.12.2017
 */

#include "client_main.h"
#include "../includes/globals.h"
#include "../includes/log.h" // The log functions
#include "../includes/config.h" // The config class
#include "../includes/utility.h" // The helper functions
#include "../includes/locale.h" // The locale system
#include "../includes/interface.h" // The interface layer
#include "../includes/gnf.h" // The gloox network functions
#include <iostream> // The standard in/output
#include <string> // The standard string type

/**
 * @brief The init func for the client main
 *
 * Here we initialize the Modules
 *
 * @param argc The number of arguments
 * @param argv The arguments
 * @return int The init code
 */
int ClientInit(int argc, char** argv)
{
    LoadConfig(
        CONFIG_FILE_NAME,
        CONFIG_DELIMITER,
        CONFIG_COMMENT_CHAR
    );

    LogInit(LOG_FILE_PATH);
    
    LocaleInit(
		ReadConfigString("client.locale.path") + 
		ReadConfigString("client.locale.file") +
		ReadConfigString("client.locale.post")
	);

    InterfaceInit();

    GnfInitChatUser();

    return 0;
}

/**
 * @brief The client main
 *
 * This is the client main to call from the main main :)
 *
 * @param argc The number of arguments passed from the main
 * @param argv The string array passed from the main
 * @return int The return value of the main. 0 = no errors
 */
int ClientMain(int argc, char** argv)
{
    ClientInit(argc, argv);

    L_INFO("default", "Starting main loop...");

    while (InterfaceCheck()) {
        GnfUpdate(GLOOX_UPDATE_TIME);
    }

    return 0;
}
