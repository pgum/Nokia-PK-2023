#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

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
    MOCK_METHOD(void, viewSmsList, (), (final));
    MOCK_METHOD((std::pair<common::PhoneNumber, std::string>), getSms, (), (final));
};

}
