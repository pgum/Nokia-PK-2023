#pragma once

#include "Messages/PhoneNumber.hpp"

namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;

    virtual void handleComposeSms() = 0;
    virtual void handleSendSms() = 0;
    virtual void handleShowSmsList() = 0;
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
    virtual void viewSmsList() = 0;
    virtual std::pair<common::PhoneNumber, std::string> getSms() = 0;
};

} // namespace ue
