#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    void start(IUserEventsHandler& handler);
    void stop();

    void setCallerNumber(common::PhoneNumber& number) override;
    void setReceivingCall(bool) override;

    common::PhoneNumber getCallerNumber() override;
    bool isReceivingCall() override;

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void showCalling(common::PhoneNumber from) override;
    void showTalking() override;
    void showPartnerNotAvailable() override;


private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;

    //number of UE from which we received callRequest
    common::PhoneNumber callerNumber;
    bool receivingCall = false;

};

}
