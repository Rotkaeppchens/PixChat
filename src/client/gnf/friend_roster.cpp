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
}

void FriendRoster::handleItemSubscribed(const gloox::JID &jid)
{
    L_INFO("friendroster", "Item subscribed");
}

void FriendRoster::handleItemRemoved(const gloox::JID &jid)
{
    L_INFO("friendroster", "Item removed");
}

void FriendRoster::handleItemUpdated(const gloox::JID &jid)
{
    L_INFO("friendroster", "Item updated");
}

void FriendRoster::handleItemUnsubscribed(const gloox::JID &jid)
{
    L_INFO("friendroster", "Item unsubscribed");
}

void FriendRoster::handleRoster(const gloox::Roster &roster)
{
    L_INFO("friendroster", "Handling inital roster.");

    gloox::Roster::const_iterator RosterIter = roster.begin();
    for (; RosterIter != roster.end(); ++RosterIter) {
        gloox::JID RosterJid = RosterIter->second->jidJID();

        this->mRosterVec.push_back(RosterJid);

        L_INFO("friendroster", "Item on roster: " + RosterJid.full());
    }
}

void FriendRoster::handleRosterPresence(const gloox::RosterItem &rosterItem, const std::string &resource, gloox::Presence::PresenceType presence, const std::string &msg)
{
    L_INFO("friendroster", "Handle roster presence");
}

void FriendRoster::handleSelfPresence(const gloox::RosterItem &rosterItem, const std::string &resource, gloox::Presence::PresenceType presence, const std::string &msg)
{
    L_INFO("friendroster", "Handle self presence");
}

bool FriendRoster::handleSubscriptionRequest(const gloox::JID &jid, const std::string &msg)
{
    L_INFO("friendroster", "Subscription request");
    return true;
}

bool FriendRoster::handleUnsubscriptionRequest(const gloox::JID &jid, const std::string &msg)
{
    L_INFO("friendroster", "Unsubscription request");
    return true;
}

void FriendRoster::handleNonrosterPresence(const gloox::Presence &presence)
{
    L_INFO("friendroster", "Handle noroster presence");
}

void FriendRoster::handleRosterError(const gloox::IQ &iq)
{
    L_INFO("friendroster", "Handle roster error");
}

/**
 * @brief This returns a vector with all friends converted to UserId
 *
 * @return vector<UserId>
 */
std::vector<UserId> FriendRoster::GetFullFriendRoster()
{
    std::vector<UserId> ReturnVec;

    for (unsigned int i = 0; i != this->mRosterVec.size(); ++i) {
        UserId SingleId;

        SingleId.Full = this->mRosterVec[i].full();
        SingleId.Bare = this->mRosterVec[i].bare();
        SingleId.Username = this->mRosterVec[i].username();
        SingleId.Server = this->mRosterVec[i].server();
        SingleId.ServerRaw = this->mRosterVec[i].serverRaw();
        SingleId.Resource = this->mRosterVec[i].resource();

        ReturnVec.push_back(SingleId);
    }

    return ReturnVec;
}
