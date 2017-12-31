/**
 * @file
 * @brief The functions for the chat state handler class
 *
 * @author Lukas Deutscher
 * @date 31.12.2017
 */

#include "gnf.h"

std::map<gloox::ChatStateType, std::string> gChatStateMap {
    {gloox::ChatStateActive, "User is active"},
    {gloox::ChatStateComposing, "User is typing"},
    {gloox::ChatStatePaused, "User is pausing"},
    {gloox::ChatStateInactive, "User is inactive."},
    {gloox::ChatStateGone, "User is gone."},
    {gloox::ChatStateInvalid, "Chat state invalid"}
};

void GnfChatStateHandler::handleChatState(const gloox::JID &From, gloox::ChatStateType State)
{
    L_INFO("gnf", "Incoming chat state from: " + From.bare());
}
