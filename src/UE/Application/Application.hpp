#pragma once

#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "IEventsHandler.hpp"
#include "Context.hpp"

namespace ue
{

using common::PhoneNumber;
using common::ILogger;

class Application : public IEventsHandler
{
public:
    Application(PhoneNumber phoneNumber,
                ILogger& iLogger,
                IBtsPort& bts,
                IUserPort& user,
                ITimerPort& timer);
    ~Application();

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    //attach, re-attach
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleBTSDisconnected() override;

    //call
    void handleCallRequest(common::PhoneNumber from) override;

    //IUserEventsHandler interface
    //call
    void handleCallAccept() override;
    void handleCallDrop() override;
    void handleUnknownRecipient() override;

private:
    Context context;
    common::PrefixedLogger logger;
};

}
