/**
 * @file
 * @brief The code for the conn Listener
 *
 * @author Lukas Deutscher
 * @date 25.12.2017
 */

#include "gnf.h" // The module header

extern gloox::Client* gMainChatClient;

std::map<gloox::CertStatus, std::string> gCertStatusMap {
    {gloox::CertOk,         "CertOk"},
    {gloox::CertInvalid,    "CertInvalid"},
    {gloox::CertSignerUnknown, "CertSignerUnknown"},
    {gloox::CertRevoked,    "CertRevoked"},
    {gloox::CertExpired,    "CertExpired"},
    {gloox::CertNotActive,  "CertNotActive"},
    {gloox::CertWrongPeer,  "CertWrongPeer"},
    {gloox::CertSignerNotCa, "CertSignerNotCa"}
};

/**
 * This map describes the error messages for the auth connect error
 */
std::map<gloox::AuthenticationError, std::string> AuthErrorMap {
    {gloox::AuthErrorUndefined,     "gloox::AuthErrorUndefined"},
    {gloox::SaslAborted,            "gloox::SaslAborted"},
    {gloox::SaslIncorrectEncoding,  "gloox::SaslIncorrectEncoding"},
    {gloox::SaslInvalidAuthzid,     "gloox::SaslInvalidAuthzid"},
    {gloox::SaslInvalidMechanism,   "gloox::SaslInvalidMechanism"},
    {gloox::SaslMalformedRequest,   "gloox::SaslMalformedRequest"},
    {gloox::SaslMechanismTooWeak,   "gloox::SaslMechanismTooWeak"},
    {gloox::SaslNotAuthorized,      "gloox::SaslNotAuthorized"},
    {gloox::SaslTemporaryAuthFailure, "gloox::SaslTemporaryAuthFailure"},
    {gloox::NonSaslConflict,        "gloox::NonSaslConflict"},
    {gloox::NonSaslNotAcceptable,   "gloox::NonSaslNotAcceptable"},
    {gloox::NonSaslNotAuthorized,   "gloox::NonSaslNotAuthorized"}
};

void ConnListener::onConnect()
{
    L_INFO("gnf", "Connected.");
    InterfaceSetInfoMsg("Connected.");
}

void ConnListener::onDisconnect(gloox::ConnectionError Error)
{
    InterfaceSetInfoMsg("Disconnected.");
    InterfaceDisplayInfoForm("Disconnected.");

    if (Error == gloox::ConnNoError) {
        L_INFO("gnf", "Disconnected.");
        return;
    }

    if (Error == gloox::ConnStreamError) {
        L_ERROR("gnf", "Disconnect: Stream Error");
    } else if (Error == gloox::ConnAuthenticationFailed) {
        L_ERROR("gnf", "Disconnect: Authentication Failed");
        std::string ErrorMessage = "There was an authentication error: ";
        ErrorMessage += AuthErrorMap[gMainChatClient->authError()];

        InterfaceDisplayErrorForm(ErrorMessage);
    } else {
        L_ERROR("gnf", "Disconnected with error.");
    }
}

bool ConnListener::onTLSConnect(const gloox::CertInfo &Info)
{
    L_INFO("gnf", "Trying to connect using tls.");

    time_t DateFrom(Info.date_from);
    time_t DateTo(Info.date_to);

    std::string InfoString = "";
    InfoString += "status: " + TranslateCertStatus(Info.status) + "\n";
    InfoString += "chain: " + std::to_string(Info.chain) + "\n";
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

    bool UserAnswer = InterfaceCreateAskForm("Do you want to accept this Certificate?\n\n" + InfoString);

    if (UserAnswer) {
        InterfaceSetInfoMsg("TLS Connected.");
        return true;
    } else {
        L_INFO("gnf", "User didn't accept Certificate.");
        InterfaceSetInfoMsg("TLS Disconnected.");
        return false;
    }
}

/**
 * @brief Translates the bitmap for the Cert Status to a string
 *
 * @param int The cert status bitmap
 * @return string The human readable string
 */
std::string TranslateCertStatus(const int &StatusBitmap)
{
    std::string CertOkString;

    if (StatusBitmap == gloox::CertOk) {
        CertOkString += gCertStatusMap[gloox::CertOk];
    }

    if (StatusBitmap & gloox::CertInvalid) {
        CertOkString += gCertStatusMap[gloox::CertInvalid];
    }
    if (StatusBitmap & gloox::CertSignerUnknown) {
        CertOkString += gCertStatusMap[gloox::CertSignerUnknown];
    }
    if (StatusBitmap & gloox::CertRevoked) {
        CertOkString += gCertStatusMap[gloox::CertRevoked];
    }
    if (StatusBitmap & gloox::CertExpired) {
        CertOkString += gCertStatusMap[gloox::CertExpired];
    }
    if (StatusBitmap & gloox::CertNotActive) {
        CertOkString += gCertStatusMap[gloox::CertNotActive];
    }
    if (StatusBitmap & gloox::CertWrongPeer) {
        CertOkString += gCertStatusMap[gloox::CertWrongPeer];
    }
    if (StatusBitmap & gloox::CertSignerNotCa) {
        CertOkString += gCertStatusMap[gloox::CertSignerNotCa];
    }

    return CertOkString;
}
