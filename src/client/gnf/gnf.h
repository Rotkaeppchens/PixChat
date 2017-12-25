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
    virtual void onConnect()
    {
        L_INFO("gnf", "Connected.");
        InterfaceSetInfoMsg("Connected.");
    }

    virtual void onDisconnect(gloox::ConnectionError e)
    {
        InterfaceSetInfoMsg("Disconnected.");

        //~ ERROR("gnf", "Test Error");

        if (e == gloox::ConnNoError) {
            L_INFO("gnf", "Disconnected.");
            return;
        }

        if (e == gloox::ConnStreamError) {
            L_ERROR("gnf", "Disconnect: Stream Error");
        } else if (e == gloox::ConnAuthenticationFailed) {
            L_ERROR("gnf", "Disconnect: Authentication Failed");
        } else {
            L_ERROR("gnf", "Disconnected with error.");
        }
    }

    virtual bool onTLSConnect(const gloox::CertInfo& Info)
    {
        L_INFO("gnf", "Trying to connect using tls.");

        time_t DateFrom(Info.date_from);
        time_t DateTo(Info.date_to);

        std::string InfoString = "";
        InfoString += "status: " + std::to_string(Info.status) + "\n";
        InfoString += "issuer: " + Info.issuer + "\n";
        InfoString += "server: " + Info.server + "\n";
        InfoString += "protocol: " + Info.protocol + "\n";
        InfoString += "cipher: " + Info.cipher + "\n";
        InfoString += "mac: " + Info.mac + "\n";
        InfoString += "compression: " + Info.compression + "\n";
        InfoString += "date from: ";
        InfoString += std::ctime(&DateFrom);
        InfoString += "date to: ";
        InfoString += std::ctime(&DateTo);

        L_INFO("gnf", "Certificate info: " + InfoString);

        bool UserAnswer = InterfaceCreateAskForm("Do you want to accept this Certificate?\n" + InfoString);

        if (UserAnswer) {
            InterfaceSetInfoMsg("TLS Connected.");
            return true;
        } else {
            L_INFO("gnf", "User didn't accept Certificate.");
            InterfaceSetInfoMsg("TLS Disconnected.");
            return false;
        }
    }
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
    virtual bool handleSubscriptionRequest(const gloox::JID &jid, const std::string &msg);
    virtual bool handleUnsubscriptionRequest(const gloox::JID &jid, const std::string &msg);
    virtual void handleNonrosterPresence(const gloox::Presence &presence);
    virtual void handleRosterError(const gloox::IQ &iq);
};

UserId FormatRosterItemToUserId(gloox::RosterItem* Item);

#endif
