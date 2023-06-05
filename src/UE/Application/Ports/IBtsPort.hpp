#pragma once

#include "Messages/BtsId.hpp"
#include "ITransport.hpp"

namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void handleSib(common::BtsId) = 0;
    virtual void handleAttachAccept() = 0;
    virtual void handleAttachReject() = 0;
    virtual void handleBTSDisconnected() = 0;
    virtual void handleCallRequest(common::PhoneNumber from) = 0;
    virtual void handleBTSCallAccept(common::PhoneNumber from) = 0;
    virtual void handleUnknownRecipient() = 0;
    virtual void handleRecieveTalkMessage(std::string message) = 0;
    virtual void handleSendTalkMessage(common::PhoneNumber destNumber, std::string message) = 0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendCallAccept(common::PhoneNumber) = 0;
    virtual void sendCallReject(common::PhoneNumber) = 0;
    virtual void sendCallRequest(common::PhoneNumber) = 0;
    virtual void callTalk(common::PhoneNumber destNumber, std::string message) = 0;
};

}
