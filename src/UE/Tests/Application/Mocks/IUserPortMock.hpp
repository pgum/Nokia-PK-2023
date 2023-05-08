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
    MOCK_METHOD(void, setReceivingCall, (bool), (final));
    MOCK_METHOD(bool, isReceivingCall, (), (final));
    MOCK_METHOD(void, showPartnerNotAvailable, (), (final));


};

}
