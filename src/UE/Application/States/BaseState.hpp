#pragma once

#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"

namespace ue
{

class Sms;

class BaseState : public IEventsHandler
{
public:
    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

    void handleTimeout() override;
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleBTSDisconnected() override;
    void handleSms(const Sms& sms) override;
    void handleComposeSms() override;
    void handleSendSms() override;
    void handleShowSmsList() override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
