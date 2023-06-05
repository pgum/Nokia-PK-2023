#pragma once

#include "Messages/PhoneNumber.hpp"
#include "ISmsDb.hpp"

namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;

    virtual void handleComposeSms() = 0;
    virtual void handleSendSms() = 0;
    virtual void handleShowSmsList() = 0;
    virtual void handleShowSms(std::size_t) = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void showNewSmsNotification() = 0;
    virtual void showNewSmsToEdit() = 0;
    virtual void viewSmsList(const std::vector<std::pair<Sms, smsState>>&) = 0;
    virtual std::pair<common::PhoneNumber, std::string> getSms() = 0;
    virtual void viewSms(const Sms&) = 0;
};

} // namespace ue
