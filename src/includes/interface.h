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
bool InterfaceCreateAskForm(std::string Message, bool ReplaceAtSign = false);
void InterfaceDisplayErrorForm(std::string Message, bool ReplaceAtSign = false);
void InterfaceDisplayInfoForm(std::string Message, bool ReplaceAtSign = false);

void DisplayIncomingMessage(const std::string &Text, const std::string &From);

void InterfaceRefreshFriendListDisplay();
