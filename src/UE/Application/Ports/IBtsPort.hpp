#pragma once

#include "Messages/BtsId.hpp"
#include "ITransport.hpp"

namespace ue
{
class Sms;

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void handleSib(common::BtsId) = 0;
    virtual void handleAttachAccept() = 0;
    virtual void handleAttachReject() = 0;
    virtual void handleSms(const Sms& sms) = 0;
    virtual void handleBTSDisconnected() = 0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId) = 0;
};

}
