/**
 * @file
 * @brief The locale module, for reading localization files.
 *
 * @author Lukas Deutscher
 * @date 07.07.2018
 */

#include "locale.h"

/**
 * @brief Initializes the locale system and loads a file into the memory.
 * 
 */
void LocaleInit(const std::string &FilePath) 
{
	L_INFO("locale", "Initializing locale system...");
	L_INFO("locale", "File path: " + FilePath);
}
