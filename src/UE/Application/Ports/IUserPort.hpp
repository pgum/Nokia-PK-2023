#pragma once

#include "Messages/PhoneNumber.hpp"
#include "ISmsDb.hpp"
#include "UeGui/IListViewMode.hpp"

namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;

    virtual void handleShowSmsList() = 0;
    virtual void handleShowSms(IUeGui::IListViewMode::Selection) = 0;
    virtual void handleComposeSms() = 0;
    virtual void handleSendSms(const Sms& sms) = 0;
    virtual void handleSmsDrop() = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;

    virtual void showNewSmsNotification() = 0;
    virtual void viewSmsList(const std::vector<Sms>&) = 0;
    virtual void viewSms(const Sms&) = 0;
    virtual void showNewSmsToEdit() = 0;
};

} // namespace ue
