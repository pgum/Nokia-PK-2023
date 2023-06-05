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

    MOCK_METHOD(void, handleCallAccept, (), (final));
    MOCK_METHOD(void, handleCallDrop, (), (final));
    MOCK_METHOD(void, handleDialModeAction, (), (final));
    MOCK_METHOD(void, handleComposeMessage, (), (final));
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

};

}
