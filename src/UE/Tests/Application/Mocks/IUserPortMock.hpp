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

    MOCK_METHOD(void, handleCallAccept, (), (final));
    MOCK_METHOD(void, handleCallDrop, (), (final));
    MOCK_METHOD(void, handleDialModeAction, (), (final));
    MOCK_METHOD(void, handleComposeMessage, (), (final));

    MOCK_METHOD(void, handleShowSmsList, (), (final));
    MOCK_METHOD(void, handleShowSms, (IUeGui::IListViewMode::Selection), (final));
    MOCK_METHOD(void, handleComposeSms, (), (final));
    MOCK_METHOD(void, handleSendSms, (const Sms&), (final));
    MOCK_METHOD(void, handleSmsDrop, (), (final));
};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, showCalling, (common::PhoneNumber), (final));
    MOCK_METHOD(void, showTalking, (), (final));
    MOCK_METHOD(void, setCallerNumber, (common::PhoneNumber&), (final));
    MOCK_METHOD(common::PhoneNumber, getCallerNumber, (), (final));
    MOCK_METHOD(void, showPartnerNotAvailable, (), (final));
    MOCK_METHOD(std::string, getOutgoingMessage, (), (final));
    MOCK_METHOD(void, displayMessage, (std::string), (final));
    MOCK_METHOD(void, showCallEnded, (), (final));
    MOCK_METHOD(common::PhoneNumber, getEnteredPhoneNumber, (), (final));


    MOCK_METHOD(void, showNewSmsNotification, (), (final));
    MOCK_METHOD(void, showNewSmsToEdit, (), (final));
    MOCK_METHOD(void, viewSmsList, (const std::vector<Sms>& messages), (final));
    MOCK_METHOD(void, viewSms, (const Sms&), (final));
};

}
