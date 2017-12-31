/**
 * @file
 * @brief The functions for the message session handler class
 *
 * @author Lukas Deutscher
 * @date 30.12.2017
 */

#include "gnf.h"

extern std::map<std::string, gloox::MessageSession*> gMessageSessionMap;

void GnfMessageSessionHandler::handleMessageSession(gloox::MessageSession* Session)
{
    L_INFO("gnfmessagesessionhandler", "Incoming message session from: " + Session->target().bare());

    gloox::ChatStateFilter* StateFilter = new gloox::ChatStateFilter(Session);
    GnfChatStateHandler* StateHandler = new GnfChatStateHandler();
    StateFilter->registerChatStateHandler(StateHandler);

    GnfMessageHandler* MessHandler = new GnfMessageHandler();
    Session->registerMessageHandler(MessHandler);

    gMessageSessionMap.insert(std::pair<std::string, gloox::MessageSession*>(Session->target().bare(), Session));
}
