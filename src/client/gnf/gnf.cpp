/**
 * @file
 * @brief The Gloox Network Functions (gnf) Definitions
 *
 * @author Lukas Deutscher
 * @date 20.12.2017
 */

#include "gnf.h" // Header for the definitions

/**
 * Globals
 */
gloox::Client* gMainChatClient;
FriendRoster* gFriendRoster;

void GnfInitChatUser()
{
    L_INFO("gnf", "Initializing chat user...");
    std::string ClientName = ReadConfigString("client.account.name");
    std::string ClientHost = ReadConfigString("client.account.host");
    std::string ClientPass = ReadConfigString("client.account.pass");

    L_INFO("gnf", "Client name: " + ClientName);
    L_INFO("gnf", "Client host: " + ClientHost);

    gloox::JID jid(
        ClientName +
        "@" +
        ClientHost
    );

    gMainChatClient = new gloox::Client(jid, ClientPass);

    MainChatMessageHandler* MsgHandler = new MainChatMessageHandler();
    gMainChatClient->registerMessageHandler(MsgHandler);

    ConnListener* connListener = new ConnListener();
    gMainChatClient->registerConnectionListener(connListener);

    FriendRoster* friendRoster = new FriendRoster();
    gMainChatClient->rosterManager()->registerRosterListener(friendRoster);
    gFriendRoster = friendRoster;

    std::string TlsActiveConfig = ReadConfigString("client.tls.active");

    if (TlsActiveConfig == "required") {
        L_INFO("gnf", "Setting tls to required.");
        gMainChatClient->setTls(gloox::TLSRequired);
    } else if (TlsActiveConfig == "optional") {
        L_INFO("gnf", "Setting tls to optional.");
        gMainChatClient->setTls(gloox::TLSOptional);
    } else {
        L_INFO("gnf", "Setting tls to disabled.");
        gMainChatClient->setTls(gloox::TLSDisabled);
    }

    L_INFO("gnf", "Connecting client...");
    gMainChatClient->connect(false);
}

bool GnfUpdate(int Timeout)
{
    gloox::ConnectionError ConError = gMainChatClient->recv(Timeout);

    if (ConError != gloox::ConnNoError) {
        L_ERROR("gnf", "Connection error.");
        return false;
    }

    return true;
}

void GnfSendMessage(const std::string &To, const std::string &Message)
{
    gloox::JID Recipient(To + "@" + ReadConfigString("client.account.host"));
    gloox::Message Msg(gloox::Message::Normal, Recipient, Message);

    L_INFO("gnf", "Sending message: " + Message + " To: " + Recipient.full());

    gMainChatClient->send(Msg);
}

void MainChatMessageHandler::handleMessage(const gloox::Message &stanza, gloox::MessageSession* session)
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

/**
 * @brief Returns the full friend roster
 *
 * @return vector<UserId> The vector with the user ids
 */
std::vector<UserId> GnfGetFullFriendRoster()
{
    return gFriendRoster->GetFullFriendRoster();
}
