#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"
#include "SmsDb.hpp"

namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;
    MOCK_METHOD(void, handleComposeSms, (), (final));
    MOCK_METHOD(void, handleSendSms, (), (final));
    MOCK_METHOD(void, handleShowSmsList, (), (final));
    MOCK_METHOD(void, handleShowSms, (std::size_t), (final));
};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, showNewSmsNotification, (), (final));
    MOCK_METHOD(void, showNewSmsToEdit, (), (final));
    MOCK_METHOD(void, viewSmsList, ((const std::vector<std::pair<Sms, smsState>>&)), (final));
    MOCK_METHOD(void, viewSms, (const Sms&), (final));
    MOCK_METHOD((std::pair<common::PhoneNumber, std::string>), getSms, (), (final));
};

}
