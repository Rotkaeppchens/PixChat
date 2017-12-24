/**
 * @file
 * @brief The public header file for the interface
 *
 * @author Lukas Deutscher
 * @date 20.12.2017
 */

#include <string>

int InterfaceInit();
int InterfaceCheck();

void InterfaceSetInfoMsg(const std::string &Message);
bool InterfaceCreateAskForm(const std::string &Message);

void DisplayIncomingMessage(const std::string &Text, const std::string &From);
