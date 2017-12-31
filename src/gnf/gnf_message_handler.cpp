/**
 * @file
 * @brief The functions for the message handler
 *
 * @author Lukas Deutscher
 * @date 30.12.2017
 */

#include "gnf.h"

/**
 * @brief Handles the incoming message and sends it to the front end
 *
 * @param stanza The message stanza
 * @param session The session from which the message comes
 * @return void
 */
void GnfMessageHandler::handleMessage(const gloox::Message &stanza, gloox::MessageSession* session)
{
    if (
        stanza.subtype() == gloox::Message::Chat ||
        stanza.subtype() == gloox::Message::Normal
    ) {
        std::string DisplayMessage;
        //~ DisplayMessage += stanza.from().username() + "@";
        //~ DisplayMessage += stanza.from().server() + ": ";
        DisplayMessage = stanza.from().bare() + ": ";
        DisplayMessage += stanza.body() + "\n";

        L_INFO("gnf", "Received message: " + DisplayMessage);

        std::string Username = stanza.from().username();
        if (Username == " ") {
            Username = "Generic";
        }

        DisplayIncomingMessage(DisplayMessage, stanza.from().username());
    } else {
        L_INFO("gnf", "Message: " + stanza.body() + " will not be printed.");
    }
}
