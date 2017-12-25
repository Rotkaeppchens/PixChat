/**
 * @file
 * @brief The public header for the Gloox Network Functions
 *
 * @author Lukas Deutscher
 * @date 20.12.2017
 */

#include <string>
#include <vector>

/**
 * We reimplement the jid type ourselves because we want to use it in our other modules.
 */
class UserId
{
    public:
    std::string Full;
    std::string Bare;
    std::string Username;
    std::string Server;
    std::string ServerRaw;
    std::string Resource;

    bool IsOnline;
};

void GnfInitChatUser();
bool GnfUpdate(int Timeout = -1);

void GnfSendMessage(const std::string &To, const std::string &Message);

std::vector<UserId> GnfGetFullFriendRoster();
UserId* GnfGetFriendData(const std::string &Id);
void GnfAddFriendToRoster(const std::string &Id);
void GnfRemoveFriendFromRoster(const std::string &Id);
