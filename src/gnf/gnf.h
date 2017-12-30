/**
 * @file
 * @brief The header for the Gloox Network Functions (gnf)
 *
 * @author Lukas Deutscher
 * @date 20.12.2017
 */

#include "../includes/gnf.h" // The public header
#include "../includes/log.h" // The log header
#include "../includes/config.h" // The config header
#include "../includes/interface.h" // The interface header
#include "../includes/globals.h" // The global macros

#include <iostream>
#include <ctime>
#include <vector>
#include <map>

#include <gloox/client.h> // The gloox client
#include <gloox/message.h> // The gloox message type
#include <gloox/messagehandler.h> // The gloox message handler
#include <gloox/connectionlistener.h> // The gloox connection listener
#include <gloox/rostermanager.h>
#include <gloox/disco.h>
#include <gloox/discohandler.h>

#ifndef GNF_H
#define GNF_H

class ConnListener : public gloox::ConnectionListener
{
    public:
    virtual void onConnect();
    virtual void onDisconnect(gloox::ConnectionError e);
    virtual bool onTLSConnect(const gloox::CertInfo& Info);

};

class MainChatMessageHandler : public gloox::MessageHandler
{
    public:
    virtual void handleMessage(const gloox::Message &stanza, gloox::MessageSession* session = 0);
};

class FriendRoster : public gloox::RosterListener
{
    public:
    virtual void handleItemAdded(const gloox::JID &jid);
    virtual void handleItemSubscribed(const gloox::JID &jid);
    virtual void handleItemRemoved(const gloox::JID &jid);
    virtual void handleItemUpdated(const gloox::JID &jid);
    virtual void handleItemUnsubscribed(const gloox::JID &jid);
    virtual void handleRoster(const gloox::Roster &roster);
    virtual void handleRosterPresence(const gloox::RosterItem &rosterItem, const std::string &resource, gloox::Presence::PresenceType presence, const std::string &msg);
    virtual void handleSelfPresence(const gloox::RosterItem &rosterItem, const std::string &resource, gloox::Presence::PresenceType presence, const std::string &msg);
    virtual bool handleSubscriptionRequest(const gloox::JID &Jid, const std::string &Msg);
    virtual bool handleUnsubscriptionRequest(const gloox::JID &Jid, const std::string &Msg);
    virtual void handleNonrosterPresence(const gloox::Presence &presence);
    virtual void handleRosterError(const gloox::IQ &iq);
};

UserId FormatRosterItemToUserId(gloox::RosterItem* Item);
std::string TranslateCertStatus(const int &StatusBitmap);

#endif
