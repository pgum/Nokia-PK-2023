#pragma once

#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"

namespace ue
{

class BaseState : public IEventsHandler
{
public:
    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

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
    void handleDialModeAction() override;
    void handleBTSCallAccept(common::PhoneNumber number) override;

    //call talk
    void handleRecieveTalkMessage(std::string message) override;
    void handleSendTalkMessage(common::PhoneNumber destNumber, std::string message) override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
