/**
 * @file
 * @brief The class file for the friend roster
 *
 * @author Lukas Deutscher
 * @date 23.12.2017
 */

#include "gnf.h"

void FriendRoster::handleItemAdded(const gloox::JID &jid)
{
    L_INFO("friendroster", "Friendroster Item added");
    InterfaceRefreshFriendListDisplay();
}

void FriendRoster::handleItemSubscribed(const gloox::JID &jid)
{
    L_INFO("friendroster", "Item subscribed");
    InterfaceRefreshFriendListDisplay();
}

void FriendRoster::handleItemRemoved(const gloox::JID &jid)
{
    L_INFO("friendroster", "Item removed");
    InterfaceRefreshFriendListDisplay();
}

void FriendRoster::handleItemUpdated(const gloox::JID &jid)
{
    L_INFO("friendroster", "Item updated");
    InterfaceRefreshFriendListDisplay();
}

void FriendRoster::handleItemUnsubscribed(const gloox::JID &jid)
{
    L_INFO("friendroster", "Item unsubscribed");
    InterfaceRefreshFriendListDisplay();
}

void FriendRoster::handleRoster(const gloox::Roster &roster)
{
    L_INFO("friendroster", "Handling inital roster.");
}

void FriendRoster::handleRosterPresence(const gloox::RosterItem &rosterItem, const std::string &resource, gloox::Presence::PresenceType presence, const std::string &msg)
{
    L_INFO("friendroster", "Handle roster presence");
    InterfaceRefreshFriendListDisplay();
}

void FriendRoster::handleSelfPresence(const gloox::RosterItem &rosterItem, const std::string &resource, gloox::Presence::PresenceType presence, const std::string &msg)
{
    L_INFO("friendroster", "Handle self presence");
}

bool FriendRoster::handleSubscriptionRequest(const gloox::JID &Jid, const std::string &Msg)
{
    L_INFO("friendroster", "Subscription request from: " + Jid.full());

    std::string DisplayMessage;

    DisplayMessage += Jid.bare();
    DisplayMessage += " wants to be your friend.\n\n";
    DisplayMessage += Msg;

    bool UserResult = InterfaceCreateAskForm(DisplayMessage);

    return UserResult;
}

bool FriendRoster::handleUnsubscriptionRequest(const gloox::JID &Jid, const std::string &Msg)
{
    L_INFO("friendroster", "Unsubscription request from: " + Jid.full());

    std::string DisplayMessage;

    DisplayMessage += Jid.bare();
    DisplayMessage += " doesn't want to be your friend anymore.\n\n";
    DisplayMessage += Msg;

    bool UserResult = InterfaceCreateAskForm(DisplayMessage);

    return UserResult;
}

void FriendRoster::handleNonrosterPresence(const gloox::Presence &presence)
{
    L_INFO("friendroster", "Handle noroster presence");
}

void FriendRoster::handleRosterError(const gloox::IQ &iq)
{
    L_INFO("friendroster", "Handle roster error");
}
