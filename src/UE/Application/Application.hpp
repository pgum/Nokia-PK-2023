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
                ITimerPort& timer,
                ISmsDb& smsDb);
    ~Application();

    void handleTimeout() override;
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleBTSDisconnected() override;

    //call
    void handleCallRequest(common::PhoneNumber from) override;
    void handleBTSCallAccept(common::PhoneNumber from) override;
    void handleBTSCallDrop(common::PhoneNumber from) override;

    //call
    void handleCallAccept() override;
    void handleCallDrop() override;
    void handleUnknownRecipient() override;
    void handleDialModeAction() override;

    //callTalk
    void handleRecieveTalkMessage(std::string message) override;
    void handleComposeMessage() override;

    void handleShowSmsList() override;
    void handleShowSms(IUeGui::IListViewMode::Selection) override;
    void handleSmsDrop() override;
    void handleComposeSms() override;
    void handleSendSms(const Sms& sms) override;
    void handleSms(const Sms& sms) override;

private:
    Context context;
    common::PrefixedLogger logger;
};

} // namespace ue
